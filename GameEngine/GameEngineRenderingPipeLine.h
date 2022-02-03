#pragma once
#include <GameEngineBase/GameEngineMath.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
private:	// member Var
	// IA1
	GameEngineVertexBuffer* VertexBuffer_;
	GameEngineVertexShader* InputLayOutVertexShader_;

	// VS
	GameEngineVertexShader* VertexShader_;

	// IA2
	GameEngineIndexBuffer* IndexBuffer_;
	D3D11_PRIMITIVE_TOPOLOGY Topology_;


	GameEngineRasterizer* Reasterizer_;

public:
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);
	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);
	void SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY Topology_);

	void SetRasterizer(const std::string& _Name);

public:
	void SetMesh();
	void SetMaterial();

public:
	void Rendering();


public:
	GameEngineRenderingPipeLine(); // default constructer ����Ʈ ������
	~GameEngineRenderingPipeLine(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void InputAssembler1();
	void VertexShader();
};

