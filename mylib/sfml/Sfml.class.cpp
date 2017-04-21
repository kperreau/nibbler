/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/21 17:48:31 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sfml.class.hpp"
#include <iostream>

Sfml::Sfml(int width, int height)
: _width(width), _height(height)
{
	this->_window.create(sf::VideoMode(width, height), "Nibbler");
	return ;
}

Sfml::~Sfml(void)
{
	return ;
}

Sfml::Sfml(Sfml const & src)
{
	*this = src;
	return ;
}

sf::RenderWindow &	Sfml::getWindow(void)
{
	return (this->_window);
}

void			Sfml::display(void)
{
	if (this->_window.isOpen())
	{
		sf::Event event;
		while (this->_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->_window.close();
		}
		//sfml.getWindow.draw(shape);
		this->_window.display();
	}
	return ;
}

void			Sfml::clear(void)
{
	if (this->_window.isOpen())
		this->_window.clear();
	return ;
}

void			Sfml::draw(int x, int y)
{
	if (this->_window.isOpen())
	{
		sf::RectangleShape rectangle(sf::Vector2f(8, 8));
		rectangle.setFillColor(sf::Color(100, 250, 50));
		rectangle.setPosition(x * 8, y * 8);
		this->_window.draw(rectangle);
	}
	return ;
}

input			Sfml::getInput(void)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		return (Left);
	}
	return (None);
}

Sfml &			Sfml::operator=(Sfml const & rhd)
{
	return (*this);
}

extern "C" int		glib(int val, int val2, int val3)
{
	switch (val)
	{
		case 1:
			static Sfml		sfml(val2, val3);
			break ;
		case 2:
			sfml.clear();
			break ;
		case 3:
			sfml.display();
			break ;
		case 4:
			sfml.draw(val2, val3);
			break ;
		case 5:
			sfml.getInput();
			break ;
	}
	return (0);
}
