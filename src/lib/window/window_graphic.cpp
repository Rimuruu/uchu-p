#include "graphic.h"
#undef UNICODE
#define UNICODE
#define _WIN32_WINNT 0x502 
#include <windows.h>
#include "key_binding.h" 
#include "uchu.h"

HWND hwnd;

int FPS = 60;
int RUNNING = 1;
int FRAMETIME = 1000 / FPS;

typedef unsigned int u_int32;

std::unordered_map<u_int32, u_int32> keyMapping = {

    {VK_UP,K_UP},
    {VK_RIGHT,K_RIGHT},
    {VK_DOWN,K_DOWN},
    {VK_LEFT,K_LEFT},
    {VK_SPACE,K_SPACE},
};
std::unordered_map<unsigned int, BMPFile*> sprites;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

typedef unsigned int u_int32;

struct win32_offscreen_buffer {
    // Pixels are alwasy 32-bits wide, memory Order BB GG RR XX, 0xXXRRGGBB
    BITMAPINFO info;
    void* memory;
    int width;
    int height;
};

win32_offscreen_buffer globalBufferWin = {};

VOID OnPaint(HDC hdc,Buffer* buffer)
{
  

    StretchDIBits(
        hdc,
        0,
        0,
        globalBufferWin.width,
        globalBufferWin.height,
        0,
        0,
        globalBufferWin.width,
        globalBufferWin.height,
        globalBufferWin.memory,
        &(globalBufferWin.info),
        DIB_RGB_COLORS,
        SRCCOPY
    );

    
}

LPCWSTR ConvertToLPCWSTR(const char* text) {
    int size = MultiByteToWideChar(CP_ACP, 0, text, -1, nullptr, 0);
    if (size == 0) {
        // Failed to get the required size
        return nullptr;
    }

    wchar_t* wideText = new wchar_t[size];
    if (MultiByteToWideChar(CP_ACP, 0, text, -1, wideText, size) == 0) {
        // Conversion failed
        delete[] wideText;
        return nullptr;
    }

    return wideText;
}


BMPFile* loadImageBMP(const char* filePath) {
    BMPFile* fileW = nullptr;
    char* buffer = nullptr;
    int offset = 0;
    int fileSize = 0;
    int isPadding = 0;
    auto file = fopen(filePath, "rb");
    if (!file)
    {
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char*)malloc(sizeof(char) * (fileSize));
    if (buffer == nullptr) return nullptr;
    memset(buffer, 0, fileSize + 1);
    fread(buffer, sizeof(char), BMPHEADERSIZE, file);

    
    fileW = (BMPFile*)buffer;
    if(fileW->infoHeader.bitCount <= 8){
        fileW->table = (Color*)malloc(sizeof(Color) * (fileW->infoHeader.bitCount));
        fseek(file, BMPHEADERSIZE, SEEK_SET);
        fread((char*)fileW->table, sizeof(char), fileW->infoHeader.bitCount * sizeof(Color), file);
        fseek(file, BMPHEADERSIZE + fileW->infoHeader.bitCount * sizeof(Color), SEEK_SET);
        offset = BMPHEADERSIZE + fileW->infoHeader.bitCount * sizeof(Color);
    }
    else {
        fseek(file, BMPHEADERSIZE, SEEK_SET);
        offset = BMPHEADERSIZE;
    }

    int padding = 4 - ((fileW->infoHeader.width * 3) % 4);
    padding = 4 ? 0 : padding;
    fileW->data = (char*)malloc(sizeof(char) * (fileW->infoHeader.imageSize));
    memset(fileW->data, 0, fileW->infoHeader.imageSize);
    int i, y;
    for ( i = offset, y = 0; i < fileW->infoHeader.imageSize; i = i + (fileW->infoHeader.width * 3) +padding,y = y + (fileW->infoHeader.width * 3)) {
        fseek(file, i, SEEK_SET);
        fread((char*)fileW->data+y, sizeof(char), fileW->infoHeader.width*3, file);
        
    }
   
    


    fclose(file);
    return fileW;


}


int loadImage(const char* filePath,unsigned int a) {
    BMPFile* image = loadImageBMP(filePath);
    if (image == nullptr) return -1;
    std::pair<unsigned int, BMPFile*> pair(a, image);
    sprites.emplace(pair);

}




int createWindow(int x, int y, int width, int height, const char* title,Game* game) {

    


    HINSTANCE hInstance =  GetModuleHandle(0);
    
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"UchuClass";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    DWORD window_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU  ;
    RECT window_rect;
    window_rect.right = width;
    window_rect.bottom = height;
    window_rect.left = window_rect.top = 0;

    AdjustWindowRectEx(&window_rect, window_style, FALSE, window_style);

    int max_right = window_rect.right - window_rect.left;
    int max_bottom = window_rect.bottom - window_rect.top;

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        ConvertToLPCWSTR(title),    // Window text
        window_style,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, max_right, max_bottom,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );



    if (hwnd == NULL)
    {
        return 0;
    }

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)game);

    ShowWindow(hwnd, 1);

    globalBufferWin.memory = VirtualAlloc(
        0,
        BYTES_PER_PIXEL*width*height,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE

    );
    globalBufferWin.height = height;
    globalBufferWin.width = width;
    globalBufferWin.info.bmiHeader.biSize = sizeof(globalBufferWin.info.bmiHeader);
    globalBufferWin.info.bmiHeader.biWidth = width;
    globalBufferWin.info.bmiHeader.biHeight = height;
    globalBufferWin.info.bmiHeader.biPlanes = 1;
    globalBufferWin.info.bmiHeader.biBitCount = 32;
    globalBufferWin.info.bmiHeader.biCompression = BI_RGB;

    game->buffer.memory = globalBufferWin.memory;
    game->buffer.sizeX = globalBufferWin.width;
    game->buffer.sizeY = globalBufferWin.height;



    

    return 0;
}

u_int32 keyMap(WPARAM wParam) {
    return keyMapping[(u_int32)wParam];
}

int main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // You can process Windows-specific initialization here if needed.

    AllocConsole();
    AttachConsole(GetCurrentProcessId());

    // Redirect stdin, stdout, and stderr to the console
    FILE* conin, * conout, * conerr;
    freopen_s(&conin, "CONIN$", "r", stdin);
    freopen_s(&conout, "CONOUT$", "w", stdout);
    freopen_s(&conerr, "CONOUT$", "w", stderr);

    int argc = __argc;
    char** argv = __argv;

    int result =main();
    FreeConsole();
    return result;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    Game* game = (Game*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    u_int32 v;
    Button_state key;
    switch (uMsg)
    {
    case WM_DESTROY:
        RUNNING = 0;
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        OnPaint(hdc,&(game->buffer));
        
        EndPaint(hwnd, &ps);
    }
    return 0;
    case WM_KEYDOWN:
        v = keyMap(wParam);
        if (v == 0) break;
        key = { v,1 };
        game->input.queue(key);
        break;
    case WM_KEYUP:
        v = keyMap(wParam);

        if (v == 0) break;
         key = { v,0 };
        game->input.queue(key);
        break;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

static inline LONGLONG GetTicks()
{
    LARGE_INTEGER ticks;
    LARGE_INTEGER frequency;
    if (!QueryPerformanceCounter(&ticks))
    {
        return 0;
    }

    if (!QueryPerformanceFrequency(&frequency)) {
        return 0;
    }

    return  (ticks.QuadPart/ frequency.QuadPart)*1000;
}

int loop(Game* game) {



    MSG msg = { };
    int countFrame = 0;



    LONGLONG elapsedTime;
    LONGLONG startTimeFrame;
    LONGLONG endTime;
    LONGLONG startTime = GetTicks();
    init(game);

    while (RUNNING){
        startTimeFrame = GetTicks();
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        updateAndRender(game);
        RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
        countFrame++;
        endTime = GetTicks();
        elapsedTime = endTime - startTimeFrame;
        if (elapsedTime < FRAMETIME) {
            Sleep(FRAMETIME - elapsedTime);
        }
        if (endTime - startTime > 1000) {
            printFormat(INFO, "%d FPS\n", (countFrame));
            startTime = GetTicks();
            countFrame = 0;
        }
    }
    end(game);
    
        
        

   

    return 0;
}

int drawRectangle(int srcX, int srcY, int destX, int destY, int color) {
    int rsrcX = srcX < destX? srcX: destX;
    int rsrcY = srcY < destY ? srcY : destY;
    int rdestX = srcX > destX ? srcX : destX;
    int rdestY = srcY > destY ? srcY : destY;

    u_int32* pixels = (u_int32*)globalBufferWin.memory;

    rdestX = rdestX > globalBufferWin.width ? globalBufferWin.width : rdestX;
    rdestY = rdestY > globalBufferWin.height ? globalBufferWin.height : rdestY;
    rsrcX = rsrcX < 0 ? 0 : rsrcX;
    rsrcY = rsrcY < 0 ? 0 : rsrcY;


    for (int x = rsrcX; x < rdestX; x++) {
        for (int y = rsrcY; y < rdestY; y++) {
            int caseX = (y * globalBufferWin.width) + x;
            
            pixels[caseX] = color;
            
        }
    }



    return 0;

}

struct int24 {
    char data[3];




};


int drawImage(int destX, int destY, unsigned int a) {

    BMPFile image = *(sprites.at(a));
    u_int32* pixels = (u_int32*)globalBufferWin.memory;
    int24* im = (int24*)image.data;
    int maxX = destX + image.infoHeader.width >  globalBufferWin.width ? globalBufferWin.width : destX + image.infoHeader.width;
    int maxY = destY + image.infoHeader.height > globalBufferWin.height ? globalBufferWin.height : destY + image.infoHeader.height;

    int minX = destX < 0 ? 0 : destX;
    int minY = destY < 0 ? 0 : destY;

    int test = image.infoHeader.imageSize/ (image.infoHeader.bitCount/8) / image.infoHeader.height;
    int test2 = image.infoHeader.imageSize / (image.infoHeader.bitCount / 8) / image.infoHeader.width;
    int padding = (image.infoHeader.width * 3) % 4;

    for (int x = minX; x < maxX; x++) {
        for (int y = minY; y < maxY; y++) {
            int caseX = (y * globalBufferWin.width) + x;
            int iX = x - minX;
            int iY = y - minY;
            int24 color = *(im + (iY * image.infoHeader.width) + iX);
            u_int32* tmp = (u_int32*)color.data;
            pixels[caseX] = (*tmp) & 0x00FFFFFF;
            int j = pixels[caseX];
            
        }
    }



    return 0;



}

int cleanupImage() {
    std::unordered_map<unsigned int, BMPFile *>::iterator it;
    for (it = sprites.begin(); it != sprites.end(); it++)
    {
        BMPFile* file = it->second;
        if (file != nullptr) {
            if (file->table != nullptr) free(file->table);
            if (file->data != nullptr) free(file->data);
            free(file);
        }
    }
    return 0;
}