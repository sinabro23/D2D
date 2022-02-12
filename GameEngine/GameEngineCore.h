#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>

// �з� : 
// �뵵 : 
// ���� : 
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
	virtual void GameLoop() = 0;
	virtual void Release() = 0;

public:
	virtual float4 StartWindowSize() = 0;
	virtual float4 StartWindowPos() = 0;
};

