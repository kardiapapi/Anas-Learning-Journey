#include <windows.h>
#include <stdio.h>

// 1. Fixed calling convention syntax
#define clrfuncstack __stdcall

// Forward declaration with proper calling convention
LRESULT clrfuncstack WndProc(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
);

// Window procedure implementation
LRESULT clrfuncstack WndProc(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam) 
{
    switch (msg) 
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            
        case WM_CLOSE:
            DestroyWindow(hWnd);
            OutputDebugStringA("close\n");
            return 0;
            
        // Other cases should either return 0 or fall through to default
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    
}

// WinMain implementation
int __stdcall WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd)
{
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";  // 2. Use wide string literal
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassEx(&wc)) 
    {
        MessageBox(NULL, 
            L"Class registration failed!", 
            L"Error", 
            MB_ICONERROR);
        return 1;
    }

    // 3. Fixed window creation
    HWND hWnd = CreateWindowEx(
        0,
        L"MyWindowClass",
        L"My Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        800, 
        600,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hWnd)
    {
        MessageBox(NULL, 
            L"Window creation failed!", 
            L"Error", 
            MB_ICONERROR);
        return 1;
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 4. Proper return value
    return 0;
}