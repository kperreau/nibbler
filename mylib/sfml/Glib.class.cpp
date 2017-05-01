/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/01 15:24:58 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib()
{
	this->_input[0][sf::Keyboard::Up] = Top;
	this->_input[0][sf::Keyboard::Down] = Bottom;
	this->_input[0][sf::Keyboard::Left] = Left;
	this->_input[0][sf::Keyboard::Right] = Right;
	this->_input[1][sf::Keyboard::Z] = Top;
	this->_input[1][sf::Keyboard::S] = Bottom;
	this->_input[1][sf::Keyboard::Q] = Left;
	this->_input[1][sf::Keyboard::D] = Right;
	this->_input[4][sf::Keyboard::Escape] = Exit;
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
	this->_window.create(sf::VideoMode(width, height), "Nibbler");
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
		sf::Event event;
		while (this->_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->_window.close();
		}
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

input			Glib::getInput(int id)
{
	//sf::Event event;
	
	for (auto it = this->_input[id].begin(); it != this->_input[id].end(); ++it)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(it->first)))
			return (it->second);
	}

	/*while (this->_window.pollEvent(event))
	{
		if (event.type != sf::Event::KeyPressed)
			continue ;
		std::cout << "id: " << id  << std::endl;
		std::cout << "map: " << this->_input[id][event.key.code] << std::endl;
		std::cout << "count: " << this->_input[id].count(event.key.code) << std::endl;
		if (this->_input[id].count(event.key.code) != 0)
			return (this->_input[id][event.key.code]);
		if (event.key.code == sf::Keyboard::Escape)
			exit (0);
	}*/
	return (None);
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
