#include "PreCompile.h"
#include "GameEnginePixelShader.h"
#include <GameEngineBase/GameEngineString.h>

GameEnginePixelShader::GameEnginePixelShader()
{
}

GameEnginePixelShader::~GameEnginePixelShader()
{
	if (nullptr != Shader_)
	{
		Shader_->Release();
		Shader_ = nullptr;
	}
}



bool GameEnginePixelShader::Load(
	const std::string& _Path,
	const std::string& _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	//SetCode(_ShaderCode);
	CreateVersion("ps");

	return FileCompile(_Path);
}

bool GameEnginePixelShader::Create(
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh/* = 5*/,
	UINT _VersionLow/* = 0*/
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	SetCode(_ShaderCode);
	CreateVersion("ps");

	return StringCompile();
}

bool GameEnginePixelShader::FileCompile(const std::string& _Path)
{
	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 00000000 00000000 00000000 00000101

	// ����� ��ġ�� �Ǽ� ���°��� �����ش�.
	// ��ġ�� �⺻�̰� ��ġ�Ȱ� �ٽ� 
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ������� ����Ʈ�ڵ�

	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	// MultiByteToWideChar()

	std::wstring Path;
	GameEngineString::StringToWString(_Path, Path);

	if (S_OK != D3DCompileFromFile(
		Path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryPoint_.c_str(),
		Version_.c_str(),
		Flag,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();

		GameEngineDebug::MsgBox(GetName() + " ������ ���� ������ �߻��߽��ϴ�.");
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("���ؽ� ���� ������ �����߽��ϴ�.");
		return false;
	}

	ResCheck();

	return true;
}

bool GameEnginePixelShader::StringCompile()
{

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 00000000 00000000 00000000 00000101

	// ����� ��ġ�� �Ǽ� ���°��� �����ش�.
	// ��ġ�� �⺻�̰� ��ġ�Ȱ� �ٽ� 
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ������� ����Ʈ�ڵ�

	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),
		Version_.c_str(),
		0,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " ������ ���� ������ �߻��߽��ϴ�.");
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("���ؽ� ���� ������ �����߽��ϴ�.");
		return false;
	}

	ResCheck();

	return true;
}

void GameEnginePixelShader::Setting()
{
	GameEngineDevice::GetInst().GetContext()->PSSetShader(Shader_, nullptr, 0);
}