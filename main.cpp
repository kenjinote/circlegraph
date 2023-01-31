#pragma comment(lib, "ComCtl32.lib")
#pragma comment(linker, "/opt:nowin98")
#include <windows.h>
#include <commctrl.h>
#include <math.h>

CHAR szClassName[]="window";
HWND hTrack;

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static RECT rect={10,50,10+256,50+256};
	switch (msg){
	case WM_HSCROLL:
		InvalidateRect(hWnd,&rect,FALSE);
		break;
	case WM_CREATE:
		InitCommonControls();
		hTrack = CreateWindow("msctls_trackbar32","",WS_CHILD|WS_VISIBLE|0x100/*tooltip*/,10,10,256,30,hWnd,NULL,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		SendMessage(hWnd,WM_HSCROLL,0,0);
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc;
			int nPos=SendMessage((HWND)hTrack,TBM_GETPOS,0,0);
			hdc=BeginPaint(hWnd,&ps);
			if(nPos==0){
				MoveToEx(hdc,rect.left,(rect.top+rect.bottom)/2-1,NULL);
				LineTo(hdc,rect.left+(rect.right-rect.left)/2,rect.top+(rect.bottom-rect.top)/2-1);
			}else if(nPos==100){
				Ellipse(hdc,rect.left,rect.top,rect.right,rect.bottom);
			}else{
				Pie(hdc,rect.left,rect.top,rect.right,rect.bottom,-(long)(cos((double)nPos*0.06283185307179586)*(rect.right-rect.left)/2)+rect.left+(rect.right-rect.left)/2,-(long)(sin((double)nPos*0.06283185307179586)*(rect.bottom-rect.top)/2)+rect.top+(rect.bottom-rect.top)/2,rect.left,(rect.top+rect.bottom)/2);
			}
			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,msg,wParam,lParam));
    }
    return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
                   LPSTR pCmdLine,int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS wndclass;
    if(!hPreInst){
        wndclass.style=CS_HREDRAW|CS_VREDRAW;
        wndclass.lpfnWndProc=WndProc;
        wndclass.cbClsExtra=0;
        wndclass.cbWndExtra=0;
        wndclass.hInstance =hinst;
        wndclass.hIcon=NULL;
        wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
        wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
        wndclass.lpszMenuName=NULL;
        wndclass.lpszClassName=szClassName;
        if(!RegisterClass(&wndclass))
            return FALSE;
    }
    hWnd=CreateWindow(szClassName,
        "ƒ^ƒCƒgƒ‹",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hinst,
        NULL);
    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}


