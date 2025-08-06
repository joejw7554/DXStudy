#pragma once

class CD3D
{
	friend class CWindow;

public:
	static CD3D* Get();

	static void Create(HWND InHandle, float InWidth, float InHeight);
	static void Destroy();

private:
	static CD3D* Instance;

	CD3D(HWND InHandle, float InWidth, float InHeight);
	~CD3D();

private:
	void CreateDevice(); //Device & DeviceContext
	void CreateSwapChain();
	void CreateRTV();
	void CreateViewport();

	void Present(); //Front버퍼에 있는걸 모니터에 내보내주는 명령어

public:
	void ClearRenderTargetView(FColor InColor = FColor::Black);

private:
	HWND Handle;
	float Width, Height;

	ID3D11Device* Device;

	ID3D11DeviceContext* DeviceContext;

	IDXGISwapChain* SwapChain;

	ID3D11RenderTargetView* RenderTargetView;

	D3D11_VIEWPORT* Viewport;

};