#include <windows.h>
#include <stdio.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    SetProcessDPIAware();  // When not called, GetSystemMetrics() returns scaled pixel values.
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);

    char *buffer = malloc(100);
    sprintf(buffer, "Width is %d and height is %d.", x, y);

    MessageBox(NULL, buffer, TEXT("Hi there"), MB_OK);

    free(buffer);
}

