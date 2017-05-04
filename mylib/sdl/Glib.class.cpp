/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/04 17:12:54 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib()
{
	this->_input[0][SDL_SCANCODE_UP] = Top;
	this->_input[0][SDL_SCANCODE_DOWN] = Bottom;
	this->_input[0][SDL_SCANCODE_LEFT] = Left;
	this->_input[0][SDL_SCANCODE_RIGHT] = Right;
	this->_input[1][SDL_SCANCODE_Z] = Top;
	this->_input[1][SDL_SCANCODE_S] = Bottom;
	this->_input[1][SDL_SCANCODE_Q] = Left;
	this->_input[1][SDL_SCANCODE_D] = Right;
	this->_input[4][SDL_SCANCODE_ESCAPE] = Exit;
	this->_input[4][SDL_SCANCODE_SPACE] = Pause;
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

void			Glib::init(int width, int height, int square)
{
	this->_width = width;
	this->_height = height;
	this->_square = square;
	// Notre fenêtre
	
    SDL_Window* fenetre(0);
	
    // Initialisation de la SDL
	
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
		
        return ;
    }
	
    // Création de la fenêtre
	
    this->_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	
	return ;
}

SDL_Window*		Glib::getWindow(void)
{
	return (this->_window);
}

void			Glib::display(void)
{
	/*if (this->_window.isOpen())
	{
		sf::Event event;
		while (this->_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->_window.close();
		}
		this->_window.display();
		this->_window.clear();
	}*/
	return ;
}

void			Glib::clear(void)
{
	/*if (this->_window.isOpen())
		this->_window.clear();*/
	return ;
}

int			Glib::getColor(int color, int type)
{
	return ((color >> (type * 8)) & 0xff);
}

void			Glib::draw(int x, int y, int color)
{
	/*if (this->_window.isOpen())
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
	}*/
	return ;
}

input			Glib::getInput(int id)
{
	// Structure
	SDL_Event evenements;


	// Récupération d'un évènement
	while (SDL_PollEvent(&evenements) == 1)
	{
		if (evenements.type == SDL_KEYDOWN)
		{
			for (auto it = this->_input[id].begin(); it != this->_input[id].end(); ++it)
			{
				if (evenements.key.keysym.scancode == it->first)
					return (it->second);
			}
		}
	}
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
