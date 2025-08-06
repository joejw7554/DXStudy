#include "Framework.h"
#include "Systems/Window.h"


int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPrevInstance, LPSTR InParam, int InCommand)
{
	CWindow* window = new CWindow(L"D3D_Game", 1024, 768, InInstance);

	WPARAM result = window->Run();

	Delete(window);



	return result;
}