#include "PreCompile.h"
#include "GameEngineReasterizer.h"

GameEngineReasterizer::GameEngineReasterizer() // default constructer ����Ʈ ������
{

}

GameEngineReasterizer::~GameEngineReasterizer() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineReasterizer::GameEngineReasterizer(GameEngineReasterizer&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



void GameEngineReasterizer::ReasterizerUpdate(float4& _Pos)
{
	// ���� ���� ���� �༮���� �����µ� ���� �����ֱ� ���ؼ� �׳� ���⼭ �ϰڽ��ϴ�.
	_Pos.x /= _Pos.w;
	_Pos.y /= _Pos.w;
	_Pos.z /= _Pos.w;
	_Pos.w = 1.0f;


	// ���⼭ 2������ �Ǵ� �̴ϴ�.
	_Pos *= ViewPort;

	// _Pos * ViewPort;
}