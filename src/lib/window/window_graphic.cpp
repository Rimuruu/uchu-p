#include "graphic.h"
#undef UNICODE
#define UNICODE
#include <windows.h>
#include <objidl.h>


HWND hwnd;

int FPS = 60;
int RUNNING = 1;
int FRAMETIME = 1000 / FPS;

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

int createWindow(int x, int y, int width, int height, const char* title,Buffer* buffer) {

    


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

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)buffer);

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

    buffer->memory = globalBufferWin.memory;
    buffer->sizeX = globalBufferWin.width;
    buffer->sizeY = globalBufferWin.height;



    

    return 0;
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    Buffer* buffer = (Buffer*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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

        OnPaint(hdc,buffer);
        
        EndPaint(hwnd, &ps);
    }
    return 0;

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

int loop(Buffer* buffer) {



    MSG msg = { };
    int countFrame = 0;



    LONGLONG elapsedTime;
    LONGLONG startTimeFrame;
    LONGLONG endTime;
    LONGLONG startTime = GetTicks();
  
    while (RUNNING){
        startTimeFrame = GetTicks();
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        updateAndRender(buffer);
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