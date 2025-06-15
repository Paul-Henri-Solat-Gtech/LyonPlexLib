#pragma once

#include "ECSManager.h"

#include "GraphicsDevice.h"
#include "CommandManager.h"
#include "DescriptorManager.h"

inline UINT Align256(UINT size) { return (size + 255) & ~255; }

struct IRender 
{
	virtual bool Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager) = 0;
	virtual void Resize(int w, int h) = 0;
	virtual void CreatePipeline() = 0;
	virtual void RecordCommands() = 0; 
};