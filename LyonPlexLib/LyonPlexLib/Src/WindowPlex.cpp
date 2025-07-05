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
	RECT wr = { 0, 0, LONG(800), LONG(600) };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
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
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED) {
			UINT newW = LOWORD(lParam);
			UINT newH = HIWORD(lParam);
			auto window = reinterpret_cast<WindowPlex*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if (window && window->m_gameManager) {
				window->m_gameManager->OnResize(newW, newH);
			}
		}
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void WindowPlex::OnResize(UINT newW, UINT newH)
{
	m_winWidth = static_cast<float>(newW);
	m_winHeight = static_cast<float>(newH);
}
