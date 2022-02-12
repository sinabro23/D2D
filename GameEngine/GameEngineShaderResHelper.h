#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "GameEngineRenderingSettingData.h"
#include "GameEngine/GameEngineShader.h"



class GameEngineShader;
class GameEngineConstantBuffer;
// ���� :
class GameEngineShaderResHelper
{
	/////////////////////////////////// ���̴� ���� �����͵�

public:
	// constrcuter destructer
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	// delete Function
	GameEngineShaderResHelper(const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper(GameEngineShaderResHelper&& _Other) noexcept = delete;
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper& operator=(GameEngineShaderResHelper&& _Other) noexcept = delete;

	void ShaderResourcesCheck(GameEngineShader* _Shader);

	void Setting();

	// �� �ּҰ��� ���������� ��� �������ִ� ��带 ���Ѵ�.
	// �ѹ� �������ָ� �־��� �ּҰ��� ��ġ�� �ı��Ǳ��������� �����е��� �Ű澵 �ʿ䰡 ����.

	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data) 
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllSettingData_.find(_SettingName);

		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		SettingData->Mode_ = SettingMode::Link;
		SettingData->SettingDataSize_ = sizeof(_Data);
		SettingData->SettingData_ = reinterpret_cast<char*>(&_Data);
	}

	// �����Ҵ��� �ؼ� ���� ũ���� ���纻�� ����� ���ϴ�.
	// �ѹ� �������ָ� �������� ������ ������ �����Ǵ°̴ϴ�.
	template<typename T>
	void SettingConstantBufferSet(const std::string& _SettingName, const T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllSettingData_.find(_SettingName);

		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		// ���ʼ����̶�� �����ش�.
		//if (SettingData->Mode_ == SettingMode::MAX)
		//{
		//	SettingData->Clear();
		//}

		SettingData->Mode_ = SettingMode::Set;
		SettingData->SettingDataSize_ = sizeof(_Data);

		if (nullptr == SettingData->SettingData_)
		{
			SettingData->SettingData_ = new char[sizeof(_Data)];
		}

		memcpy_s(SettingData->SettingData_, sizeof(_Data), &_Data, sizeof(_Data));
	}

protected:

private:
	std::map<std::string, GameEngineConstantBufferSetting*> AllSettingData_;


};

