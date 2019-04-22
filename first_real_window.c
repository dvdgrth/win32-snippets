// 0. #include <windows.h> and link User32.lib (and Winmm.lib fro playsound)
// 1. WinMain entry point. The user-provided entry point for a graphical Windows-based application.
// 2. WNDCLASSEX structure. Contains window class information. It is used with the RegisterClassEx and GetClassInfoEx  functions.
// 3. WindowProc callback function. An application-defined function that processes messages sent to a window. The WNDPROC type defines a pointer to this callback function.
// 4. RegisterClassEx function. Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function.
// 5. CreateWindowEx function. Creates an overlapped, pop-up, or child window with an extended window style.
// 6. MSG structure. Contains message information from a thread's message queue.
// 7a. PeekMessage function. Dispatches incoming sent messages, checks the thread message queue for a posted message, and retrieves the message (if any exist).
// 7b. GetMessage function. Retrieves a message from the calling thread's message queue. The function dispatches incoming sent messages until a posted message is available for retrieval.
// 8. TranslateMessage function. Translates virtual-key messages into character messages. The character messages are posted to the calling thread's message queue, to be read the next time the thread calls the GetMessage or PeekMessage function.
// 9. DispatchMessage function. Dispatches a message to a window procedure. It is typically used to dispatch a message retrieved by the GetMessage function.
// 10. (3). DefWindowProc function. Calls the default window procedure to provide default processing for any window messages that an application does not process.
// This function ensures that every message is processed. DefWindowProc is called with the same parameters received by the window procedure.

#include <windows.h>

// 3. WindowProc callback function.
// Forward Declaration.
LRESULT CALLBACK DavidsMainWindowCallback(
  HWND   Window,
  UINT   Message,
  WPARAM WParam,
  LPARAM LParam);

// 1. WinMain entry point.
int CALLBACK WinMain(
  HINSTANCE Instance,
  HINSTANCE PrevInstance,
  LPSTR     CommandLine,
  int       ShowCode)
{
  // 2. WNDCLASSEX structure.
  // Initialize everything to 0, then set a few member.
  WNDCLASSEX DavidsWindowClass = {0};
  DavidsWindowClass.cbSize = sizeof(WNDCLASSEX);
  DavidsWindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
  DavidsWindowClass.lpfnWndProc = DavidsMainWindowCallback;
  DavidsWindowClass.hInstance = Instance;
  DavidsWindowClass.lpszClassName = "DavidsMainWindowClassBla";

  // 4. RegisterClassEx function.
  if(!RegisterClassEx(&DavidsWindowClass))
  {
    MessageBox(NULL, "Window Registration Failed!", "Error!",
    MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  // 5. CreateWindowEx function.
  HWND DavidsWindow = CreateWindowEx(0,
                                    DavidsWindowClass.lpszClassName,
                                    "Davids Application",
                                    WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                    CW_USEDEFAULT,
                                    CW_USEDEFAULT,
                                    CW_USEDEFAULT,
                                    CW_USEDEFAULT,
                                    0,
                                    0,
                                    Instance,
                                    0);

  if(DavidsWindow == NULL)
  {
      MessageBox(NULL, "Window Creation Failed!", "Error!",
          MB_ICONEXCLAMATION | MB_OK);
      return 0;
  }

  // 6. MSG structure.
  MSG Message;

  // 7b. GetMessage function.
  while(GetMessage(&Message, 0, 0, 0) > 0)
  {
    // 8. TranslateMessage function.
    TranslateMessage(&Message);
    // 9. DispatchMessage function.
    DispatchMessage(&Message);
  }
  return Message.wParam;
}

// 3. WindowProc callback function.
LRESULT CALLBACK DavidsMainWindowCallback(
  HWND   Window,
  UINT   Message,
  WPARAM WParam,
  LPARAM LParam)
{
  HDC hdc;
  PAINTSTRUCT ps;
  RECT rect;

  switch(Message)
  {
    case WM_CREATE:
        PlaySound("bachfugue.wav", NULL, SND_FILENAME | SND_ASYNC);
        return 0 ;
    case WM_PAINT:
        hdc = BeginPaint(Window, &ps);
        GetClientRect(Window, &rect);
        DrawText(hdc, "Hello, people!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(Window, &ps);
        return 0;
    case WM_CLOSE:
        DestroyWindow(Window);
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
    break;
    default:
        // 10. (3). DefWindowProc function.
        return DefWindowProc(Window, Message, WParam, LParam);
  }
}