#include "graphic.h"
#undef UNICODE
#define UNICODE
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

int createWindow(int x, int y, int width, int height, const char* title) {
    HINSTANCE hInstance =  GetModuleHandle(0);
    
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"UchuClass";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        ConvertToLPCWSTR(title),    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        x, y, width, height,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, 1);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    printFormat(INFO, "uMsg %d ", uMsg);
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}