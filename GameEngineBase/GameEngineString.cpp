#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

GameEngineString::GameEngineString() // default constructer ����Ʈ ������
{

}

GameEngineString::~GameEngineString() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



void GameEngineString::toupper(std::string& Text)
{
	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);
}

void GameEngineString::StringToWString(const std::string& _Text, std::wstring& _Out)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), _Text.size(), nullptr, 0);

	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}

	_Out.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), _Text.size(), &_Out[0], Size);

	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
}