#include "pch.h"
#include "InputManager.h"

bool InputManager::m_mouseLocked = false;

bool InputManager::GetKeyIsPressed(char keyName)
{
	if (GetAsyncKeyState(keyName) & 0x8000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::GetKeyIsReleased(char keyName)
{
	// tableau statique pour memoriser l'etat precedent de chaque touche
	static bool prevState[256] = {};

	bool isDownNow = (GetAsyncKeyState(keyName) & 0x8000) != 0;
	bool wasDown = prevState[(unsigned char)keyName];
	bool justReleased = (wasDown && !isDownNow);

	prevState[(unsigned char)keyName] = isDownNow;
	return justReleased;
}

void InputManager::EnableFPSMouseLock(HWND hWnd)
{
	// Masque le curseur
	//while (ShowCursor(FALSE) >= 0);

	// Clip le curseur à l'intérieur de la fenêtre
	RECT rc;
	GetClientRect(hWnd, &rc);
	POINT ul = { rc.left,  rc.top };
	POINT lr = { rc.right, rc.bottom };
	ClientToScreen(hWnd, &ul);
	ClientToScreen(hWnd, &lr);
	rc = { ul.x, ul.y, lr.x, lr.y };
	ClipCursor(&rc);

	// Place-le au centre
	POINT center = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };
	SetCursorPos(center.x, center.y);

	m_mouseLocked = true;
}

void InputManager::DisableFPSMouseLock()
{
	// Affiche à nouveau le curseur
	while (ShowCursor(TRUE) < 0);

	// Libère le clip
	ClipCursor(nullptr);

	m_mouseLocked = false;
}

void InputManager::CenterLockCursor(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	POINT center = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };

	SetCursorPos(center.x, center.y);
}

