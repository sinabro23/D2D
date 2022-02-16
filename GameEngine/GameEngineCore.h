#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>
#include "GameEngineLevel.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineLevel;
class GameEngineCore : public GameEngineObjectBase
{
private:
	void EngineInitialize();
	void EngineDestroy();

protected:
	GameEngineCore(); // default constructer ����Ʈ ������
	~GameEngineCore(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	static GameEngineCore* MainCore_;

private:
	static void WindowCreate(GameEngineCore& _RuntimeCore);
	static void Loop();
	static void MainLoop();

public:
	template<typename UserGameType>
	static void Start() 
	{
		GameEngineDebug::LeakCheckOn();

		// �ŷ��� ��.
#ifdef _DEBUG
		// ����׶��� ���� ������̴�.
		new int();
#endif
		UserGameType NewUserGame;
		WindowCreate(NewUserGame);

		NewUserGame.EngineInitialize();
		NewUserGame.ResourcesLoad();
		NewUserGame.Initialize();

		MainCore_ = &NewUserGame;

		Loop();

		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void Release() = 0;

public:
	virtual float4 StartWindowSize() = 0;
	virtual float4 StartWindowPos() = 0;



////////////////////////////////////// Level

public:
	template<typename LevelType>
	static void LevelCreate(const std::string& _Level) 
	{
		if (nullptr != LevelFind(_Level))
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������ 2�� ������� �߽��ϴ�");
			return;
		}

		AllLevel_.insert(std::make_pair(_Level, new LevelType()));
		AllLevel_[_Level]->LevelStart();
	}
	static void LevelChange(const std::string& _Level);
	static GameEngineLevel* LevelFind(const std::string& _Level);

private:
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* CurrentLevel_;
	static std::map<std::string, GameEngineLevel*> AllLevel_;

};

