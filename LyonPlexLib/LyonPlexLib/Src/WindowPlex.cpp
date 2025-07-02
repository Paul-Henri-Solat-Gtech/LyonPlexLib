#include "pch.h"

bool WindowPlex::Init(HINSTANCE appInstance, const std::wstring& windowName, float windowWidth, float windowHeight)
{
	const wchar_t* className = L"MyNewWindowClass";

	m_winWidth = windowWidth;
	m_winHeight = windowHeight;

	WNDCLASSEX wcx = {};
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WindowProcedure;
	wcx.hInstance = appInstance;
	wcx.lpszClassName = className;
	wcx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// more parameters can be added
	if (RegisterClassEx(&wcx) == 0)
	{
		// Error register new class
		return false;
	}

	m_windowHandle = CreateWindowEx(
		0, className, windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, m_winWidth, m_winHeight,
		nullptr, nullptr, appInstance, nullptr
	);

	// Instance moteur
	SetWindowLongPtr(m_windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	if (!m_windowHandle)
	{
		// Error window creation
		return false;
	}

	ShowWindow(m_windowHandle, SW_SHOW);
	UpdateWindow(m_windowHandle);
	return true;
}

LRESULT CALLBACK WindowPlex::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// case WM_PAINT:
		//     // BeginPaint/EndPaint si tu veux dessiner
		//     break;
		// autres messages...
	case WM_SIZE:
		// RESIZE
		if (wParam != SIZE_MINIMIZED) {
			UINT newW = LOWORD(lParam);
			UINT newH = HIWORD(lParam);
			// appeler votre gestionnaire pour redimensionner :
			// par exemple :
			auto app = reinterpret_cast<RenderingManager*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			//if (app) app->OnResize(newW, newH);
		}
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}