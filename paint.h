#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <vector>
#include <iostream>

class Paint
{
	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;

		// Functions
		void initVariables();
		void initWindow();
		void initInk();
		void initFonts();

		// Mouse pos
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		// Entities
		sf::RectangleShape ink;
		std::vector<sf::RectangleShape> inks;
		sf::RectangleShape menu;

		sf::Font font;
		sf::Text clear_text;

		sf::Text small_text, normal_text, big_text;
		sf::RectangleShape red_pen, green_pen, blue_pen, yellow_pen, white_pen, purple_pen;

	public:
		Paint();
		virtual ~Paint();

		const bool running() const;

		void update();
		void updateMousePosition();
		void updateInk();
		void updateColors();
		void updateInkColor();
		void updateInkSize();
		void updateEraser();
		void pollEvents();
		void render();
		void renderInk();
		void renderTexts();
		void spawnInk();

		// Logic
		bool eraser;
};
