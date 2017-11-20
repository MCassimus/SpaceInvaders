/*
	Michael Cassimus / Daniel Barnett
	Space Invaders
	Recreate arcade game space invaders
*/
#include "stdafx.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game.h"
#include "GameObject.h"
#include <windows.h>


int main()
{ 
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes().at(0), "Space Invaders", (sf::Style::Resize + sf::Style::Close /*+ sf::Style::Fullscreen*/));
	//sf::RenderWindow window(sf::VideoMode(310, 248), "Space Invaders", (sf::Style::Resize + sf::Style::Close + sf::Style::Fullscreen));
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);

	sf::View view(sf::Rect<float>(0, 0, 310, 248));
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

	MONITORINFO mi = { sizeof(mi) };

	HWND hwnd = window.getSystemHandle();

	// get the coordinates of the monitor the window is currently in
	GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST), &mi);
	
	double viewRatio = view.getSize().x / view.getSize().y;
	DWORD winWidth = (mi.rcMonitor.right - mi.rcMonitor.left);
	DWORD winHeight =  (mi.rcMonitor.bottom - mi.rcMonitor.top);

	printf("%d\n", winWidth / winHeight);

	sf::Vector2<double> viewPos(0, 0);
	sf::Vector2<double> viewSize(1, 1);

	//apply margins where approriate to scale view to fit window
	/*if (winRatio < viewRatio)
	{
		viewSize.y = winRatio / viewRatio;
		viewPos.y = (1 - viewSize.y) / 2.0f;
	}
	else
	{
		viewSize.x = viewRatio / winRatio;
		viewPos.x = (1 - viewSize.x) / 2.0f;
	}
*/
	view.setViewport(sf::FloatRect(viewPos.x, viewPos.y, viewSize.x, viewSize.y));
	window.setView(view);

	GameObject menu(&window);
	menu.setTexture("mainMenu.png");
	menu.setPosition(sf::Vector2f(window.getView().getSize().x / 2, window.getView().getSize().y / 2));

	Game * game = nullptr;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				//float winRatio = sf::VideoMode::getFullscreenModes().at(0).width / sf::VideoMode::getFullscreenModes().at(0).height;

				////apply margins where approriate to scale view to fit window
				//if (winRatio < viewRatio)
				//{
				//	//viewSize.y = winRatio / viewRatio;
				//	//viewPos.y = (1 - viewSize.y) / 2.0f;
				//}
				//else
				//{
				//	viewSize.x = viewRatio / winRatio;
				//	viewPos.x = (1 - viewSize.x) / 2.0f;
				//}
			
				//view.setViewport(sf::FloatRect(viewPos.x, viewPos.y, viewSize.x, viewSize.y));
				//window.setView(view);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Num1 && game == nullptr)
					game = new Game(&window, false);
				else if (event.key.code == sf::Keyboard::Num2 && game == nullptr)
					game = new Game(&window, true);
				else if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

			if (game != nullptr)
			{
				while (game->loop())
					game->render();
				
				delete game;
				game = nullptr;
			}
		}

		window.clear();
		menu.render();
		window.display();
	}
	
	return 0;
}