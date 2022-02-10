#pragma once
#include <GameEngine/GameEngineDevice.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRenderingSettingData.h"



// �з� : 
// �뵵 : 
// ���� : 
class GameEngineShader;
class GameEngineConstantBuffer;
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEnginePixelShader;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
private:	// member Var
	// IA1
	GameEngineVertexBuffer* VertexBuffer_;
	// IA1
	GameEngineVertexShader* InputLayOutVertexShader_;
	// VS
	GameEngineVertexShader* VertexShader_;
	// IA2
	GameEngineIndexBuffer* IndexBuffer_;
	// IA2
	D3D11_PRIMITIVE_TOPOLOGY Topology_;
	// RS
	GameEngineRasterizer* Rasterizer_;
	// PS
	GameEnginePixelShader* PixelShader_;
	// OM
	GameEngineRenderTarget* RenderTarget_;

public:
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);

	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);

	void SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY Topology_);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMerger(const std::string& _Name);

	void RenderingPipeLineSetting();

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
	void InputAssembler2();
	void VertexShader();
	void Rasterizer();
	void PixelShader();




	/////////////////////////////////// ���̴� ���� �����͵�
public:
	void ResourcesCheck();

	void ShaderResourcesCheck(GameEngineShader* _Shader);

	std::map<std::string, GameEngineConstantBufferSetting*> ConstantBufferSetting_;

	// void ConstantBufferSetting();
};

