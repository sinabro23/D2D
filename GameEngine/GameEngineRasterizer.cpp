#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer ����Ʈ ������
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



void GameEngineRasterizer::RasterizerUpdate(float4& _Pos)
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