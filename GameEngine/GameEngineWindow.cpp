#include "PreCompile.h"
#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>
#include <iostream>

// �������� �̱���
GameEngineWindow* GameEngineWindow::Inst = new GameEngineWindow();

bool WindowOn = true;

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        // HDC �����쿡 �ȼ��� ������ �ٲܼ� �ִ� �������Դϴ�.
        // ������â�� �׷����� 2���� �迭�� �����Ҽ� �ִ� �����Դϴ�.
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
        break;
    }
    case WM_SIZE:
    {
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
        break;
    }
    case WM_DESTROY:
    {
        WindowOn = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow() 
    : className_("")
    , windowTitle_("")
    , windowhandle_(nullptr)
    , hInstance_(nullptr)
    , devicecontext_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
    if (nullptr != windowhandle_)
    {
        DestroyWindow(windowhandle_);
        windowhandle_ = nullptr;
    }
}

// constructer destructer
//member Func
void GameEngineWindow::CreateMainWindowClass()
{
    hInstance_ = GetModuleHandle(NULL);

    if (nullptr == hInstance_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    className_ = "DEF";

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW; // ȭ�� �簻�� �ɼ�
    wcex.lpfnWndProc = WndProc; // <= ���� ����
    wcex.cbClsExtra = 0; // �Ű�Ƚᵵ ��
    wcex.cbWndExtra = 0; // �Ű�Ƚᵵ ��.
    wcex.hInstance = hInstance_;
    wcex.hIcon = nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor = nullptr;//LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName = className_.c_str();
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // �Ʒ��� �Լ��� ������ 
    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateMainWindow(const std::string& _titlename, const float4& _size, const float4& _pos)
{
    CreateMainWindowClass();

    if (nullptr == hInstance_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    if ("" == className_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    windowTitle_ = _titlename;
    windowhandle_ = nullptr;
    windowhandle_ = CreateWindowA(className_.c_str(), "TEST", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance_, nullptr);

    if (0 == windowhandle_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    SetWindowTextA(windowhandle_, windowTitle_.c_str());
    ShowWindow(windowhandle_, SW_SHOW);
    SetSizeAndPos(_size, _pos);
    UpdateWindow(windowhandle_);


    HDC Devicecontext = ::GetDC(windowhandle_);
    return;
}

void GameEngineWindow::SetSizeAndPos(const float4& _size, const float4& _pos)
{
    size_ = _size;
    pos_ = _pos;

    //          1920          
    RECT Rc = { 0, 0, _size.ix(), _size.iy() };
    // ���� �־��� ��Ʈ�� Ÿ��Ʋ�ٿ� �޴����� ����� �� �༮���� ������ּ���.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);

    // 0������ �׳� ���� �⺻�̴�.
    SetWindowPos(windowhandle_, nullptr, _pos.ix(), _pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, 0);
}

void GameEngineWindow::Loop(void(*_loopFunc)()) 
{
    MSG msg;
    while (WindowOn)
    {
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            GameEngineTime::GetInst().TimeCheck();
            GameEngineSound::GetInst().SoundUpdate();

            if (nullptr == _loopFunc)
            {
                GameEngineDebug::AssertFalse();
                return;
            }

            _loopFunc();

            // Window�޼����� �ֵ� ���� ���ư���.
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg); // WNDPROC
            }


        }
        else 
        {
            GameEngineTime::GetInst().TimeCheck();
            GameEngineSound::GetInst().SoundUpdate();

            if (nullptr == _loopFunc)
            {
                GameEngineDebug::AssertFalse();
                return;
            }

            _loopFunc();
        }
    }
}

