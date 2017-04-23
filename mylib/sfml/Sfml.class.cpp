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

int			Sfml::getColor(int color, int type)
{
	return ((color >> (type * 8)) & 0xff);
}

void			Sfml::draw(s_data *data)
{
	if (this->_window.isOpen())
	{
		sf::RectangleShape rectangle(sf::Vector2f(8, 8));
		rectangle.setFillColor(
			sf::Color(
				  this->getColor(data->color, 0)
				, this->getColor(data->color, 1)
				, this->getColor(data->color, 2)
				)
			);
		rectangle.setPosition(data->x * 8, data->y * 8);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		return (Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		return (Bottom);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		return (Top);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exit (0);
	}
	return (None);
}

Sfml &			Sfml::operator=(Sfml const & rhd)
{
	return (*this);
}

extern "C" int		glib(int val, s_data *data)
{
	switch (val)
	{
		case 1:
			static Sfml		sfml(data->x, data->y);
			break ;
		case 2:
			sfml.clear();
			break ;
		case 3:
			sfml.display();
			break ;
		case 4:
			sfml.draw(data);
			break ;
		case 5:
			data->in = sfml.getInput();
			break ;
	}
	return (0);
}
