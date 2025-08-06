#pragma once

class CWindow
{
public:

	CWindow(wstring InAppName, float InWidth, float InHeight, HINSTANCE InInstance);
	~CWindow();

	WPARAM Run();

private:
	void CreateHandle();

private:
	static LRESULT CALLBACK WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam);
private:
	HINSTANCE Instance;
	HWND Handle;

	wstring AppName;
	float Width;
	float Height;


};