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
		sf::RectangleShape rectangle(sf::Vector2f(data->square, data->square));
		rectangle.setFillColor(
			sf::Color(
				  this->getColor(data->color[0], 0)
				, this->getColor(data->color[0], 1)
				, this->getColor(data->color[0], 2)
				)
			);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(
			sf::Color(
				  this->getColor(data->color[1], 0)
				, this->getColor(data->color[1], 1)
				, this->getColor(data->color[1], 2)
				)
			);
		rectangle.setPosition(data->x * data->square, data->y * data->square);
		this->_window.draw(rectangle);
	}
	return ;
}

void			Sfml::getInput(s_data *data)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		data->in[0] = Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		data->in[0] = Right;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		data->in[0] = Bottom;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		data->in[0] = Top;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		data->in[1] = Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		data->in[1] = Right;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		data->in[1] = Bottom;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		data->in[1] = Top;
	//else
	//	data->in[0] = None;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		exit (0);
	return ;
}

Sfml &			Sfml::operator=(Sfml const & rhd)
{
	return (*this);
}

extern "C" int		glib(instruct val, s_data *data)
{
	switch (val)
	{
		case Ins_Create:
			static Sfml		sfml(data->x, data->y);
			break ;
		case Ins_Clear:
			sfml.clear();
			break ;
		case Ins_Display:
			sfml.display();
			break ;
		case Ins_Draw:
			sfml.draw(data);
			break ;
		case Ins_Input:
			sfml.getInput(data);
			break ;
		default:
			;
	}
	return (0);
}
