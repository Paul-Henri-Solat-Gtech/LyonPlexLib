#pragma once
class Button : public GameObject
{
public:
	void Init(/*GameObject gmButton,*/ HWND windowHandle);

	void OnUpdate(float deltatime) {};

	void Release();

	// use them in update
	bool GetMouseOnBtn();
	bool GetBtnIsClicked();

private:

	//GameObject m_gameObjectBtn;
	HWND m_windowHandle;
};

