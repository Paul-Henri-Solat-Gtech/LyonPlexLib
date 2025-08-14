#pragma once
class Button : public GameObject
{
public:
	//Button() : mp_scene(nullptr), m_windowHandle(nullptr) {}
	Button(Scene* scene, HWND windowHandle);

	void Initialize(HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh);

	void OnUpdate(float deltatime) {};

	void Release();

	// use them in update
	bool GetMouseOnBtn();
	bool GetBtnIsClicked();

private:

	//GameObject m_gameObjectBtn;
	Scene* mp_scene;
	HWND m_windowHandle;
};

