#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineCore : public GameEngineObjectBase
{
public:
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

public:
	template<typename UserGameType>
	static void Start()
	{
		UserGameType NewUserGame;

		NewUserGame.Initialize();
		NewUserGame.ResourcesLoad();

		while (NewUserGame.IsOn())
		{
			NewUserGame.GameLoop();
		}

		NewUserGame.Release();
	}

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void GameLoop() = 0;
	virtual void Release() = 0;
};


