#pragma once
#include "FMOD/fmod.hpp"
#include <list>
#include <map>
#include <string>

#pragma comment(lib, "fmod_vc.lib") // Release�� ����� �ڵ�����

// �̷� ���� �̹��� ���ҽ� ��Ʈ �츮�� �ε��ϰų� 
// �������� �����ų� �ʹ� �����Ƽ� ����ϴ� ���̺귯����

// �ܰ谡 ������ ����.
// �̴ϼȶ����� �Լ��� ã�´�. <= ��κ� �� ���̺귯�� ��ü �Ѱ� �ý��ۿ� ��ü�� �����Ѵ�.
// �������Լ�����.
// �ε� �Լ��� ã�ƾ��Ѵ�.
// �״����� �������̳� ����Լ��� ã�ƾ� �մϴ�.

// �з� :
// �뵵 :
// ���� :
class GameEngineSoundFile;
class GameEngineSoundPlayer;
class GameEngineSound
{

private:
	static GameEngineSound* Inst;

public:
	static GameEngineSound& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	friend GameEngineSoundFile;
	friend GameEngineSoundPlayer;

private:	// member Var
	FMOD::System* soundSystem_; // Fmod�� �������ִ� �������̽�
	// ���������ϳ��ϳ��� �ƴ϶�
	// fmod�� ����Ҽ� �ִ��� Ȯ�����ְ� ���带 �ε��Ҽ� �ְ� ���ִ� �⺻ �������̽��Դϴ�.
	// �̳༮�� ���� ����� ��������� �ִ� ȯ���̾�� ���带 ����Ҽ� �ֽ��ϴ�.
	std::map<std::string, GameEngineSoundFile*> allLoadSound_;

	std::list<GameEngineSoundPlayer*> allSoundPlayer_;

private:
	GameEngineSoundFile* FindSound(const std::string& _name);

public:
	void Initialize();

	void LoadSound(const std::string& _path);

	void LoadSound(const std::string& _name, const std::string& _path);
	void PlaySoundOneShot(const std::string& _name);
	GameEngineSoundPlayer* CreateSoundPlayer();

public:
	void SoundUpdate();

private:
	GameEngineSound(); // default constructer ����Ʈ ������
	~GameEngineSound(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineSound(const GameEngineSound& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSound(GameEngineSound&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineSound& operator=(const GameEngineSound& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSound& operator=(const GameEngineSound&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
};

