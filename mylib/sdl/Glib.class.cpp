/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 15:07:36 by kperreau         ###   ########.fr       */
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
	this->_input[1][SDL_SCANCODE_W] = Top;
	this->_input[1][SDL_SCANCODE_S] = Bottom;
	this->_input[1][SDL_SCANCODE_A] = Left;
	this->_input[1][SDL_SCANCODE_D] = Right;
	this->_input[4][SDL_SCANCODE_ESCAPE] = Exit;
	this->_input[4][SDL_SCANCODE_SPACE] = Pause;
	this->_input[4][SDL_SCANCODE_F1] = F1;
	this->_input[4][SDL_SCANCODE_F2] = F2;
	this->_input[4][SDL_SCANCODE_F3] = F3;
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
	
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
		
        return ;
    }
	
    // Création de la fenêtre
	
    this->_window = SDL_CreateWindow("Nibbler SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    this->_renderer = SDL_CreateRenderer( this->_window, -1, SDL_RENDERER_ACCELERATED);
    this->_state = SDL_GetKeyboardState(NULL);
	return ;
}

SDL_Window*		Glib::getWindow(void)
{
	return (this->_window);
}

void			Glib::display(void)
{
	SDL_RenderPresent(this->_renderer);
	SDL_SetRenderDrawColor( this->_renderer, 0, 0, 0, 0 );
	SDL_RenderClear( this->_renderer );
	return ;
}

void			Glib::clear(void)
{
	SDL_RenderClear( this->_renderer );
	return ;
}

void			Glib::exit(void)
{
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
	return ;
}

int			Glib::getColor(int color, int type)
{
	return ((color >> (type * 8)) & 0xff);
}

void			Glib::draw(int x, int y, int color)
{
	SDL_Rect r;
    r.x = x * this->_square;
    r.y = y * this->_square;
    r.w = this->_square;
    r.h = this->_square;
    SDL_SetRenderDrawColor( this->_renderer, this->getColor(color, 0), this->getColor(color, 1), this->getColor(color, 2), 0 );
	SDL_RenderFillRect( this->_renderer, &r );
    r.x = x * this->_square-1;
    r.y = y * this->_square-1;
    r.w = this->_square+2;
    r.h = this->_square+2;
    SDL_SetRenderDrawColor(this->_renderer, 0xff, 0xff, 0xff, 0);
    SDL_RenderDrawRect( this->_renderer, &r );
	return ;
}

input			Glib::getInput(int id)
{
	SDL_Event evenements;
	while (SDL_PollEvent(&evenements) == 1)
	{
		if (evenements.type == SDL_WINDOWEVENT && evenements.window.event == SDL_WINDOWEVENT_CLOSE) {
			SDL_DestroyWindow(this->_window);
			SDL_Quit();
			return (Exit);
		}
	}
	SDL_PumpEvents();
	for (auto it = this->_input[id].begin(); it != this->_input[id].end(); ++it)
	{
		if (this->_state[it->first])
			return (it->second);
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
