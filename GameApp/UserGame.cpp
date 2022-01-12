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

	GameEngineSoundManager::GetInst().Initialize();
	return;
}

float RotAngle = 0.0f;

void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectroy SoundDir;
		SoundDir.MoveParent("D2D");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}


	{
		std::vector<float4> RectVertex = std::vector<float4>(4);

		RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
		RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
		RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
		RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

		//RectVertex[4] = RectVertex[0].Rotatefloat2Degree();
		//RectVertex[5] = RectVertex[1]
		//RectVertex[6] = RectVertex[2]
		//RectVertex[7] = RectVertex[3]

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);
	}

	{
		std::vector<int> RectIndex = { 0,1,2, 0,2,3 };

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);
	}

	{
		// �� ���ÿ��� ��ٷ� �־��ְ� ������
		// []


		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				float4 MovePos = { 200.0f, 200.0f };
				float4 Pos = _Value;
				Pos *= 100.0f;
				Pos.RotateZfloat2Degree(RotAngle);
				Pos += MovePos;

				return Pos;
			}
		);
	}

}

void UserGame::Release()
{
	// Resources
	GameEngineIndexBufferManager::Destroy();
	GameEngineVertexShaderManager::Destroy();
	GameEngineVertexBufferManager::Destroy();
	GameEngineTextureManager::Destroy();
	GameEngineSoundManager::Destroy();

	// Base
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();
}

void UserGame::GameLoop()
{

	GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");

	RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();

	// Polygon(GameEngineWindow::GetInst().GetWindowDC(), PolyGon, 4);

	// ���� static
	//static float X = 0.0f;
	//X += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//Rectangle(GameEngineWindow::GetInst().GetWindowDC(), 0 + X, 0, 100 + X, 100);
}