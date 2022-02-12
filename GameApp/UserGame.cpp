#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



struct TransformData
{
	float4x4 World;
	float4x4 View;
	float4x4 Proj;
};

float4 Pos;
TransformData TransData;

void UserGame::Initialize()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	// cpu�� �����Ϳ� ������۸� �����Ѵ�.
	Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);


	// Pipe->ShaderHelper.SettingConstantBufferLink("TransformData222", TransData);
	// cpu�� �����Ϳ� ������۸� �ѹ� �����Ѵ�.
	// Pipe->ShaderHelper.SettingConstantBufferSet("TransformData", TransData);

	return;
}

void UserGame::Release()
{

}



void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	{
		Pos.x += 0.0001f;
		TransData.World.Translation(Pos);


		// ������ ������������ �ϳ��� ����
		// �̾ȿ� ���������� �����ϰ���?
		GameEngineDevice::RenderStart();

		// �������Ӹ��� ��������� �ϴ°� ����?
		// 
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
}


