#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineVertexBuffer;
class GameEngineVertexBufferManager
{
private:
	static GameEngineVertexBufferManager* Inst;

public:
	static GameEngineVertexBufferManager& GetInst()
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
	std::map<std::string, GameEngineVertexBuffer*> ResourcesMap;

public:
	// ���� ����� �ִ�.
	GameEngineVertexBuffer* Create(const std::string& _Name);
	// ���Ͽ��� �ε�
	GameEngineVertexBuffer* Load(const std::string& _Path);
	// 
	GameEngineVertexBuffer* Load(const std::string& _Name, const std::string& _Path);
	// ��Ͽ��� ã�´�.
	GameEngineVertexBuffer* Find(const std::string& _Name);

private:
	GameEngineVertexBufferManager(); // default constructer ����Ʈ ������
	~GameEngineVertexBufferManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexBufferManager(const GameEngineVertexBufferManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexBufferManager(GameEngineVertexBufferManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexBufferManager& operator=(const GameEngineVertexBufferManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexBufferManager& operator=(const GameEngineVertexBufferManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
};

