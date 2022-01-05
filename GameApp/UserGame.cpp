#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



void UserGame::Initialize()
{

	GameEngineSound::GetInst().Initialize();
	return;
}

void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectroy SoundDir;
		SoundDir.MoveParent("D2D");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");


		GameEngineSound::GetInst().LoadSound("Bgm.mp3", SoundDir.PathToPlusFileName("Bgm.mp3"));
	}



	GameEngineSound::GetInst().PlaySoundOneShot("Bgm.mp3");

}

void UserGame::Release()
{
	GameEngineSound::Destroy();
}

void UserGame::GameLoop()
{
	switch (_getch())
	{
	case 'q':
	case 'Q':
		EngineDestroy();
		return;
	default:
		break;
	};
}