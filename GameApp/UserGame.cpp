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

float RotAngle = 0.0f;
float4 BoxPos = { 0.0f, 0.0f, 0.0f };

void UserGame::Release()
{

}

void UserGame::GameLoop()
{
	GameEngineDevice::RenderStart();

	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("BoxRendering");
	Pipe->Rendering();

	// ���׸���

	//GameEngineRenderingPipeLine Pipe;

	//// �Ž�
	//Pipe.SetInputAssembler1("Rect"); // ���ؽ� ����
	//Pipe.SetInputAssembler2("Rect"); // �ε��� ����

	//// ���׸���
	//Pipe.SetVertexShader("TestShader"); // ��� �����Ϸ�??????
	//Pipe.SetRasterizer("TestRasterizer");
	//RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();
	//BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//Pipe.Rendering();


	GameEngineDevice::RenderEnd();
}

