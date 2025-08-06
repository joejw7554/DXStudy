#include "Framework.h"
#include "D3D.h"


CD3D* CD3D::Instance = nullptr;

CD3D::CD3D(HWND InHandle, float InWidth, float InHeight) : Handle(InHandle), Width(InWidth), Height(InHeight)
{
	CreateDevice();
	//����̽� ����
	//����̽�: �׷���ī��� ����ϴ� ��ü�̸� ��� �׷��� ���ҽ��� ������������ �����ϰ� �����ϴ� �������Ѵ�

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
	DXGI_SWAP_CHAIN_DESC desc; //DESC�� ��ü�� ��� ��������� �����ϴ°�
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = (UINT)Width;
	desc.BufferDesc.Height = (UINT)Height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 0; //Refresh Rate(�ֻ��� : Frame Rate) �ִ� �ֻ����� �ֱ����� 0�� 1 �� �ذ�
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = Handle;
	desc.SampleDesc.Count = 1;
	desc.Windowed = true; //�������� ����Ұ��̳�
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //����۷� ���ƿ����� ��� ó���Ҳ��� ��������?

	HRESULT hr = 0;

	IDXGIDevice* dxgiDevice = nullptr; //DXGI ���� ��ġ�� ������ �� �ִ� ��ü
	hr = Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	Check(hr);

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	Check(hr);

	IDXGIFactory* factory = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
	Check(hr);

	//__uuidof �� ���� : I �� COM �������̽��� �ǹ� �׸��� COM �������̽����� ��� UUID���� �������־ UUID�� ���ؼ� �����޶� ����
	//��� �ڷ����� ���� UUID ���� �𸣴ϱ� void**�� �޾ƿͼ� �Ҵ��ϴ°�`

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
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer); //�������ٴ� SwapChain�� �ִ� ����۸� �����ͼ� Texture2D�� �����ϴ°�
	Check(hr);

	hr = Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
	Check(hr);

	Release(backBuffer);

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr); //RenderTargetView ���ٰ� �������� �ش޶� �����ϴ°�

}

void CD3D::CreateViewport()
{
	Viewport = new D3D11_VIEWPORT(); //����Ʈ: ȭ���� �󸶸�ŭ �׷����� ������ �����ϴ°�
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
