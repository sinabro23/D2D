#pragma once

#include <GameEngineBase/GameEngineSoundManager.h>
#include "GameEngineConstantBufferManager.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineTextureManager.h"

#include "GameEngineRenderingPipeLineManager.h"

#include "GameEngineConstantBuffer.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineIndexBuffer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineTexture.h"

#include "GameEngineRenderingPipeLine.h"


class GameEngineManagerHelper 
{
public:
	static void ManagerRelease()
	{
		GameEngineSoundManager::Destroy();

		GameEngineRenderingPipeLineManager::Destroy();

		GameEngineConstantBufferManager::Destroy();
		GameEngineIndexBufferManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEngineRenderTargetManager::Destroy();
		GameEnginePixelShaderManager::Destroy();
		GameEngineTextureManager::Destroy();
	}
};
