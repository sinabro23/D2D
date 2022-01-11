#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>


// �з� : 
// �뵵 : 
// ���� : 
class GameEngineVertexShader
{
public:	// member Var
	std::function<float4(const float4& _Vertex)> VertexShaderFunction;

	// virtual float4 VertexShaderFunction(const float4& _Vertex);

public:
	GameEngineVertexShader(); // default constructer ����Ʈ ������
	~GameEngineVertexShader(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

