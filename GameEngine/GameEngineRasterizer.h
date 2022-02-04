#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11RasterizerState* State;
	D3D11_VIEWPORT ViewPort;

public:
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth)
	{
		ViewPort.Height = _Height;
		ViewPort.Width = _Width;
		ViewPort.TopLeftX = _TopLeftX;
		ViewPort.TopLeftY = _TopLeftY;
		ViewPort.MinDepth = _MinDepth;
		ViewPort.MaxDepth = _MaxDepth;
	}

public:
	void Create(const D3D11_RASTERIZER_DESC& _Value);

public:
	GameEngineRasterizer(); // default constructer ����Ʈ ������
	~GameEngineRasterizer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SettingViewPort();

	void Setting();
};
