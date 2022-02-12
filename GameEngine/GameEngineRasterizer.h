#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11RasterizerState* State_;
	ID3D11RasterizerState* OldState_;
	D3D11_RASTERIZER_DESC Desc_;
	D3D11_RASTERIZER_DESC WireDesc_;
	D3D11_VIEWPORT ViewPort_;
	D3D11_RECT rects;

	std::vector<D3D11_RECT> ScissorRects_;

	void Clear();

public:
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth)
	{
		ViewPort_.Height = _Height;
		ViewPort_.Width = _Width;
		ViewPort_.TopLeftX = _TopLeftX;
		ViewPort_.TopLeftY = _TopLeftY;
		ViewPort_.MinDepth = _MinDepth;
		ViewPort_.MaxDepth = _MaxDepth;
	}

	void Create(const D3D11_RASTERIZER_DESC& _Value);

	void PushScissorRect(D3D11_RECT _Rect);

	GameEngineRasterizer(); // default constructer ����Ʈ ������
	~GameEngineRasterizer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SettingScissorEnable();

	void SettingViewPort();

	void SwitchState();

	void Setting();
};



