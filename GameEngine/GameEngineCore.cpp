#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineDevice.h"
#include "GameEngineLevel.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

GameEngineCore::GameEngineCore() // default constructer 디폴트 생성자
{

}

GameEngineCore::~GameEngineCore() // default destructer 디폴트 소멸자
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
	for (auto& Level : AllLevel_)
	{
		if (true)
		{
			delete  Level.second;
			Level.second = nullptr;
		}
	}

	GameEngineManagerHelper::ManagerRelease();
	GameEngineTime::Destroy();
	GameEngineDevice::Destroy();
	GameEngineWindow::Destroy();
}

/// <summary>
/// /////////////////////////// static
/// </summary>

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();

	if (nullptr != NextLevel_)
	{
		if (nullptr == CurrentLevel_)
		{
			CurrentLevel_ = NextLevel_;
		}
		else
		{
			CurrentLevel_->LevelChangeEndEvent();
			NextLevel_->LevelChangeStartEvent();
			CurrentLevel_ = NextLevel_;
		}
		GameEngineTime::GetInst().TimeCheckReset();
	}

	if (nullptr == CurrentLevel_)
	{
		GameEngineDebug::MsgBoxError("현재 레벨이 존재하지 않습니다.");
	}

	CurrentLevel_->LevelUpdate(GameEngineTime::GetInst().GetDeltaTime());
	CurrentLevel_->ActorUpdate(GameEngineTime::GetInst().GetDeltaTime());




	// 오브젝트 루프

	//MainCore_->GameLoop();
}

void GameEngineCore::WindowCreate(GameEngineCore& _RuntimeCore)
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", _RuntimeCore.StartWindowSize(), _RuntimeCore.StartWindowPos());

	// 디바이스가 만들어져야 합니다.
	// HWND 윈도우에서 제공하는 3D 라이브러리니까 WINDOW API를 기반으로 처리되어 있습니다.
	GameEngineDevice::GetInst().Initialize();
}

void GameEngineCore::Loop()
{
	GameEngineTime::GetInst().TimeCheckReset();
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}


std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel_;
GameEngineLevel* GameEngineCore::NextLevel_ = nullptr;
GameEngineLevel* GameEngineCore::CurrentLevel_ = nullptr;


GameEngineLevel* GameEngineCore::LevelFind(const std::string& _Level)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Level);
	if (FindIter != AllLevel_.end())
	{
		return FindIter->second;
	}
	return nullptr;
}


void GameEngineCore::LevelChange(const std::string& _Level)
{
	GameEngineLevel* FindLevel = LevelFind(_Level);

	if (nullptr == FindLevel)
	{
		GameEngineDebug::MsgBoxError("Next Level Is Nullptr");
	}

	NextLevel_ = FindLevel;
}