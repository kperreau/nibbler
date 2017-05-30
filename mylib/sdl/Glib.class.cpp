/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 20:56:29 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib() : _texture(false)
{
	this->_input[SDL_SCANCODE_UP] = std::pair<input, int>(Top, 0);
	this->_input[SDL_SCANCODE_DOWN] = std::pair<input, int>(Bottom, 0);
	this->_input[SDL_SCANCODE_LEFT] = std::pair<input, int>(Left, 0);
	this->_input[SDL_SCANCODE_RIGHT] = std::pair<input, int>(Right, 0);
	this->_input[SDL_SCANCODE_Z] = std::pair<input, int>(Top, 1);
	this->_input[SDL_SCANCODE_S] = std::pair<input, int>(Bottom, 1);
	this->_input[SDL_SCANCODE_Q] = std::pair<input, int>(Left, 1);
	this->_input[SDL_SCANCODE_D] = std::pair<input, int>(Right, 1);
	this->_input[SDL_SCANCODE_ESCAPE] = std::pair<input, int>(Exit, 4);
	this->_input[SDL_SCANCODE_SPACE] = std::pair<input, int>(Pause, 4);
	this->_input[SDL_SCANCODE_F1] = std::pair<input, int>(F1, 4);
	this->_input[SDL_SCANCODE_F2] = std::pair<input, int>(F2, 4);
	this->_input[SDL_SCANCODE_F3] = std::pair<input, int>(F3, 4);
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

void			Glib::setTexture(void)
{
	this->_texture = !this->_texture;
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

void			Glib::draw(int x, int y, int color, cell c)
{
	SDL_Rect	r;

	if (c == CELL_DEFAULT)
		return ;

    r.x = x * this->_square + 1;
    r.y = y * this->_square + 1;
    r.w = this->_square - 2;
    r.h = this->_square - 2;
    SDL_SetRenderDrawColor( this->_renderer, this->getColor(color, 0), this->getColor(color, 1), this->getColor(color, 2), 0 );
	SDL_RenderFillRect( this->_renderer, &r );
    r.x = x * this->_square;
    r.y = y * this->_square;
    r.w = this->_square;
    r.h = this->_square;
    SDL_SetRenderDrawColor(this->_renderer, 0xff, 0xff, 0xff, 0);
    SDL_RenderDrawRect( this->_renderer, &r );
	return ;
}

void			Glib::write(std::string str, int color)
{

}

std::list <std::pair <input, int> >		Glib::getInput(void)
{
	SDL_Event								event;
	std::list <std::pair <input, int> >		keys;

	while (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_WINDOWEVENT
			&& event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			SDL_DestroyWindow(this->_window);
			SDL_Quit();
			keys.push_front(std::pair<input, int>(Exit, 4));
		}
		else if (event.type == SDL_KEYDOWN
			&& this->_input.count(event.key.keysym.scancode))
			keys.push_front(this->_input.at(event.key.keysym.scancode));
	}
	//SDL_PumpEvents();
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
