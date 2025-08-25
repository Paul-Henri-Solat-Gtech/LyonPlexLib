#pragma once
//class Button : public GameObject
//{
//public:
//	//Button() : mp_scene(nullptr), m_windowHandle(nullptr) {}
//	Button(Scene* scene, HWND windowHandle, uint32_t texture, std::string btnName);
//
//	void Initialize(HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh);
//
//	void OnUpdate(float deltatime) {};
//
//	void Release();
//
//	// use them in update
//	bool GetMouseOnBtn();
//	bool GetBtnIsClicked();
//
//private:
//
//	//GameObject m_gameObjectBtn;
//	Scene* mp_scene;
//	HWND m_windowHandle;
//};


class Button : public GameObject
{
public:
    Button(Scene* scene, HWND windowHandle, uint32_t texture, std::string btnName);

    void Initialize(HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh);

   // void OnUpdate(float deltatime) override {};

    void Release();

    // use them in update
    bool GetMouseOnBtn();
    bool GetBtnIsClicked();

private:
    Scene* mp_scene = nullptr;
    HWND m_windowHandle = nullptr;

    // cached transform pointer (may be null if not available)
    TransformComponent* m_cachedTransform = nullptr;

    // cached fallback values if transform not available
    XMFLOAT3 m_cachedPos{ 0,0,0 };
    XMFLOAT3 m_cachedScale{ 100,40,0 };

    // helper to obtain a valid HWND to use for ScreenToClient
    HWND ResolveHWND() const;
};