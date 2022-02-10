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



void UserGame::Initialize()
{

	return;
}

void UserGame::Release()
{

}

float4 vPos = { 0.0f, 0.0f , 0.0f };
float4 vRot = { 0.0f, 0.0f , 0.0f };
float4 vScale = { 1.0f, 1.0f , 1.0f };

void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("BoxRendering");
	float4x4 mScale;
	float4x4 mRot;
	float4x4 mPos;
	float4x4 mWorld;

	// ������Ʈ
	{
		mScale.Scaling(vScale);
		mRot.RotationDeg(vRot);
		mPos.Translation(vPos);

		mWorld = mScale * mRot * mPos;

		// Pipe.Setting("World", mWorld);
	}

	//  ������
	{
		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
}

