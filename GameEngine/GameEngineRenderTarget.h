#pragma once
#include "GameEngineDirectXDevice.h"

class GameEngineTexture;
class GameEngineRenderTarget : public GameEngineObjectNameBase
{
private:	// member Var
	// �ؽ�ó���Լ� �������� �̴ϴ�.
	std::vector<GameEngineTexture*> Textures_;
	// std::vector<D3D11_VIEWPORT> ViewPort_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;

	std::vector<float4> ClearColor_;

public:
	void Clear();

	// -1�̸� ���δ� �����϶�� �ǹ̰� �˴ϴ�.
	// 0~n�� �� �ε��� 1���� �����϶�� �ǹ̰� �˴ϴ�.
	void Setting(int _Index = -1);

public:
	void Create(const std::string _TextureName, float4 _ClearColor);

public:
	GameEngineRenderTarget(); // default constructer ����Ʈ ������
	~GameEngineRenderTarget(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

};

