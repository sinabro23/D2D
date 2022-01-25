#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineReasterizerManager.h"


#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineReasterizer.h"


#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer ����Ʈ ������
	: VertexBuffer_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: VertexBuffer_(_other.VertexBuffer_)
	, VertexShader_(_other.VertexShader_)
	, IndexBuffer_(_other.IndexBuffer_)
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Reasterizer_ = GameEngineReasterizerManager::GetInst().Find(_Name);

	if (nullptr == Reasterizer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �����Ͷ����� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}


void GameEngineRenderingPipeLine::Rendering()
{
	// input����� �ܰ�
	std::vector<float4> CopyVertex;
	{
		CopyVertex = VertexBuffer_->GetVertexs();
	}

	{
		for (size_t i = 0; i < CopyVertex.size(); i++)
		{
			CopyVertex[i] = VertexShader_->VertexShaderFunction(CopyVertex[i]);
		}
	}

	// Reasterizer_)

	std::vector<std::vector<float4>> TriVector;
	// �׸���.
	{
		const std::vector<int>& Index = IndexBuffer_->Indexs;


		TriVector.resize(Index.size() / 3);


		for (size_t TriCount = 0; TriCount < Index.size() / 3; TriCount++)
		{
			TriVector[TriCount].resize(3);

			int CurIndex0 = Index[(TriCount * 3) + 0];
			int CurIndex1 = Index[(TriCount * 3) + 1];
			int CurIndex2 = Index[(TriCount * 3) + 2];

			TriVector[TriCount][0] = CopyVertex[CurIndex0];
			TriVector[TriCount][1] = CopyVertex[CurIndex1];
			TriVector[TriCount][2] = CopyVertex[CurIndex2];
		}
	}

	for (size_t Tri = 0; Tri < TriVector.size(); Tri++)
	{
		for (size_t i = 0; i < TriVector[Tri].size(); i++)
		{
			Reasterizer_->ReasterizerUpdate(TriVector[Tri][i]);
		}
	}

	for (size_t Tri = 0; Tri < TriVector.size(); Tri++)
	{

		POINT ArrTri[3];

		ArrTri[0] = TriVector[Tri][0].GetWindowPoint();
		ArrTri[1] = TriVector[Tri][1].GetWindowPoint();
		ArrTri[2] = TriVector[Tri][2].GetWindowPoint();

		Polygon(GameEngineWindow::GetInst().GetWindowDC(), &ArrTri[0], 3);
	}


	// Polygon(GameEngineWindow::GetInst().GetWindowDC(), &ArrTri[0], 3);
}