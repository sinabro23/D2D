#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"
#include "UserGame_Resources_Shader.h"


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

	AppShaderLoad();

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
			RectVertex[1] = {float4({ 0.5f, 0.5f, 0.5f }) };
			RectVertex[2] = {float4({ 0.5f, -0.5f, 0.5f }) };
			RectVertex[3] = {float4({ -0.5f, -0.5f, 0.5f }) };

			RectVertex[4] = { float4::RotateXDegree(RectVertex[0].Postion, 180.0f) };
			RectVertex[5] = { float4::RotateXDegree(RectVertex[1].Postion, 180.0f) };
			RectVertex[6] = { float4::RotateXDegree(RectVertex[2].Postion, 180.0f) };
			RectVertex[7] = { float4::RotateXDegree(RectVertex[3].Postion, 180.0f) };
		}

		{
			RectVertex[8] =  {float4::RotateYDegree(RectVertex[0].Postion, 90.0f)};
			RectVertex[9] =  {float4::RotateYDegree(RectVertex[1].Postion, 90.0f)};
			RectVertex[10] = { float4::RotateYDegree(RectVertex[2].Postion, 90.0f)};
			RectVertex[11] = { float4::RotateYDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[12] = {float4::RotateYDegree(RectVertex[0].Postion, -90.0f)};
			RectVertex[13] = {float4::RotateYDegree(RectVertex[1].Postion, -90.0f)};
			RectVertex[14] = {float4::RotateYDegree(RectVertex[2].Postion, -90.0f)};
			RectVertex[15] = {float4::RotateYDegree(RectVertex[3].Postion, -90.0f)};
		}

		{
			RectVertex[16] = {float4::RotateXDegree(RectVertex[0].Postion, 90.0f)};
			RectVertex[17] = {float4::RotateXDegree(RectVertex[1].Postion, 90.0f)};
			RectVertex[18] = {float4::RotateXDegree(RectVertex[2].Postion, 90.0f)};
			RectVertex[19] = {float4::RotateXDegree(RectVertex[3].Postion, 90.0f)};

			RectVertex[20] = {float4::RotateXDegree(RectVertex[0].Postion, -90.0f)};
			RectVertex[21] = {float4::RotateXDegree(RectVertex[1].Postion, -90.0f)};
			RectVertex[22] = {float4::RotateXDegree(RectVertex[2].Postion, -90.0f)};
			RectVertex[23] = { float4::RotateXDegree(RectVertex[3].Postion, -90.0f) };
		}

		GameEngineVertexBufferManager::GetInst().Create("Box", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
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

		GameEngineIndexBufferManager::GetInst().Create("Box", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}



	{
		// ���� ��ü�� ������ ũ��� ȸ������ ���� ����
		// ���ý����̽�

		// ���ü��� �ִ� ��ü�� �츮�� ���ϴ� ��� �����ϰ�
		// ��ġ��Ű�� �ν��մϴ�.
		// ���彺���̽�

		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		{
			// �ո�
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }) };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }) };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }) };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }) };
		}

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		// ���� ��ü�� ������ ũ��� ȸ������ ���� ����
		// ���ý����̽�

		// ���ü��� �ִ� ��ü�� �츮�� ���ϴ� ��� �����ϰ�
		// ��ġ��Ű�� �ν��մϴ�.
		// ���彺���̽�

		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		{
			// �ո�
			RectVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }) };
			RectVertex[1] = { float4({ 1.0f, 1.0f, 0.0f }) };
			RectVertex[2] = { float4({ 1.0f, -1.0f, 0.0f }) };
			RectVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }) };
		}

		GameEngineVertexBufferManager::GetInst().Create("FullRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("FullRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}



	{
		D3D11_RASTERIZER_DESC Info = { D3D11_FILL_MODE::D3D11_FILL_SOLID, };

		Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		// �����Ǳ׷���
		// Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// �ð�ݴ�������� �׷����͵��� �׷���
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		Info.AntialiasedLineEnable = true;
		Info.MultisampleEnable = true;

		//// ȭ�� �ٱ��� ���� ����� �߶󳽴�.
		// Info.FrontCounterClockwise = true;
		//Info.ScissorEnable = true;
		//Info.SlopeScaledDepthBias = 0;

		//// ���̰����� ���� �����Ұ̴ϴ�.
		//// ���̹��۸� �����ϰ� ���� �մϴ�.
		//Info.DepthBias = 0;
		//Info.DepthBiasClamp = 0;
		//Info.DepthClipEnable = FALSE;
		//Info.MultisampleEnable = TRUE;

		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("ColorRendering");

		// �̷� �⺻���� vertex���� �ִ�.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");

		// �� vertex�� �̷��� ��ġ��Ű�ڴ�.
		Pipe->SetVertexShader("Color_VS");

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
		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("Color_PS");
	}



}
