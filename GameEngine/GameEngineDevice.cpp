#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineWindow.h"
#include "GameEngineTextureManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineRenderTarget.h"

GameEngineDevice* GameEngineDevice::Inst = new GameEngineDevice();

GameEngineRenderTarget* GameEngineDevice::BackBufferTarget_ = nullptr;
ID3D11Device* GameEngineDevice::Device_ = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context_ = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain_ = nullptr;

ID3D11Device* GameEngineDevice::GetDevice()
{
	return Device_;
}

ID3D11DeviceContext* GameEngineDevice::GetContext()
{
	return Context_;
}

GameEngineDevice::GameEngineDevice() // default constructer 디폴트 생성자
{

}

GameEngineDevice::~GameEngineDevice() // default destructer 디폴트 소멸자
{
	if (nullptr != SwapChain_)
	{
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}

	if (nullptr != Device_)
	{
		Device_->Release();
		Device_ = nullptr;
	}

	if (nullptr != Context_)
	{
		Context_->Release();
		Context_ = nullptr;
	}
}

void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetInst().GetWindowHWND())
	{
		GameEngineDebug::MsgBoxError("Window Hwnd ERROR");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 님이 사용하려는 다이렉트 버전이 몇인가요?
	// 다이렉트 11 사용합니다.
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// D3D_FEATURE_LEVEL eLVArr[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0;

	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE

	if (
		S_OK != D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			iFlag,
			nullptr, // eLVArr
			0,
			D3D11_SDK_VERSION,
			&Device_, // 디바이스 반환
			&eLV,
			&Context_) // 컨텍스트 반환
		)
	{
		GameEngineDebug::MsgBoxError("D3D11 Create Device ERROR");
	}

	if (eLV != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		GameEngineDebug::MsgBoxError("D3D11 Not FEATURE LEVEL 11 ERROR");
	}

	CreateSwapChain(); // 디바이스와 컨텍스트 만들었으니 스왑체인 만들기
}

void GameEngineDevice::CreateSwapChain()
{
	if (0 >= GameEngineWindow::GetInst().GetSize().x &&
		0 >= GameEngineWindow::GetInst().GetSize().y)
	{
		GameEngineDebug::MsgBoxError("Screen Size Zero");
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize();

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, }; // DXGI_SWAP_CHAIN_DESC 스왑체인의 정보를 저장하기 위한 구조체

	// 그래픽카드에 버퍼는 들어있어야 겠죠.
	ScInfo.BufferDesc.Width = ScreenSize.uix(); 
	ScInfo.BufferDesc.Height = ScreenSize.uiy();

	// 모니터에 간섭해서 
	// 1초에
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	// 60프레임 백버퍼를 스왑해라.
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 화면에 띄우기 위해서는 그런 용도로 만든다는걸 알려줘야 하는데
	// 만들려는 스왑체인의 버퍼의 용도. 렌더타겟과 쉐이더를 넣기위함
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	ScInfo.SampleDesc.Quality = 0; //샘플링?
	ScInfo.SampleDesc.Count = 1;

	ScInfo.OutputWindow = GameEngineWindow::GetInst().GetWindowHWND();

	ScInfo.BufferCount = 2; // 더블버퍼링을 위한 2개의 버퍼

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; // 스왑하는 방법

	// 전체화면 모드 가능
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 전체화면 안함.
	ScInfo.Windowed = true;

	// 그래픽카드의 화면출력에 관련된 리소스에 관여할수 있는 
	// 기능들의 포인터를 얻어오고
	// 그 기능들을 통해서 백버퍼의 텍스처를 직업 얻어올 것이다.

	// ID3D11Device* != IDXGIDevice;
	// 그래픽카드의 메모리에 관리자를 접근한다..
	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (nullptr == pD)
	{
		GameEngineDebug::MsgBoxError("IDXGIDevice null");
	}

	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (nullptr == pA)
	{
		GameEngineDebug::MsgBoxError("IDXGIAdapter null");
	}

	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (nullptr == pF)
	{
		GameEngineDebug::MsgBoxError("IDXGIFactory null");
	}

	if (S_OK != pF->CreateSwapChain(Device_, &ScInfo, &SwapChain_))
	{
		GameEngineDebug::MsgBoxError("SwapChain Create Error");
	}

	pF->Release();
	pA->Release();
	pD->Release();

	ID3D11Texture2D* BackBufferTexture = nullptr;
	// 스왑체인에 있는 백버퍼(원본은 텍스쳐형식임)를 BackBufferTexture로 가져옴.
	if (S_OK != SwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture)))
	{
		GameEngineDebug::MsgBoxError("SwapChain Texture Error");
	}

	// BackBufferTexture는 스왑체인의 백버퍼를 가리키고 있음.
	GameEngineTextureManager::GetInst().Create("BackBuffer", BackBufferTexture); 	// 이미 백버퍼 만들어졌지만 관리하기위해 매니저에 넣어주는거구나
	
	BackBufferTarget_ = GameEngineRenderTargetManager::GetInst().Create("BackBuffer", "BackBuffer", float4::BLUE);
}

void GameEngineDevice::RenderStart()
{
	// BackBufferTarget_ <= 여기에 그린 녀석만 나와.
	// 지우고
	BackBufferTarget_->Clear();
	// 세팅하고
	BackBufferTarget_->Setting();
}


void GameEngineDevice::RenderEnd()
{
	// 화면에 그려라 인데.
	HRESULT Result = SwapChain_->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		int a = 0;
	}

	// 화면에 뿌려라
	// BackBufferTarget_;
}