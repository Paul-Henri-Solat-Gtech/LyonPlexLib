#pragma once
class Button
{
public:
	void Init(GameObject gmButton, HWND windowHandle);

	// use them in update
	bool GetMouseOnBtn();
	bool GetBtnIsClicked();

private:

	GameObject m_gameObjectBtn;
	HWND m_windowHandle;
};

