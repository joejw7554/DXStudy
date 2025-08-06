#include "Framework.h"
#include "D3D.h"


CD3D* CD3D::Instance = nullptr;

CD3D::CD3D(HWND InHandle, float InWidth, float InHeight) : Handle(InHandle), Width(InWidth), Height(InHeight)
{
	CreateDevice();
	//디바이스 생성
	//디바이스: 그래픽카드와 통신하는 객체이며 모든 그래픽 리소스와 파이프라인을 관리하고 생성하는 역할을한다

	CreateSwapChain();

	CreateRTV();

	CreateViewport();
}

CD3D::~CD3D()
{
	Release(Device);
	Release(DeviceContext);
	Release(SwapChain);
	Release(RenderTargetView);
	Delete(Viewport);
}

void CD3D::CreateDevice()
{
	/*HRESULT hr = D3D11CreateDevice
	(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &Device, nullptr, &DeviceContext
	);*/

	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &Device, nullptr, &DeviceContext);
	
	Check(hr);
}

void CD3D::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc; //DESC란 객체를 어떻게 만들어줄지 설정하는것
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = (UINT)Width;
	desc.BufferDesc.Height = (UINT)Height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 0; //Refresh Rate(주사율 : Frame Rate) 최대 주사율을 주기위해 0과 1 을 준것
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = Handle;
	desc.SampleDesc.Count = 1;
	desc.Windowed = true; //윈도우모드 사용할것이냐
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //백버퍼로 돌아왔을때 어떻게 처리할꺼냐 버릴꺼냐?

	HRESULT hr = 0;

	IDXGIDevice* dxgiDevice = nullptr; //DXGI 쪽은 장치를 관리할 수 있는 객체
	hr = Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	Check(hr);

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	Check(hr);

	IDXGIFactory* factory = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
	Check(hr);

	//__uuidof 가 뭐냐 : I 는 COM 인터페이스를 의미 그리고 COM 인터페이스들은 모두 UUID들을 가지고있어서 UUID을 통해서 만들어달란 뜻임
	//어떠한 자료형에 대한 UUID 인지 모르니까 void**로 받아와서 할당하는것`

	hr = factory->CreateSwapChain(Device, &desc, &SwapChain);
	Check(hr);

	Release(factory);
	Release(adapter);
	Release(dxgiDevice);

}

void CD3D::CreateRTV()
{
	HRESULT hr;

	ID3D11Texture2D* backBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer); //생성보다는 SwapChain에 있는 백버퍼를 가져와서 Texture2D를 생성하는것
	Check(hr);

	hr = Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
	Check(hr);

	Release(backBuffer);

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr); //RenderTargetView 에다가 렌더링을 해달라 설정하는것

}

void CD3D::CreateViewport()
{
	Viewport = new D3D11_VIEWPORT(); //뷰포트: 화면이 얼마만큼 그려질지 영역을 설정하는것
	Viewport->TopLeftX = 0;
	Viewport->TopLeftY = 0;
	Viewport->Width = Width;
	Viewport->Height = Height;
	Viewport->MinDepth = 0;
	Viewport->MaxDepth = 0;

	DeviceContext->RSSetViewports(1, Viewport);
}

void CD3D::Present()
{
	SwapChain->Present(0, 0);
}

void CD3D::ClearRenderTargetView(FColor InColor)
{
	DeviceContext->ClearRenderTargetView(RenderTargetView, InColor);
}

CD3D* CD3D::Get()
{
	return Instance;
}

void CD3D::Create(HWND InHandle, float InWidth, float InHeight)
{
	assert(Instance == nullptr);

	Instance = new CD3D(InHandle, InWidth, InHeight);
}

void CD3D::Destroy()
{
	Delete(Instance);
}
