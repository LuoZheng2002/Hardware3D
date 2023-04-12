#include "App.h"

App::App()
	:
	wnd(800, 600, TEXT("The Donkey Fart Box")),
	assTest(1.0f),
	pointLight(wnd.Gfx())
{

}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().BeginFrame(c, c, 1.0f);
	float time = gameTimer.Mark();
	pointLight.Bind(wnd.Gfx(), DirectX::XMMatrixTranslation(0, 0.5, 0));
	assTest.Update(time);
	assTest.Draw(wnd.Gfx());

	wnd.Gfx().EndFrame();
}