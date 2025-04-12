// stick
#include <windows.h>
#include <stdio.h>
#define clrfuncstack __stdcall // types of clearing the stack C
#define local static
#define global static
#define internal static
// declaration
global BITMAPINFO BitmapInfo ;
global void * BitmapMemory ;
//global HBITMAP BitmapHandle  ;
global int MapWidth;
global int MapHeight;
//global HDC Bitmaphdc ;
//global HDC hdc ;
// proc f 
LRESULT CALLBACK WndProc(HWND Hmodule,UINT msg,WPARAM wParam,LPARAM lParam);

// mreating memory buffer compatible with our DC
// note m ggonna get rid of createcompatibleDC and try to allocate memory manually == no more DC xd  

internal void ResizeDIBSection(int Width , int Height){
     MapWidth = Width ;
     MapHeight = Height ;
    printf("mapW %d\n",MapWidth);
    printf("maph %d\n",MapHeight);
    printf("width2 %d\n",Width);
    if(BitmapMemory){VirtualFree(BitmapMemory , 0 , MEM_RELEASE);}   
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = MapWidth;
    BitmapInfo.bmiHeader.biHeight = -MapHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32; // 8 byte blue 8 red 8 green 8 for PADDING = boundary
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

int BytesperPixel = 4;
int BitmapMemorySize = (Width*Height)*BytesperPixel ; 
BitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);

int pitch = MapWidth*BytesperPixel ; 
unsigned char*row = (unsigned char*)BitmapMemory;
for(int y = 0 ; y < MapHeight ;y++){
           unsigned char *pixel= row ;
        for(int x = 0 ; x< MapWidth ; x++){
            *pixel =255  ;          // blue -> little indian
            pixel++;
            
            *pixel = 0 ;
            pixel++;
            
            *pixel = 0 ;
            pixel++;
            
            *pixel = 0 ;
            pixel++; 
        }
        row += pitch ;
    }
}
// MEM_COMMIT VS MEM_RESERVE decides if we wanna use now or later {cpu tracking or not yet }
//BitmapHandle = CreateDIBSection(hdc, &BitmapInfo, DIB_RGB_COLORS, &BitmapMemory, 0, 0); // bitmapmemory is a pointer to a poniter *Bitmapmemory  
//    ReleaseDC(0, hdc);


// copying our mm buffer to the actual HDC
internal void
updatepaint(HDC hdc ,RECT *WndRect , int x , int y , int Width , int Height  ){
int WwndWidth = WndRect->bottom - WndRect->top;
int WndHeight =WndRect->right - WndRect->left;
StretchDIBits(hdc,
0, 0, MapWidth, MapHeight,
0, 0, WwndWidth, WndHeight,
BitmapMemory,
&BitmapInfo,
DIB_RGB_COLORS, SRCCOPY);


                                                            };

     // modulehandle funcPROC
LRESULT CALLBACK WndProc(HWND Hmodule, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (msg)
    {
    case WM_DESTROY:
    {
        OutputDebugStringA("destoy\n");
        PostQuitMessage(0);
        return 0;
    }
    break;
    case WM_SIZE:
    { 
      RECT clientrect ;
      GetClientRect(Hmodule , &clientrect) ;
      
      int Width = clientrect.right - clientrect.left;
      int Height = clientrect.bottom - clientrect.top;
      printf("width %d\n",Width);
      printf("height: %d\n",Height);
      ResizeDIBSection(Width , Height );
      OutputDebugStringA("SIWW\n");
        return 0;
    }
    case WM_PAINT:
    { 
        
    OutputDebugStringA("WEEEPAINT\n");                                                                                           
    PAINTSTRUCT ps ;
    HDC hdc = BeginPaint(Hmodule,&ps);  
        int x = ps.rcPaint.left;
        int y = ps.rcPaint.top;
        int Width = ps.rcPaint.right - ps.rcPaint.left;
        int Height = ps.rcPaint.bottom - ps.rcPaint.top;
        RECT clientrect ;
    GetClientRect(Hmodule , &clientrect) ;  
    updatepaint(hdc,&clientrect , x, y, Width, Height);    
    EndPaint(Hmodule , &ps);
    return 0;
    }
    break;
    case WM_CLOSE:
    {
        DestroyWindow(Hmodule);
        OutputDebugStringA("close\n");

        return 0;
    }
    default:
    {
        OutputDebugStringA("default\n");
        return DefWindowProc(Hmodule, msg, wParam, lParam);
    }
    break;
    }
}


int WINAPI WinMain(HINSTANCE hinstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nShowCmd)
{

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hinstance;
    wc.lpszClassName = "MyWindowClass";
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    MSG msg;
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Class registration failed!", "Error", MB_ICONERROR);
        return 1;
    }
    else
    {

        HWND Hmodule = CreateWindowEx(0,
                                      "MyWindowClass",
                                      "mywindow",
                                      WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                      NULL,
                                      NULL,
                                      GetModuleHandle(0),
                                      NULL);

        if (!Hmodule)
        {
            MessageBox(NULL, "Window creation failed!", "Error", MB_ICONERROR);
            return 1;
        }
        else
        {
            ShowWindow(Hmodule, nShowCmd);
         //   UpdateWindow(Hmodule); 

            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    return (0);
}
