// winAPI2Dimitation_LIS.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "TouhouIN.h"
#include <locale.h>

#define MAX_LOADSTRING 100

//HINSTACNE, HWND 등의 자료형은 typedef로 어떤 역할을 하는 자료형인지 이름을 바꾸어 준 것.
//CALLBACK APIENTRY, _In_ 등은 주석의 역할을 해주는 키워드.

// 전역 변수:
//WCHAR : 모든 문자(영어 외의)를 표현하기 위한 자료형
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
PAINTSTRUCT ps;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//hInstance : 실행된 프로세스의 시작 주소, 인스턴스 핸들
//hPrevInstance : 이전에 실행된 인스턴스 핸들
//lpCmdLine : 명령으로 입력된 프로그램의 인수
//nCmdShow : 윈도우의 보이는(시작될) 상태
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    //안쓰는 인자들.
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2DIMITATIONLIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    setlocale(LC_ALL, "");

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //단축키 로드. 아래쪽에 있는 TranslateAccelerator로 단축키인지 확인
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2DIMITATIONLIS));

    //아래쪽에 GetMessage로 msg값에 메세지를 저장.
    MSG msg;

    // 기본 메시지 루프입니다:
    //GetMessage는 메세지가 없을 경우 false 반환이 아니라, 대기함. false를 반환하는 경우는 exit 등의 message를 받았을 경우.
    //message가 없어도 무언가 작동되게 하고 싶으면 GetMessage가 아니라 PeekMessage를 사용.
    CCore::getInstance()->init();
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
            {
                break;
            }
                        
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 update
            // 게임 render
            CCore::getInstance()->update();
            CCore::getInstance()->render();
            
        }
    }
    
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //기본 창 정보 설정
    WNDCLASSEXW wcex;

    //구조체의 크기
    wcex.cbSize = sizeof(WNDCLASSEX);

    //창 스타일 설정
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    //창 프로시저 설정(윈도우 메세지 처리 함수)
    wcex.lpfnWndProc    = WndProc;
    //창이 사용하고자 하는 여분의 메모리 크기?
    wcex.cbClsExtra     = 0;
    //개별 창에서 사용하고자 하는 여분의 메모리 크기?
    wcex.cbWndExtra     = 0;
    //핸들 값
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2DIMITATIONLIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //창 메뉴줄 설정
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_WINAPI2DIMITATIONLIS);
    wcex.lpszClassName  = szWindowClass;
    //창의 작은 아이콘
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //설정된 창 정보로 실제로 창 생성
   hWnd = CreateWindowW(szWindowClass,
                             szTitle,
                             WS_MYSTYLE /*WS_OVERLAPPEDWINDOW*/,
                             WS_STARTX, //CW_USEDEFAULT
                             WS_STARTY, //0
                             WS_WIDTH, //CW_USEDEFAULT
                             WS_HEIGHT, //0
                             nullptr, //창의 부모
                             nullptr, 
                             hInstance, 
                             nullptr); //추가 매개변수

   if (!hWnd)
   {
      return FALSE;
   }
   
   //창 메뉴, 스크롤 등을 제외한 크기로 창 크기 설정.
   RECT rc;
   rc.top = 0;
   rc.left = 0;
   rc.bottom = WS_HEIGHT;
   rc.right = WS_WIDTH;
   AdjustWindowRect(&rc, WS_MYSTYLE, false); // false로 해야 메뉴 제외 크기값 얻음. 해당 함수로 rc의 값을 재조절함.
   //실제 창 크기,위치 재설정.
   SetWindowPos(hWnd, NULL, WS_STARTX, WS_STARTY, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
            //dc : device context
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            Logger::debug(L"Paint");
            
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
