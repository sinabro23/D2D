#include "CbufferHeader.fx"

float4 Texture_VS(float4 pos : POSITION) : SV_POSITION
{
    // pos *= World;
    pos = mul(pos, World);

    return pos;
}

float4 Texture_PS(float4 pos : SV_POSITION) : SV_Target0
{
    pos = mul(pos, World);
    // 결과값에 영향을 미쳤나?

	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}


