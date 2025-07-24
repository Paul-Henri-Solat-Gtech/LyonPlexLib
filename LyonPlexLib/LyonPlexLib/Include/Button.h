#pragma once
class Button : public GameObject
{
public:
	void Initialize(/*GameObject gmButton,*/ HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh);

	void OnUpdate(float deltatime) {};

	void Release();

	// use them in update
	bool GetMouseOnBtn();
	bool GetBtnIsClicked();

private:

	//GameObject m_gameObjectBtn;
	HWND m_windowHandle;
};

