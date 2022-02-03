#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("AR38");
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


	// �̰� �׷��� ī�忡�� �˷��ִ� �̴ϴ�.
	{

		// POSITION�� �ø�ƽ�̶�� �մϴ�.
		// �⺻������ ���� ��ġ�� �ٲ۴�.
		// �ٸ� �������� �ϵ� �Ҽ� ������
		// �⺻������ ������ ���� ��ġ�� �ٲ۴�.
		// +a
		// �� ���� �ִ°��� ��������� ���Գִ°��� ��Ʈ���̴ϴ�.
		std::string ShaderCode =
			"\
			float4 StartVertexShader( float4 pos : POSITION ) : SV_POSITION\n \
			{\n \
				return pos;\n\
			}\n\
			";

		GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create("StartVertexShader", ShaderCode);

		//Ptr->AddInputLayOut("TEXCOORD", 0, 0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		//Ptr->AddInputLayOut("POSTION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		//Ptr->AddInputLayOut("COLOR", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);

	}

	{
		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("TestReasterizer");
		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("BoxRendering");

		// �̷� �⺻���� vertex���� �ִ�.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("StartVertexShader");

		// �� vertex�� �̷��� ��ġ��Ű�ڴ�.
		Pipe->SetVertexShader("StartVertexShader");

		// �� vertex�� 3�� ��� ������ �׸��ڴ�. ������ �ε��� ������ �������
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// �� �׼����̼� ������ ������Ʈ���� ������ ����ǰ� ��� �ʼ��� �ƴϴ�. 
		// vertex�� �� �ɰ��ǵ� �غ� �ϰڴ�. 
		// ��
		// 
		// �濡�� ���Ѵ�� vertex�� �� �ɰ���.
		// �׼����̼� 
		// 
		// �� �� �ɰ� vertex���� �����ϰڴ�.
		// ������ 
		// 
		// ������Ʈ�� ������ ���ο� vertex���� �� ����ڴ�.
		// �ִ� ���ӿ��� �� ���� ��������.

		// �׸������� ��Ȥ�� �� �� ��ġ�� ������� �ȼ����� �����ϰڴ�. 
		// �����Ͷ����Ͷ�����
	}



}
