#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform() 
{
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	//if (nullptr == _Child)
	//{
	//	GameEngineDebug::
	//}
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent) 
{
	if (nullptr == _Parent)
	{
	}

	if (nullptr != Parent_)
	{
		Parent_->DetachChild(this);
		// ���� �θ𿡰Լ� �������� �ٸ� �θ𿡰Է� �Űܰ��� �ϹǷ�
		// ���� �ڽ��� �θ𿡼��� ������������ �Ѵ�.
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}