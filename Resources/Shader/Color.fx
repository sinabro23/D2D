#include "CbufferHeader.fx"
// b32 ���� �����ߴ��ɷ� �ƴµ�
// �׳� �������� ���ô�.

// 512����Ʈ �� �ִ��ϰ̴ϴ�.



float4 Color_VS(float4 pos : POSITION) : SV_POSITION
{
    // pos *= World;
    pos = mul(pos, World);

    return pos;
}


float4 Color_PS(float4 pos : SV_POSITION) : SV_Target0
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}


