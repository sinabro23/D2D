#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineObjectBase
{
private:	// member Var
	// true��� �ϴ¼��� �޸������� �ı��ɰ̴ϴ�.
	bool isDeath_; // �״±���� �ƴմϴ�. �׾����� Ȯ���Ҽ� �ִ±��
	bool isUpdate_; // �̰� ������Ʈ�Ǵ� ����� �ƴϰ� ������Ʈ�� �ؾ�
	bool isDebug_; // ����� ��� �̰� true�� �س��� f9 �ɾ� ������ 
	GameEngineObjectBase* parent_;

public:
	bool IsNull()
	{
		return nullptr == this;
	}

	void SetParent(GameEngineObjectBase* _parent)
	{
		parent_ = _parent;
	}

public:
	bool IsDeath()
	{
		if (nullptr == parent_)
		{
			return isDeath_;
		}

		return true == isDeath_ || parent_->isDeath_;
	}

	bool IsOn()
	{
		if (nullptr == parent_)
		{
			return false == IsDeath() && isUpdate_;
		}

		return false == IsDeath() &&  // ���� ���׾���
			true == isUpdate_ &&  // ���� �����ְ�
			parent_->isUpdate_; // �θ� �����־��
	}


	void Death()
	{
		isDeath_ = true;
	}

	void On()
	{
		isUpdate_ = true;
	}

	void Off()
	{
		isUpdate_ = false;
	}

	void DebugOn()
	{
		isDebug_ = true;
	}

	void DebugOff()
	{
		isDebug_ = false;
	}

	void IsDebugCheck()
	{
		if (true == isDebug_)
		{
			int a = 0;
		}
	}

public:
	GameEngineObjectBase(); // default constructer ����Ʈ ������
	virtual ~GameEngineObjectBase(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineObjectBase(const GameEngineObjectBase& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};
