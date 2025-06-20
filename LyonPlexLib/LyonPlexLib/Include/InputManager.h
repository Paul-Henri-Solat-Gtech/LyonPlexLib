#pragma once
class InputManager
{
public:
	static bool GetKeyIsPressed(char keyName);
	static bool GetKeyIsReleased(char keyName);

	static void EnableFPSMouseLock(HWND hWnd);
	static void DisableFPSMouseLock();
	
	static bool IsMouseLocked() { return m_mouseLocked; };

private:
	static bool m_mouseLocked;

};

