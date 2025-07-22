#pragma once
class InputManager
{
public:
	static bool GetKeyIsPressed(char keyName);
	static bool GetKeyIsReleased(char keyName);
	static bool GetKeyIsJustPressed(char keyName);

	static void EnableFPSMouseLock(HWND hWnd);
	static void DisableFPSMouseLock();
	static void CenterLockCursor(HWND hWnd);

	static bool IsMouseLocked() { return m_mouseLocked; };

	static void OnMouseWheel(WPARAM wParam);
    static int  GetAndResetWheelDelta();

private:
	static bool m_mouseLocked;
	inline static int  m_wheelDelta = 0;

};

