#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineDirectXDevice.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

GameEngineCore::GameEngineCore() // default constructer ����Ʈ ������
{

}

GameEngineCore::~GameEngineCore() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{


}

/// <summary>
/// /////////////////////////// member
/// </summary>

void GameEngineCore::EngineInitialize()
{
	GameEngineSoundManager::GetInst().Initialize();
}


void GameEngineCore::EngineDestroy()
{
	GameEngineManagerHelper::ManagerRelase();
	GameEngineTime::Destroy();
	GameEngineDirectXDevice::Destroy();
	GameEngineWindow::Destroy();
}

/// <summary>
/// /////////////////////////// static
/// </summary>

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();
	MainCore_->GameLoop();
}

void GameEngineCore::WindowCreate()
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", { 1280, 720 }, { 0, 0 });

	// ����̽��� ��������� �մϴ�.
	// HWND �����쿡�� �����ϴ� 3D ���̺귯���ϱ� WINDOW API�� ������� ó���Ǿ� �ֽ��ϴ�.
	GameEngineDirectXDevice::GetInst().Initialize();
}

void GameEngineCore::Loop()
{
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}
