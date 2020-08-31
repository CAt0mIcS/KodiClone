#pragma once

#include "Kodi/Window/Window.h"


class Application
{
public:
	Application() = default;

	int Run();

private:
	Window m_Window;
};

