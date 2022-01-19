#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float DegreeToRadian;
	static const float RadianToDegree;
};

class float4x4;
class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

public:
	// 1 0 0 0 
	// 0 1 0 0 
	// 0 0 1 0
	// 0 0 0 1 

	static float4 Cross3D(float4 _Left, float4 _Right)
	{
		return DirectX::XMVector3Cross(_Left.DirectVector, _Right.DirectVector);
	}

	static float Dot3D(float4 _Left, float4 _Right)
	{
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// ������
	static float Dot3DToLen(float4 _Left, float4 _Right)
	{
		_Right.Normalize3D();
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// �ڻ���
	static float Dot3DToCos(float4 _Left, float4 _Right)
	{
		_Left.Normalize3D();
		_Right.Normalize3D();
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	static float Dot3DToCosAngle(float4 _Left, float4 _Right)
	{
		// 1 / 3;
		// 0.9999999999 / 3
		// 0.9999999999 / 3

		// (1 * 2) = 2
		//  / 2
		// ���Լ�
		// cost(1) = ???
		// ??? => 1
		return acos(Dot3DToCos(_Left, _Right));
	}





	static float4 RotateYDegree(float4 _OriginVector, float _Degree)
	{
		return RotateYRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateYRadian(float4 _OriginVector, float _Radian);

	static float4 RotateXDegree(float4 _OriginVector, float _Degree)
	{
		return RotateXRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateXRadian(float4 _OriginVector, float _Radian);

	static float4 RotateZDegree(float4 _OriginVector, float _Degree)
	{
		return RotateZRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateZRadian(float4 _OriginVector, float _Radian);

	static float4 DirZDegree(float _Degree)
	{
		return DirZRadian(_Degree * GameEngineMath::DegreeToRadian);
	}

	// 0�� {1, 0} �϶��� ���͸� ȸ����Ű�� �����ΰ̴ϴ�.
	static float4 DirZRadian(float _Radian);

public:
	// unnamed union�� �����ϸ� 
	// ������ �޸𸮸� ������ union ������� �������ش�.
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		DirectX::XMFLOAT3 DxXmfloat3;
		DirectX::XMFLOAT4 DxXmfloat4;

		DirectX::XMVECTOR DirectVector;

		// �Ǽ��� �⺻������ 00000000 00000000 00000000 00000000
	};

	float4 operator+(const float4 _value) const
	{
		return DirectX::XMVectorAdd(DirectVector, _value.DirectVector);
	}

	float4 operator-() const
	{
		return DirectX::XMVectorNegate(DirectVector);
	}


	float4 operator-(const float4 _value) const
	{
		return DirectX::XMVectorSubtract(DirectVector, _value.DirectVector);
	}

	float4 operator*(const float _value) const
	{
		float4 CalVector = { _value , _value , _value , 1.0f };
		return DirectX::XMVectorMultiply(DirectVector, CalVector.DirectVector);
	}

	float4 operator*(const float4x4& _Value) const;
	float4& operator*=(const float4x4& _Value);

	float4 operator*(const float4 _value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, _value.DirectVector);
	}

	float4 operator/(const float4 _value) const
	{
		return DirectX::XMVectorDivide(DirectVector, _value.DirectVector);
	}


	float4& operator+=(const float4 _value)
	{
		DirectVector = DirectX::XMVectorAdd(DirectVector, _value.DirectVector);
		return *this;
	}

	float4& operator-=(const float4 _value)
	{
		DirectVector = DirectX::XMVectorSubtract(DirectVector, _value.DirectVector);
		return *this;
	}

	float4& operator*=(const float4 _value)
	{
		DirectVector = DirectX::XMVectorMultiply(DirectVector, _value.DirectVector);
		return *this;
	}

	float4& operator*=(const float _Value)
	{
		float4 Value = float4(_Value, _Value, _Value, 1.0f);
		DirectVector = DirectX::XMVectorMultiply(DirectVector, Value.DirectVector);
		return *this;
	}


	float4& operator/=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorDivide(DirectVector, _Value.DirectVector);
		return *this;
	}

	// ���Կ�����
	float4& operator=(const float4& _value)
	{
		DirectVector = DirectX::XMVectorSet(_value.x, _value.y, _value.z, _value.w);
		return *this;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}


	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float4 halffloat4() const
	{
		return { hx(), hy(), hz() };
	}

	int ihx() const
	{
		return static_cast<int>(hx());
	}

	int ihy() const
	{
		return static_cast<int>(hy());
	}

	int ihz() const
	{
		return static_cast<int>(hz());
	}

	float Len3D()
	{
		float4 Len = DirectX::XMVector3Length(DirectVector);
		return Len.x;
	}

	float4 NormalizeReturn3D() const
	{
		return DirectX::XMVector3Normalize(DirectVector);
	}

	void Normalize3D()
	{
		DirectVector = DirectX::XMVector3Normalize(DirectVector);
	}

	POINT GetWindowPoint()
	{
		return { ix(), iy() };
	}

	void RotateXDegree(float _Deg)
	{
		*this = RotateXDegree(*this, _Deg);
		return;
	}

	void RotateYDegree(float _Deg)
	{
		*this = RotateYDegree(*this, _Deg);
		return;
	}

	void RotateZDegree(float _Deg)
	{
		*this = RotateZDegree(*this, _Deg);
		return;
	}


public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{
	}

	// ����Ʈ �Ķ����
	// ���� ������ �ִ� ���ڿ� ������� �־
	// ���� ���ڸ� �־����� �ʾ������� 
	float4(float _x, float _y, float _z, float _w = 1.0f)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	float4(DirectX::XMVECTOR _value)
		: DirectVector(_value)
	{
	}

	~float4() {

	}

public:		// delete constructer
	float4(const float4& _value)
		: x(_value.x), y(_value.y), z(_value.z), w(_value.w)
	{

	}

};

class int4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			__int64 HighValue;
			__int64 LowValue;
		};
	};
};


class Figure
{
public:
	float4 pos_;
	float4 size_;

public:
	float Left()
	{
		return pos_.x - size_.hx();
	}

	float Right()
	{
		return pos_.x + size_.hx();
	}

	float Top()
	{
		return pos_.y - size_.hy();
	}

	float Bot()
	{
		return pos_.y + size_.hx();
	}

	int iLeft()
	{
		return pos_.ix() - size_.ihx();
	}

	int iRight()
	{
		return pos_.ix() + size_.ihx();
	}

	int iTop()
	{
		return pos_.iy() - size_.ihy();
	}

	int iBot()
	{
		return pos_.iy() + size_.ihy();
	}

	float4 LeftTopfloat4()
	{
		return { Left(), Top() };
	}

	float4 RightTopfloat4()
	{
		return { Right(), Top() };
	}

	float4 LeftBotfloat4()
	{
		return { Left(), Bot() };
	}

	float4 RightBotfloat4()
	{
		return { Right(), Bot() };
	}


public:
	Figure(float4 _Pos, float4 _Size)
		: pos_(_Pos), size_(_Size)
	{

	}
};

class float4x4
{
public:
	union
	{
		float Arr2D[4][4];
		struct
		{
			float4 vx;
			float4 vy;
			float4 vz;
			float4 vw;
		};

		float Arr1D[4 * 4];
		// �Ǽ��� �⺻������ 00000000 00000000 00000000 00000000

		DirectX::XMFLOAT4X4 DxXmfloat4x4;
		DirectX::XMMATRIX DirectMatrix;
	};

public:
	float4x4()
		: DirectMatrix(DirectX::XMMatrixIdentity())
	{

	}

	float4x4(const float4x4& _value)
		: DirectMatrix(_value.DirectMatrix)
	{

	}

	float4x4(const DirectX::XMMATRIX& _value)
		: DirectMatrix(_value)
	{

	}

	~float4x4()
	{

	}

	void Scaling(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value.DirectVector);
	}

	void Translation(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);
	}

	void RotationDeg(const float4& _Value)
	{
		RotationRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationXDeg(const float& _Value)
	{
		RotationXRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationYDeg(const float& _Value)
	{
		RotationYRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationZDeg(const float& _Value)
	{
		RotationZRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationRad(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Value.DirectVector);
	}

	void RotationXRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationX(_Value);
	}

	void RotationYRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationY(_Value);
	}

	void RotationZRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationZ(_Value);
	}

	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}

	void Transpose()
	{
		// 1 0 0 0
		// 0 1 0 0
		// 0 0 1 0
		// 1 0 0 1


		DirectMatrix = DirectX::XMMatrixTranspose(DirectMatrix);
	}

	void ViewAt(const float4& _EyePos, const float4& _EyeFocus, const float4& _EyeUp)
	{
		// 1 0 0 0
		// 0 1 0 0
		// 0 0 1 0
		// 0 0 0 1

		// ������ ���� �ʿ��ϴ�. 

		//float4 ZPivot = _EyeFocus - _EyePos;
		//ZPivot.Normalize3D();
		//float4 EyeUp = _EyeUp.NormalizeReturn3D();
		//float4 XPivot = float4::Cross3D(EyeUp, ZPivot);
		//XPivot.Normalize3D();
		//float4 YPivot = float4::Cross3D(ZPivot, XPivot);
		//YPivot.Normalize3D();

		//float4 NegEyePosition = -_EyePos;

		//float D0 = float4::Dot3D(XPivot, NegEyePosition);
		//float D1 = float4::Dot3D(YPivot, NegEyePosition);
		//float D2 = float4::Dot3D(ZPivot, NegEyePosition);

		//XPivot;
		//YPivot;
		//ZPivot;

		//float4x4 VieMat;

		//VieMat.vx = float4(XPivot.x, XPivot.y, XPivot.z, D0);
		//VieMat.vy = float4(YPivot.x, YPivot.y, YPivot.z, D1);
		//VieMat.vz = float4(ZPivot.x, ZPivot.y, ZPivot.z, D2);
		//VieMat.vw = { 0.0f, 0.0f ,0.0f , 1.0f};
		//VieMat.Transpose();

		// VieMat.tRA

		// cos -sin
		// sin cos


		// ������� ���� �ٶ󺸴� ����� ������ �ǰ� ��� ��ü�� ������ �ִ� ���.

		// float4x4 Mat;



		/*
		XMVECTOR EyeDirection = XMVectorSubtract(FocusPosition, EyePosition);

		assert(!XMVector3Equal(EyeDirection, XMVectorZero()));
		assert(!XMVector3IsInfinite(EyeDirection));
		assert(!XMVector3Equal(UpDirection, XMVectorZero()));
		assert(!XMVector3IsInfinite(UpDirection));

		XMVECTOR R2 = XMVector3Normalize(EyeDirection);
		XMVECTOR R0 = XMVector3Cross(UpDirection, R2);
		R0 = XMVector3Normalize(R0);

		XMVECTOR R1 = XMVector3Cross(R2, R0);

		XMVECTOR NegEyePosition = XMVectorNegate(EyePosition);

		XMVECTOR D0 = XMVector3Dot(R0, NegEyePosition);
		XMVECTOR D1 = XMVector3Dot(R1, NegEyePosition);
		XMVECTOR D2 = XMVector3Dot(R2, NegEyePosition);

		XMMATRIX M;
		M.r[0] = XMVectorSelect(D0, R0, g_XMSelect1110.v);
		M.r[1] = XMVectorSelect(D1, R1, g_XMSelect1110.v);
		M.r[2] = XMVectorSelect(D2, R2, g_XMSelect1110.v);
		M.r[3] = g_XMIdentityR3.v;

		M = XMMatrixTranspose(M);
		return M;
		*/

		DirectMatrix = DirectX::XMMatrixLookAtLH(_EyePos.DirectVector, _EyeFocus.DirectVector, _EyeUp.DirectVector);
	}

	void ViewTo(const float4& _EyePos, const float4& _EyeFocus, const float4& _EyeUp)
	{
		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos.DirectVector, _EyeFocus.DirectVector, _EyeUp.DirectVector);
	}

	float4x4 operator*(const float4x4& _value)
	{
		return DirectX::XMMatrixMultiply(DirectMatrix, _value.DirectMatrix);
	}



};

// using FVector = float4;