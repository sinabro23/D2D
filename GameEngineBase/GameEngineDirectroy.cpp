#include "PreCompile.h"
#include "GameEngineDirectroy.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"
#include <filesystem>

// Static Var
// Static Func

// constructer destructer
GameEngineDirectroy::GameEngineDirectroy()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectroy::GameEngineDirectroy(const GameEngineDirectroy& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectroy::~GameEngineDirectroy()
{
}

GameEngineDirectroy::GameEngineDirectroy(GameEngineDirectroy&& _other) noexcept
{
}

//member Func

std::string GameEngineDirectroy::DirectroyName()
{
	return path_.filename().string();
}

void GameEngineDirectroy::MoveParent()
{
	path_ = path_.parent_path();
}

bool GameEngineDirectroy::IsRoot()
{
	return path_.root_directory() == path_;
}

bool GameEngineDirectroy::MoveParent(const std::string& _DirName)
{
	while (false == IsRoot())
	{
		if (path_.filename().string() == _DirName)
		{
			return true;
		}

		MoveParent();
	}
	return false;
}


bool GameEngineDirectroy::MoveChild(const std::string& _DirName)
{
	path_.append(_DirName);

	if (false == IsExist())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ��η� �̵��߽��ϴ�.");
		return false;
	}

	return true;
}

std::string GameEngineDirectroy::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);
	return NewPath.string();
}


//std::filesystem::directory_iterator�� ����Ͽ� ���丮�� ���� ��� ���� ����
//opendir / readdir �Լ��� ����Ͽ� ���丮�� ���� ��� ���� ����
//std::filesystem::recursive_directory_iterator�� ����Ͽ� ��� ���� ���丮�� ���� ����� �����ɴϴ�

std::vector<GameEngineFile> GameEngineDirectroy::GetAllFile(const std::string& _filter /*= "*"*/)
{
	std::string Filter = "";

	//.�� ���¾ָ� .�� ����
	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}

	Filter += _filter;

	GameEngineString::toupper(Filter);

	std::vector<GameEngineFile> Return;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);

	for (const std::filesystem::directory_entry& File : DirIter)
	{
		std::string Ext = File.path().extension().string();
		GameEngineString::toupper(Ext);

		if (_filter != "*" && Filter != Ext)
		{
			continue;
		}

		Return.push_back(GameEngineFile(File.path()));

	}


	return Return;
}