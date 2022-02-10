#pragma once
class GameEngineString
{
private:
	GameEngineString(); // default constructer ����Ʈ ������
	virtual ~GameEngineString(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineString(const GameEngineString& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineString(GameEngineString&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineString& operator=(const GameEngineString& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineString& operator=(const GameEngineString&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	static void toupper(std::string& Text);

	static void StringToWString(const std::string& Text, std::wstring& _Out);
};

