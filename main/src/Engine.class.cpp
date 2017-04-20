/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/20 20:34:39 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"

Engine::Engine(uint32_t width, uint32_t height, uint32_t nb_players, void *handle)
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
	for (uint32_t i = 0; i < nb_players; ++i)
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

void					Engine::run(void)
{
	auto	time = Clock::now();
	auto	oldtime = Clock::now();
	long	duration = 0;
	void *		(*f)();
	char *		error;

	*(void**)(&f) = dlsym(this->_handle, "lol");
	if ((error = dlerror()) != NULL)  {
		fputs(error, stderr);
		exit(1);
	}

	while (1)
	{
		f();
		time = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
		if (duration < this->_speed * 1000000)
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
		|| std::get<1>(head) > this->get_game_height())
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

Snake const *			Engine::get_player_by_id(uint32_t id) const
{
	return (this->_listPlayers.at(id));
}

std::vector <Snake *>	Engine::get_players_list(void) const
{
	return (this->_listPlayers);
}

uint32_t				Engine::get_game_height(void) const
{
	return (this->_height / SQUARE);
}

uint32_t				Engine::get_game_width(void) const
{
	return (this->_width / SQUARE);
}

uint32_t				Engine::get_height(void) const
{
	return (this->_height);
}

uint32_t				Engine::get_width(void) const
{
	return (this->_width);
}

uint32_t				Engine::get_nbPlayers(void) const
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
