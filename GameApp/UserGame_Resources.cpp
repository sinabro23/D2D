#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
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
		// ���� ��ü�� ������ ũ��� ȸ������ ���� ����
		// ���ý����̽�

		// ���ü��� �ִ� ��ü�� �츮�� ���ϴ� ��� �����ϰ�
		// ��ġ��Ű�� �ν��մϴ�.
		// ���彺���̽�

		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4 * 6);

		{
			// �ո�
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.5f }) };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.5f }) };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.5f }) };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.5f }) };

			RectVertex[4] = { float4::RotateXDegree(RectVertex[0].Postion, 180.0f) };
			RectVertex[5] = { float4::RotateXDegree(RectVertex[1].Postion, 180.0f) };
			RectVertex[6] = { float4::RotateXDegree(RectVertex[2].Postion, 180.0f) };
			RectVertex[7] = { float4::RotateXDegree(RectVertex[3].Postion, 180.0f) };
		}

		{
			RectVertex[8] = { float4::RotateYDegree(RectVertex[0].Postion, 90.0f) };
			RectVertex[9] = { float4::RotateYDegree(RectVertex[1].Postion, 90.0f) };
			RectVertex[10] = { float4::RotateYDegree(RectVertex[2].Postion, 90.0f) };
			RectVertex[11] = { float4::RotateYDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[12] = { float4::RotateYDegree(RectVertex[0].Postion, -90.0f) };
			RectVertex[13] = { float4::RotateYDegree(RectVertex[1].Postion, -90.0f) };
			RectVertex[14] = { float4::RotateYDegree(RectVertex[2].Postion, -90.0f) };
			RectVertex[15] = { float4::RotateYDegree(RectVertex[3].Postion, -90.0f) };
		}

		{
			RectVertex[16] = { float4::RotateXDegree(RectVertex[0].Postion, 90.0f) };
			RectVertex[17] = { float4::RotateXDegree(RectVertex[1].Postion, 90.0f) };
			RectVertex[18] = { float4::RotateXDegree(RectVertex[2].Postion, 90.0f) };
			RectVertex[19] = { float4::RotateXDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[20] = { float4::RotateXDegree(RectVertex[0].Postion, -90.0f) };
			RectVertex[21] = { float4::RotateXDegree(RectVertex[1].Postion, -90.0f) };
			RectVertex[22] = { float4::RotateXDegree(RectVertex[2].Postion, -90.0f) };
			RectVertex[23] = { float4::RotateXDegree(RectVertex[3].Postion, -90.0f) };
		}

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		for (int i = 0; i < 6; i++)
		{
			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 1);
			RectIndex.push_back(i * 4 + 2);

			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 2);
			RectIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
		{
			// 1 0 0 0
			// 0 1 0 0
			// 0 0 1 0
			// 0 0 0 1

			//float4x4 ScaleMat;
			//ScaleMat.Scaling({ 20.0f, 20.0f, 20.0f });

			//float4x4 RotMat;
			//RotMat.RotationDeg({ 0.0f, 0.0f, 0.0F });
			//// RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });

			//float4x4 PosMat;
			//// PosMat.Translation({ 0.0f, 0.0f, 0.0f });
			//PosMat.Translation(BoxPos);

			//float4x4 ViewMat;
			//ViewMat.ViewToLH({ 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });

			//// 

			//// ������ ũ�⸦ -1 1������ ������ ���δ�.
			//// X = -1~1;
			//// Y = -1~1;
			//// Z = 0~1;

			//// ���� 2���� ��������� �ִµ�.
			//// 1. ���ٰ��� �ִ� ������� ��������
			//// 2. ���� �ʴ� ������� ��������

			//// -1~1�� ���� �������� �ٲߴϴ�.



			//float4x4 PerspectiveMat;
			//PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);


			//float4x4 OrthographicMat;
			//OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);


			//// ���Ͷ�?
			//// ������������ �����ϴ� x y
			//// 2 2
			//// 50 40
			//// 2, 2


			//// 51 41
			//// 52, 42


			//// ����� ��ȯ��Ģ�� �������� �ʽ��ϴ�.
			//// ũ���̰���
			//// ũ��
			//// ����
			//// �̵�
			//// ����
			//// �θ�

			//
			//{

			//	// float4 VectorTest = { 0.0f, 0.0f, 100.0f, 2.0f };
			//	float4 VectorTest = { 0.0f, 0.0f, 100.0f, 1.0f };

			//	float4x4 TestMat;

			//	TestMat.vx = { 0.1f, 0.0f , 0.0f , 0.0f };
			//	TestMat.vy = { 0.0f, 0.1f , 0.0f , 0.0f };
			//	TestMat.vz = { 0.0f, 0.0f , 0.1f , 1.0f };
			//	TestMat.vw = { 0.0f, 0.0f , 0.0f , 0.0f };

			//	// �� ������� ���� ����� ������������ z�� �̹� w�� �����Ѱ̴ϴ�.
			//	VectorTest *= TestMat;

			//	int a = 0;

			//}



			//float4x4 WorldMat = ScaleMat * RotMat * PosMat;
			//float4x4 WorldView = WorldMat * ViewMat;

			//float4x4 WorldViewProjectionMat = WorldMat * ViewMat * PerspectiveMat;

			//float4x4 WorldViewOrthographicMat = WorldMat * ViewMat * OrthographicMat;

			//float4 PersPos = _Value;
			//PersPos *= WorldViewProjectionMat;

			//float4 OrthPos = _Value;
			//OrthPos *= WorldViewOrthographicMat;


			float4 PersPos = _Value;
			return PersPos;
		}
		);
	}

	{
		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("TestReasterizer");
		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("BoxRendering");
		//Pipe->SetInputAssembler1();
	}



}
