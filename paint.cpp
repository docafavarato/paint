#include "paint.h"

void Paint::initVariables()
{
	this->window = nullptr;
}

void Paint::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1000;
	this->window = new sf::RenderWindow(this->videoMode, "Paint", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Paint::initInk()
{
	this->ink.setSize(sf::Vector2f(8, 8));
	this->ink.setFillColor(sf::Color::White);

	this->menu.setSize(sf::Vector2f(1000, 60));
	this->menu.setFillColor(sf::Color(196, 196, 196));
	
	this->eraser.setSize(sf::Vector2f(20, 20));
}

void Paint::initFonts()
{
	this->font.loadFromFile("fonts/hatsch.otf");

	this->clear_text.setFont(this->font);
	this->clear_text.setFillColor(sf::Color::White);
	this->clear_text.setCharacterSize(35);
	this->clear_text.setPosition(sf::Vector2f(870, 8));
	this->clear_text.setString("Clear");

	this->red_pen.setSize(sf::Vector2f(20, 20));
	this->red_pen.setFillColor(sf::Color::Red);
	this->red_pen.setOutlineColor(sf::Color::Black);
	this->red_pen.setOutlineThickness(1);
	this->red_pen.setPosition(sf::Vector2f(400, 20));

	this->green_pen.setSize(sf::Vector2f(20, 20));
	this->green_pen.setFillColor(sf::Color::Green);
	this->green_pen.setOutlineColor(sf::Color::Black);
	this->green_pen.setOutlineThickness(1);
	this->green_pen.setPosition(sf::Vector2f(430, 20));

	this->blue_pen.setSize(sf::Vector2f(20, 20));
	this->blue_pen.setFillColor(sf::Color::Blue);
	this->blue_pen.setOutlineColor(sf::Color::Black);
	this->blue_pen.setOutlineThickness(1);
	this->blue_pen.setPosition(sf::Vector2f(460, 20));

	this->yellow_pen.setSize(sf::Vector2f(20, 20));
	this->yellow_pen.setFillColor(sf::Color::Yellow);
	this->yellow_pen.setOutlineColor(sf::Color::Black);
	this->yellow_pen.setOutlineThickness(1);
	this->yellow_pen.setPosition(sf::Vector2f(490, 20));

	this->white_pen.setSize(sf::Vector2f(20, 20));
	this->white_pen.setFillColor(sf::Color::White);
	this->white_pen.setOutlineColor(sf::Color::Black);
	this->white_pen.setOutlineThickness(1);
	this->white_pen.setPosition(sf::Vector2f(520, 20));

	this->purple_pen.setSize(sf::Vector2f(20, 20));
	this->purple_pen.setFillColor(sf::Color::Magenta);
	this->purple_pen.setOutlineColor(sf::Color::Black);
	this->purple_pen.setOutlineThickness(1);
	this->purple_pen.setPosition(sf::Vector2f(550, 20));

	this->small_text.setFont(this->font);
	this->small_text.setFillColor(sf::Color::White);
	this->small_text.setCharacterSize(20);
	this->small_text.setPosition(sf::Vector2f(10, 20));
	this->small_text.setString("Small");

	this->normal_text.setFont(this->font);
	this->normal_text.setFillColor(sf::Color::White);
	this->normal_text.setCharacterSize(20);
	this->normal_text.setPosition(sf::Vector2f(90, 20));
	this->normal_text.setString("Normal");

	this->big_text.setFont(this->font);
	this->big_text.setFillColor(sf::Color::White);
	this->big_text.setCharacterSize(20);
	this->big_text.setPosition(sf::Vector2f(190, 20));
	this->big_text.setString("Big");
}

void Paint::spawnInk() {
	this->ink.setPosition(this->mousePosView);
	this->inks.push_back(this->ink);
}

void Paint::updateInkColor()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->red_pen.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setFillColor(sf::Color::Red);
		}
		else if (this->green_pen.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setFillColor(sf::Color::Green);
		}
		else if (this->blue_pen.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setFillColor(sf::Color::Blue);
		}
		else if (this->yellow_pen.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setFillColor(sf::Color::Yellow);
		}
		else if (this->white_pen.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setFillColor(sf::Color::White);
		}
		else if (this->purple_pen.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setFillColor(sf::Color::Magenta);
		}
	}
}

void Paint::updateInkSize()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->small_text.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setSize(sf::Vector2f(3, 3));
		}
		else if (this->normal_text.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setSize(sf::Vector2f(10, 10));
		}
		else if (this->big_text.getGlobalBounds().contains(this->mousePosView))
		{
			this->ink.setSize(sf::Vector2f(16, 16));
		}
	}
}

void Paint::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window->close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->clear_text.getGlobalBounds().contains(this->mousePosView))
			{
				this->inks.clear();
			}
			else
			{
				if (this->mousePosView.y > 60) 
				{
					this->spawnInk();
				}
			}
		}
	}
}

void Paint::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Paint::updateInk()
{
	for (int i = 0; i < this->inks.size(); i++)
	{
		bool deleted = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (this->inks[i].getGlobalBounds().intersects(this->eraser.getGlobalBounds()))
			{
				deleted = true;
			}
		}

		if (deleted)
		{
			this->inks.erase(this->inks.begin() + i);
		}
	}
}

void Paint::updateColors()
{
	if (this->clear_text.getGlobalBounds().contains(this->mousePosView))
	{
		this->clear_text.setFillColor(sf::Color(0, 0, 0));
	}
	else
	{
		this->clear_text.setFillColor(sf::Color::White);
	}

	if (this->small_text.getGlobalBounds().contains(this->mousePosView))
	{
		this->small_text.setFillColor(sf::Color(0, 0, 0));
	} 
	else if (this->normal_text.getGlobalBounds().contains(this->mousePosView))
	{
		this->normal_text.setFillColor(sf::Color(0, 0, 0));
	}
	else if (this->big_text.getGlobalBounds().contains(this->mousePosView))
	{
		this->big_text.setFillColor(sf::Color(0, 0, 0));
	}
	else
	{
		this->small_text.setFillColor(sf::Color::White);
		this->normal_text.setFillColor(sf::Color::White);
		this->big_text.setFillColor(sf::Color::White);
	}
}

void Paint::updateEraser()
{
	this->eraser.setPosition(this->mousePosView));
}

void Paint::update()
{
	this->pollEvents();
	this->updateMousePosition();
	this->updateInk();
	this->updateColors();
	this->updateInkColor();
	this->updateInkSize();
}

void Paint::renderInk()
{
	for (auto& i : this->inks)
	{
		this->window->draw(i);
	}
	
	this->window->draw(this->menu);
}

void Paint::renderTexts()
{
	this->window->draw(this->clear_text);

	this->window->draw(this->red_pen);
	this->window->draw(this->green_pen);
	this->window->draw(this->blue_pen);
	this->window->draw(this->yellow_pen);
	this->window->draw(this->white_pen);
	this->window->draw(this->purple_pen);

	this->window->draw(this->small_text);
	this->window->draw(this->normal_text);
	this->window->draw(this->big_text);
}

void Paint::render()
{
	this->window->clear();

	this->renderInk();
	this->renderTexts();

	this->window->display();
}

Paint::Paint()
{
	this->initVariables();
	this->initInk();
	this->initFonts();
	this->initWindow();
}

Paint::~Paint() {
	delete this->window;
}

const bool Paint::running() const
{
	return this->window->isOpen();
}
