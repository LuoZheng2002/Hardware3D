#pragma once
#include "Window.h"
#include "Timer.h"
#include "Exception.h"
#include"Drawable/AssTest.h"
#include"Drawable/PointLight.h"
class App
{
public:
	App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
	Timer gameTimer;
	AssTest assTest;
	PointLight pointLight;
};