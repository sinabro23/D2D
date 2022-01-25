#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineReasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	float4x4 ViewPort;

public:
	void SetViewPort(float _ScreenX, float _ScreenY, float _StartX, float _StartY, float _MinZ, float _MaxZ)
	{
		ViewPort.ViewPortCenter(_ScreenX, _ScreenY, _StartX, _StartY, _MinZ, _MaxZ);
	}

public:
	void ReasterizerUpdate(float4& _Pos);


public:
	GameEngineReasterizer(); // default constructer ����Ʈ ������
	~GameEngineReasterizer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineReasterizer(const GameEngineReasterizer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineReasterizer(GameEngineReasterizer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineReasterizer& operator=(const GameEngineReasterizer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineReasterizer& operator=(const GameEngineReasterizer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

