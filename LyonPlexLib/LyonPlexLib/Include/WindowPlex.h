#pragma once

class GameManager;

class WindowPlex
{
public:
	//Default value can be changed (also they always have to be at the end)
	bool Init(HINSTANCE appInstance, const std::wstring& windowName = L"MyNewWindow", float windowWidth = 1920, float windowHeight = 1080);
	
	void OnResize(UINT newW, UINT newH);

	HWND GetWindowHandle() const { return m_windowHandle; };

	float GetWindowWidth() { return m_winWidth; }
	float GetWindowHeight() { return m_winHeight; }

	void SetGameManager(GameManager* gameManager) { m_gameManager = gameManager; };
	GameManager* GetGameManager() const { return m_gameManager; }

private:
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

	HWND m_windowHandle = nullptr;

	float m_winWidth, m_winHeight;

	// Game
	GameManager* m_gameManager = nullptr;
};

