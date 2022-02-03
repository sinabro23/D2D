#pragma once
#include <vector>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineIndexBuffer : public GameEngineObjectNameBase
{
public:	// member Var
	// �����ϸ� �����ִ� ������
	ID3D11Buffer* Buffer_;
	// ������ ������. ũ�� ������
	D3D11_BUFFER_DESC BufferData_;

	// ���� �ʱⰪ ����
	D3D11_SUBRESOURCE_DATA ResData_;

	DXGI_FORMAT Format_;
	UINT Offset_;

public:
	GameEngineIndexBuffer(); // default constructer ����Ʈ ������
	~GameEngineIndexBuffer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Create(const std::vector<UINT>& _Datas, D3D11_USAGE _Usage);
	void Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage);

	void Setting();
};

