#pragma once

#include "FpsCamera.h"
#include <Player.h>

class ArenaScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	//Free cam
	//FreeCamera m_freeCam;

	GameObject m_cam;
	FpsCamera m_fpsCam;

	Player m_player;

};

