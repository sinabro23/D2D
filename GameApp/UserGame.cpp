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

TransformData TransData;

void UserGame::Initialize()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	return;
}

void UserGame::Release()
{

}



void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//float4x4 mScale;
	//float4x4 mRot;
	//float4x4 mPos;
	//float4x4 mWorld;

	//// ������Ʈ
	//{
	//	mScale.Scaling(vScale);
	//	mRot.RotationDeg(vRot);
	//	mPos.Translation(vPos);

	//	mWorld = mScale * mRot * mPos;

	//	// Pipe.Setting("World", mWorld);
	//}

	//  ������
	{


		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
}

