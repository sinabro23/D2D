#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

class TransformData 
{
	float4 vWorldTranslation;
	float4 vWorldRotation;
	float4 vWorldScaling;

	float4 vLocalTranslation;
	float4 vLocalRotation;
	float4 vLocalScaling;

	float4x4 Scaling;
	float4x4 Rotation;
	float4x4 Translation;
	float4x4 Revolve;
	float4x4 Parent;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
};

// ����̶� 
// ��ġ�� �����ؾ� �Ѵ�. => ���

// ��� ��ġ�� �׷����� �Ѵ�. => ���
// ��� ��ġ���� �ٸ� �ֵ�� �浹�ؾ� �Ѵ� => ���

// ��ġ�� ��Ÿ���� ����̶� ������ ������Ʈ��� �θ��� ���������� �߿��ϴ�.

// ���� :
class GameEngineTransform 
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

protected:
	TransformData TransData_;

	GameEngineTransform* Parent_;
	std::list<GameEngineTransform*> Childs_;

private:
	void SetParent(GameEngineTransform* _Parent);

	void DetachChild(GameEngineTransform* _Child);

};

