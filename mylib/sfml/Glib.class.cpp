/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 20:50:14 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib() : _texture(false)
{
	sf::Texture		texture;

	// input
	this->_input[sf::Keyboard::Up] = std::pair<input, int>(Top, 0);
	this->_input[sf::Keyboard::Down] = std::pair<input, int>(Bottom, 0);
	this->_input[sf::Keyboard::Left] = std::pair<input, int>(Left, 0);
	this->_input[sf::Keyboard::Right] = std::pair<input, int>(Right, 0);
	this->_input[sf::Keyboard::W] = std::pair<input, int>(Top, 1);
	this->_input[sf::Keyboard::S] = std::pair<input, int>(Bottom, 1);
	this->_input[sf::Keyboard::A] = std::pair<input, int>(Left, 1);
	this->_input[sf::Keyboard::D] = std::pair<input, int>(Right, 1);
	this->_input[sf::Keyboard::U] = std::pair<input, int>(Top, 2);
	this->_input[sf::Keyboard::J] = std::pair<input, int>(Bottom, 2);
	this->_input[sf::Keyboard::H] = std::pair<input, int>(Left, 2);
	this->_input[sf::Keyboard::K] = std::pair<input, int>(Right, 2);
	this->_input[sf::Keyboard::Escape] = std::pair<input, int>(Exit, 4);
	this->_input[sf::Keyboard::Space] = std::pair<input, int>(Pause, 4);
	this->_input[sf::Keyboard::F1] = std::pair<input, int>(F1, 4);
	this->_input[sf::Keyboard::F2] = std::pair<input, int>(F2, 4);
	this->_input[sf::Keyboard::F3] = std::pair<input, int>(F3, 4);
	this->_input[sf::Keyboard::F4] = std::pair<input, int>(F4, 4);

	// textures
	texture.setSmooth(true);
	if (!texture.loadFromFile("./data/malus.png"))
	{
		throw std::runtime_error("Failed to load texture ./data/malus.png");
		return ;
	}
	this->_textures[CELL_MALUS] = texture;
	if (!texture.loadFromFile("./data/burger.png"))
	{
		throw std::runtime_error("Failed to load texture ./data/burger.png");
		return ;
	}
	this->_textures[CELL_FOOD] = texture;
	if (!texture.loadFromFile("./data/rock.png"))
	{
		throw std::runtime_error("Failed to load texture ./data/rock.png");
		return ;
	}
	this->_textures[CELL_ROCK] = texture;
	if (!texture.loadFromFile("./data/grass.png"))
	{
		throw std::runtime_error("Unable to load texture ./data/grass.png");
		return ;
	}
	this->_textures[CELL_DEFAULT] = texture;
	if (!texture.loadFromFile("./data/snake.png"))
	{
		throw std::runtime_error("Failed to load texture ./data/snake.png");
		return ;
	}
	this->_textures[CELL_SNAKE] = texture;
	if (!texture.loadFromFile("./data/head.png"))
	{
		throw std::runtime_error("Failed to load texture ./data/head.png");
		return ;
	}
	this->_textures[CELL_HEAD] = texture;
	return ;
}

Glib::~Glib(void)
{
	return ;
}

Glib::Glib(Glib const & src)
{
	static_cast<void>(src);
	//*this = src;
	return ;
}

void				Glib::init(int width, int height, int square)
{

	if (static_cast<unsigned int>(width) >= sf::VideoMode::getDesktopMode().width
		|| static_cast<unsigned int>(height) >= sf::VideoMode::getDesktopMode().height)
	{
		throw std::length_error("Window size too big");
		return ;
	}

	this->_width = width;
	this->_height = height;
	this->_square = square;
	this->_window.create(sf::VideoMode(width, height), "Nibbler SFML");
	this->_window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width/2)-(width/2), (sf::VideoMode::getDesktopMode().height/2)-(height/2)));

	if (!this->_font.loadFromFile("data/arial.ttf"))
	{
		throw std::runtime_error("Failed to load font ./data/arial.ttf");
		return ;
	}
	this->_text.setFont(this->_font); // font est un sf::Font
	this->_text.setCharacterSize(24); // exprimée en pixels, pas en points !
	this->_text.setString("");
	return ;
}

sf::RenderWindow &	Glib::getWindow(void)
{
	return (this->_window);
}

void			Glib::display(void)
{
	if (this->_window.isOpen())
	{
		this->_window.draw(this->_text);
		this->_window.display();
		this->_window.clear();
	}
	return ;
}

void			Glib::setTexture(void)
{
	this->_texture = !this->_texture;
	return ;
}

void			Glib::clear(void)
{
	if (this->_window.isOpen())
		this->_window.clear();
	return ;
}

void			Glib::exit(void)
{
	this->_window.close();
	return ;
}

int			Glib::getColor(int color, int type)
{
	return ((color >> (type * 8)) & 0xff);
}

void			Glib::draw(int x, int y, int color, cell c)
{
	if (this->_window.isOpen())
	{
		if (this->_texture == 0)
		{
			if (c == CELL_DEFAULT)
				return ;
			sf::RectangleShape rectangle(sf::Vector2f(this->_square -2 , this->_square - 2));
			rectangle.setFillColor(
				sf::Color(
					  this->getColor(color, 0)
					, this->getColor(color, 1)
					, this->getColor(color, 2)
					)
				);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(
				sf::Color(
					  0xff
					, 0xff
					, 0xff
					)
				);
			rectangle.setPosition(x * this->_square + 1, y * this->_square + 1);
			this->_window.draw(rectangle);
		}
		else
		{
			sf::Sprite	rectangle;
			if (c == CELL_SNAKE
				|| c == CELL_HEAD)
			{
				if (c == CELL_HEAD)
					color *= 2;
				rectangle.setColor(
					sf::Color(
						  this->getColor(color, 0)
						, this->getColor(color, 1)
						, this->getColor(color, 2)
						)
					);
			}
			rectangle.setTexture(this->_textures[c]);

			if (c != CELL_DEFAULT)
			{
				sf::Sprite	rectangle2;
				rectangle2.setTexture((this->_textures[CELL_DEFAULT]));
				rectangle2.setPosition(x * this->_square, y * this->_square);
				this->_window.draw(rectangle2);
			}
			rectangle.setPosition(x * this->_square, y * this->_square);
			this->_window.draw(rectangle);
		}

	}
	return ;
}

void			Glib::write(std::string str, int color)
{
	this->_text.setString(str);
	this->_text.setFillColor(sf::Color(
			  this->getColor(color, 0)
			, this->getColor(color, 1)
			, this->getColor(color, 2)
			));
	sf::FloatRect textRect = this->_text.getLocalBounds();
	this->_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	this->_text.setPosition(sf::Vector2f(this->_width/2.0f, this->_height/2.0f));
}

std::list <std::pair <input, int> >			Glib::getInput(void)
{
	std::list <std::pair <input, int> >	keys;
	sf::Event			event;

	while (this->_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->_window.close();
			keys.push_front(std::pair<input, int>(Exit, 4));
		}
		if (event.type == sf::Event::KeyPressed
			&& this->_input.count(event.key.code)
			&& this->_window.hasFocus())
		{
			keys.push_front(this->_input.at(event.key.code));
		}
	}
	return (keys);
}

/*IGlib &			Glib::operator=(IGlib const & rhd)
{
	return (*this);
}
*/

extern "C" Glib *		getGlib()
{
	return (new Glib());
}
