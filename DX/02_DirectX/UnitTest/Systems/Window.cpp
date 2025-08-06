#include "Framework.h"
#include "Window.h"

CWindow::CWindow(wstring InAppName, float InWidth, float InHeight, HINSTANCE InInstance)
	:AppName(InAppName), Width(InWidth), Height(InHeight), Instance(InInstance)
{
	CreateHandle();

	CD3D::Create(Handle, Width, Height);
}

CWindow::~CWindow()
{
	CD3D::Destroy();

	DestroyWindow(Handle);
	UnregisterClass(AppName.c_str(), Instance);
}

WPARAM CWindow::Run()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			DispatchMessage(&msg);
		}
		else
		{
			CD3D::Get()->ClearRenderTargetView(FColor::Blue);
			{
				//여기에 이제 렌더링할 코드를 작성하게 될것이다



			}


			CD3D::Get()->Present();
		}
	}

	return msg.wParam;
}

void CWindow::CreateHandle()
{
	//Regist Window Class
	{
		WNDCLASSEX wndClass;
		ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.hCursor = LoadCursor(Instance, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT);
		wndClass.lpszClassName = AppName.c_str();
		wndClass.hInstance = Instance;

		wndClass.lpfnWndProc = WndProc;

		ATOM check = RegisterClassEx(&wndClass);
		assert(check != 0);

	}


	//Create Window Handle
	{
		Handle = CreateWindowEx(0, AppName.c_str(), AppName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (int)Width, (int)Height, nullptr, nullptr, Instance, nullptr);
		assert(Handle != nullptr);
	}

	//Show Window
	{
		ShowWindow(Handle, SW_SHOWNORMAL);
		SetForegroundWindow(Handle);
		SetFocus(Handle);
		ShowCursor(true);
	}


}

LRESULT CWindow::WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
	if (InMessage == WM_KEYDOWN)
	{
		if (InwParam == VK_ESCAPE)
		{
			//MessageBox(InHandle, L"이 프로그램이 종료됩니다.", L"경고", MB_OK);

			PostQuitMessage(0);

			return 0;
		}
	}

	if (InMessage == WM_CLOSE || InMessage == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(InHandle, InMessage, InwParam, InlParam);
}




