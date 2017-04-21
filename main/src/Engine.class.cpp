/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/21 17:51:42 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"

Engine::Engine(int width, int height, int nb_players, void *handle)
: _speed(700), _rate(0), _handle(handle)
{
	if (nb_players < 1 && nb_players > 4)
	{
		std::cerr << "Bad players number" << std::endl;
		return ;
	}
	
	if (width < 100 * nb_players || height < 100 * nb_players)
	{
		std::cerr << "Window size too small" << std::endl;
		return ;
	}
	
	this->_nbPlayers = nb_players;
	this->_nbPlayersAlive = nb_players;
	this->_width = width;
	this->_height = height;
	for (int i = 0; i < nb_players; ++i)
		this->_listPlayers.push_back(new Snake(std::pair <int, int>(this->_width / SQUARE / 2  - (nb_players * 2) + i * 2, this->_height / SQUARE / 2)));
	this->run();		// run the game
	return ;
}

Engine::Engine(Engine const & src)
{
	*this = src;
	return ;
}

Engine::~Engine(void)
{
	if (!this->_listPlayers.empty())
		this->_listPlayers.clear();
	return ;
}

typedef struct	data
{
	input	in = None;
}				s_data;

void					Engine::run(void)
{
	auto	time = Clock::now();
	auto	oldtime = Clock::now();
	long	duration = 0;
	int		(*f)(int, int, int);
	char *	error;
	input	in = None;

	*(void**)(&f) = dlsym(this->_handle, "glib");
	if ((error = dlerror()) != NULL)  {
		fputs(error, stderr);
		exit(1);
	}


	f(1, this->_width, this->_height);
	while (1)
	{
		f(2, 0, 0);
		for (auto it = this->_listPlayers.begin() ; it != this->_listPlayers.end(); ++it)
		{
			in = (input)f(5, 0, 0);
			//std::cout << in << std::endl;
			if (in != None)
				(*it)->setDir(in);
			auto elem = (*it)->get_elems();
			for (auto it2 = elem.begin(); it2 != elem.end(); ++it2)
			{
				f(4, std::get<0>(*it2), std::get<1>(*it2));
			}
		}
		f(3, 0, 0);
		time = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
		if (duration < this->_speed * 500000)
			continue ;
		oldtime = Clock::now();
		this->checkPlayers();
		if (this->_nbPlayersAlive < 1)
		{
			std::cout << "Game over" << std::endl;
			return ;
		}
	}
	return ;
}

void					Engine::checkPlayers(void)
{
	for (auto it = this->_listPlayers.begin() ; it != this->_listPlayers.end(); ++it)
	{
		(*it)->move();
		if (this->checkCollision(**it) == 1)
		{
			std::cout << "Collision snake id: " << (*it)->getID() << std::endl;
			--this->_nbPlayersAlive;
			(*it)->set_isAlive(0);
			delete *it;
		}
	}
	return ;
}

int						Engine::checkCollision(Snake const & snake)
{
	std::pair <int, int> head = snake.get_elems().front();

	if (std::get<0>(head) > this->get_game_width()
		|| std::get<1>(head) > this->get_game_height()
		|| std::get<0>(head) < 0 || std::get<1>(head) < 0) 
		return (1);
	return (0);
}

long					Engine::getRate(void) const
{
	return (this->_rate);
}

void					Engine::setRate(void)
{
	return ;
}

Snake const *			Engine::get_player_by_id(int id) const
{
	return (this->_listPlayers.at(id));
}

std::vector <Snake *>	Engine::get_players_list(void) const
{
	return (this->_listPlayers);
}

int						Engine::get_game_height(void) const
{
	return (this->_height / SQUARE);
}

int						Engine::get_game_width(void) const
{
	return (this->_width / SQUARE);
}

int						Engine::get_height(void) const
{
	return (this->_height);
}

int						Engine::get_width(void) const
{
	return (this->_width);
}

int						Engine::get_nbPlayers(void) const
{
	return (this->_nbPlayers);
}

Engine &				Engine::operator=(Engine const & rhs)
{
	this->_nbPlayers = rhs.get_nbPlayers();
	this->_width = rhs.get_width();
	this->_height = rhs.get_height();
	return (*this);
}
