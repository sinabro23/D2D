#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer ����Ʈ ������
    : State(nullptr), ViewPort()
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer ����Ʈ �Ҹ���
{
    if (nullptr != State)
    {
        State->Release();
        State = nullptr;
    }
}


void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
    // 	D3D11_RASTERIZER_DESC;
    //    D3D11_FILL_MODE FillMode;
    //    D3D11_CULL_MODE CullMode;
    //    BOOL FrontCounterClockwise;
    //    INT DepthBias;
    //    FLOAT DepthBiasClamp;
    //    FLOAT SlopeScaledDepthBias;
    //    BOOL DepthClipEnable;
    //    BOOL ScissorEnable;
    //    BOOL MultisampleEnable;
    //    BOOL AntialiasedLineEnable;

    if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_Value, &State))
    {
        GameEngineDebug::MsgBoxError("�����Ͷ����� ������ �����߽��ϴ�.");
        return;
    }
}



void GameEngineRasterizer::SettingViewPort()
{
    GameEngineDevice::GetContext()->RSSetViewports(0, &ViewPort);
}

void GameEngineRasterizer::Setting()
{



}