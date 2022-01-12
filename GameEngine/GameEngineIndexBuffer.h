#pragma once
#include <vector>
#include <GameEngineBase/GameEngineObjectNameBase.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineIndexBuffer : public GameEngineObjectNameBase
{
public:	// member Var
	std::vector<int> Indexs;
	// 0 1 3 
	// 0 3 2
	// 0 4 1

public:
	GameEngineIndexBuffer(); // default constructer ����Ʈ ������
	~GameEngineIndexBuffer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

