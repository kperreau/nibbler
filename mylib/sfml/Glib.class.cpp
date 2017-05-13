/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 19:24:59 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib()
{
	this->_input[sf::Keyboard::Up] = std::pair<input, int>(Top, 0);
	this->_input[sf::Keyboard::Down] = std::pair<input, int>(Bottom, 0);
	this->_input[sf::Keyboard::Left] = std::pair<input, int>(Left, 0);
	this->_input[sf::Keyboard::Right] = std::pair<input, int>(Right, 0);
	this->_input[sf::Keyboard::Z] = std::pair<input, int>(Top, 1);
	this->_input[sf::Keyboard::S] = std::pair<input, int>(Bottom, 1);
	this->_input[sf::Keyboard::Q] = std::pair<input, int>(Left, 1);
	this->_input[sf::Keyboard::D] = std::pair<input, int>(Right, 1);
	this->_input[sf::Keyboard::Escape] = std::pair<input, int>(Exit, 4);
	this->_input[sf::Keyboard::Space] = std::pair<input, int>(Pause, 4);
	this->_input[sf::Keyboard::F1] = std::pair<input, int>(F1, 4);
	this->_input[sf::Keyboard::F2] = std::pair<input, int>(F2, 4);
	this->_input[sf::Keyboard::F3] = std::pair<input, int>(F3, 4);
	return ;
}

Glib::~Glib(void)
{
	return ;
}

Glib::Glib(Glib const & src)
{
	//*this = src;
	return ;
}

void				Glib::init(int width, int height, int square)
{
	this->_width = width;
	this->_height = height;
	this->_square = square;
	this->_window.create(sf::VideoMode(width, height), "Nibbler SFML");
	this->_window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width/2)-(width/2), (sf::VideoMode::getDesktopMode().height/2)-(height/2)));

	this->_font.loadFromFile("data/arial.ttf");
	this->_text.setFont(this->_font); // font est un sf::Font
	this->_text.setCharacterSize(24); // exprimée en pixels, pas en points !
	this->_text.setString("");
	this->_text.setPosition(width/2, height/2);
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

void			Glib::draw(int x, int y, int color)
{
	if (this->_window.isOpen())
	{
		sf::RectangleShape rectangle(sf::Vector2f(this->_square, this->_square));
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
		rectangle.setPosition(x * this->_square, y * this->_square);
		this->_window.draw(rectangle);
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
}

std::list <std::pair <input, int> >			Glib::getInput(int id)
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
