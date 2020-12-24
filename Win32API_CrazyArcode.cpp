
// Win32API_CrazyArcode.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "framework.h"
#include "Win32API_CrazyArcode.h"
#include "GameMananger.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32APICRAZYARCODE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APICRAZYARCODE));

    MSG msg;
    ULONGLONG tick = GetTickCount64();
    GameMananger gameManager(hWnd);
    gameManager.LoadLobbyData();
    gameManager.LoadMapData();
  
    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            else 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        if (GetTickCount64() > tick + 33)
        {
            tick = GetTickCount64();
            gameManager.Run();
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APICRAZYARCODE));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;     //MAKEINTRESOURCEW(IDC_WIN32APICRAZYARCODE);.. 메뉴창삭제
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_SYSMENU,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT clientRect{ 0, 0, 800, 600 };
    static HCURSOR cursor = (HCURSOR)LoadImage(NULL, "image\\Default\\cursor.cur", IMAGE_CURSOR, 33, 36, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    switch (message)
    {
    case WM_CREATE:
        //윈도우 크기결정
        AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, false);
        MoveWindow(hWnd, 400, 100, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, true);
        //커서 이미지 변경
        //SetCursor(cursor);
        break;

    case WM_GETMINMAXINFO:      //윈도우크기변경시 생성되는 메시지
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = clientRect.right - clientRect.left;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = clientRect.bottom - clientRect.top;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = clientRect.right - clientRect.left;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = clientRect.bottom - clientRect.top;
        break;

    case WM_SETCURSOR:          //마우스가 윈도우창나갔다가 들어올때 생성되는 메시지
        //SetCursor(cursor);
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
