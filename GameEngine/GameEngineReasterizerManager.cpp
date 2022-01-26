#include "PreCompile.h"
#include "GameEngineReasterizerManager.h"
#include "GameEngineReasterizer.h"

GameEngineReasterizerManager* GameEngineReasterizerManager::Inst = new GameEngineReasterizerManager();

GameEngineReasterizerManager::GameEngineReasterizerManager() // default constructer ����Ʈ ������
{

}

GameEngineReasterizerManager::~GameEngineReasterizerManager() // default destructer ����Ʈ �Ҹ���
{
	for (const std::pair<std::string, GameEngineReasterizer*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineReasterizerManager::GameEngineReasterizerManager(GameEngineReasterizerManager&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



GameEngineReasterizer* GameEngineReasterizerManager::Create(const std::string& _Name)
{
	GameEngineReasterizer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}


	GameEngineReasterizer* NewRes = new GameEngineReasterizer();
	NewRes->SetName(_Name);

	// �׸��� ���Ұų�?

	ResourcesMap.insert(std::map<std::string, GameEngineReasterizer*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineReasterizer* GameEngineReasterizerManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineReasterizer* GameEngineReasterizerManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineReasterizer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineReasterizer* NewRes = new GameEngineReasterizer();
	NewRes->SetName(_Name);


	ResourcesMap.insert(std::map<std::string, GameEngineReasterizer*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineReasterizer* GameEngineReasterizerManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineReasterizer*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}