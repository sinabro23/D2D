#pragma once

// ���� : 
class GameEngineReasterizer;
class GameEngineReasterizerManager
{
private:
	static GameEngineReasterizerManager* Inst;

public:
	static GameEngineReasterizerManager& GetInst()
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

private:	// member Var
	std::map<std::string, GameEngineReasterizer*> ResourcesMap;

public:
	// ���� ����� �ִ�.
	GameEngineReasterizer* Create(const std::string& _Name);
	// ���Ͽ��� �ε�
	GameEngineReasterizer* Load(const std::string& _Path);
	// �̸� ���� ����
	GameEngineReasterizer* Load(const std::string& _Name, const std::string& _Path);
	// ��Ͽ��� ã�´�.
	GameEngineReasterizer* Find(const std::string& _Name);

private:
	GameEngineReasterizerManager(); // default constructer ����Ʈ ������
	~GameEngineReasterizerManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineReasterizerManager(const GameEngineReasterizerManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineReasterizerManager(GameEngineReasterizerManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineReasterizerManager& operator=(const GameEngineReasterizerManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineReasterizerManager& operator=(const GameEngineReasterizerManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
};




