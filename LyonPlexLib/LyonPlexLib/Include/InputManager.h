#pragma once
class InputManager
{
public:
	static bool GetKeyIsPressed(char keyName);
	static bool GetKeyIsReleased(char keyName);

	static void EnableFPSMouseLock(HWND hWnd);
	static void DisableFPSMouseLock();
	static void CenterLockCursor(HWND hWnd);

	static bool IsMouseLocked() { return m_mouseLocked; };

	static int OnMouseWheel(WPARAM wParam) {return GET_WHEEL_DELTA_WPARAM(wParam);}

private:
	static bool m_mouseLocked;

};

