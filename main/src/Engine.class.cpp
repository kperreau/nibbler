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

Engine::Engine(int width, int height, int nb_players, void *handle, uint32_t difficulty)
: _speed(150), _score(0), _rate(0), _handle(handle), _difficulty(difficulty)
{
	if (nb_players < 1 && nb_players > 4)
	{
		std::cerr << "Bad players number" << std::endl;
		return ;
	}
	
	if (width < (SQUARE + 2) * 4 * nb_players
		|| height < (SQUARE + 2) * 4 * nb_players)
	{
		std::cerr << "Window size too small" << std::endl;
		return ;
	}
	
	this->_nbPlayers = nb_players;
	this->_nbPlayersAlive = nb_players;
	this->_width = width - (width % SQUARE);
	this->_height = height - (height % SQUARE);

	// init players
	for (int i = 0; i < nb_players; ++i)
	{
		this->_listPlayers.push_back(
			new Snake(
				std::pair <int, int>(
					  this->_width / SQUARE / 2  - (nb_players * 2) + i * 2
					, this->_height / SQUARE / 2
					)
				, this->_color[i]
				)
			);
	}
	this->_map = new std::vector <cell>(
		  this->get_game_width() * this->get_game_height()
		, CELL_DEFAULT
		);
	this->fillMap();
	this->genFoods();
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
		delete this->_map;
	if (!this->_listPlayers.empty())
		this->_listPlayers.clear();
	return ;
}

void					Engine::genFoods(void)
{
	if (this->_nbPlayersAlive < 1
		|| this->_listFoods.size() > this->_nbPlayersAlive)
		return ;
	
	for (int i = 0; i < this->_nbPlayersAlive - this->_listFoods.size(); ++i)
	{
		uint32_t	n = std::rand() % this->_emptyCells.size();
		auto		it = this->_emptyCells.begin();
		std::advance(it, n);

		this->_map->at(
			std::get<1>(*it) * this->get_game_width() + std::get<0>(*it)
			) = CELL_FOOD;

		this->_listFoods.push_back(std::pair <int, int>(std::get<0>(*it), std::get<1>(*it)));
		this->_emptyCells.erase(it);
	}
	return ;
}

void					Engine::genRocks(void)
{
	if (this->_difficulty < 3)
		return ;
	
	for (int i = 0; i < this->_score - this->_listRocks.size(); ++i)
	{
		uint32_t	n = std::rand() % this->_emptyCells.size();
		auto		it = this->_emptyCells.begin();
		std::advance(it, n);

		this->_map->at(
			std::get<1>(*it) * this->get_game_width() + std::get<0>(*it)
			) = CELL_ROCK;

		this->_listRocks.push_back(std::pair <int, int>(std::get<0>(*it), std::get<1>(*it)));
		this->_emptyCells.erase(it);
	}
	return ;
}

void					Engine::resetMap(void)
{
	for (int i = 0; i < this->_map->size(); ++i)
		this->_map->at(i) = CELL_DEFAULT;
	return ;
}

void					Engine::fillMap(void)
{
	int		coord;

	this->_emptyCells.clear();

	// fill snake cells
	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		auto elem = (*it)->get_elems();
		for (auto it2 = elem.begin(); it2 != elem.end(); ++it2)
		{
			this->_map->at(
				std::get<0>(*it2) + std::get<1>(*it2) * this->get_game_width()
				) = CELL_SNAKE;
			//this->_func_lib(Ins_Draw, &(this->_data));		// Draw snakes
		}
	}

	for (auto it = this->_listFoods.begin(); it != this->_listFoods.end(); ++it)
	{
		this->_map->at(
			std::get<0>(*it) + std::get<1>(*it) * this->get_game_width()
			) = CELL_FOOD;
			//this->_func_lib(Ins_Draw, &(this->_data));		// Draw snakes
	}


	for (auto it = this->_listRocks.begin(); it != this->_listRocks.end(); ++it)
	{
		this->_map->at(
			std::get<0>(*it) + std::get<1>(*it) * this->get_game_width()
			) = CELL_ROCK;
			//this->_func_lib(Ins_Draw, &(this->_data));		// Draw snakes
	}

	for (int i = 0; i < this->_map->size(); ++i)
	{
		if (this->_map->at(i) != CELL_DEFAULT)
			continue ;
		this->_emptyCells.push_back(
			std::pair <int, int>(
				  i % this->get_game_width()
				, i / this->get_game_width()
				)
			);
	}
	return ;
}

void					Engine::drawPlayers(void)
{
	int  color = 0;

	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		auto elem = (*it)->get_elems();
		for (auto it2 = elem.begin(); it2 != elem.end(); ++it2)
		{
			color = (*it)->getColor();
			if (it2 == elem.begin())
				color /= 2;
			this->_data.x = std::get<0>(*it2);
			this->_data.y = std::get<1>(*it2);
			this->_glib->draw(std::get<0>(*it2), std::get<1>(*it2), color);		// Draw snakes
		}
	}
	return ;
}

void					Engine::drawFoods(void)
{
	for (auto it = this->_listFoods.begin(); it != this->_listFoods.end(); ++it)
	{
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0xff00ff);		// Draw foods
	}
	return ;
}


void					Engine::drawRocks(void)
{
	for (auto it = this->_listRocks.begin(); it != this->_listRocks.end(); ++it)
	{
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0x770033);		// Draw rocks
	}
	return ;
}

void					Engine::getInputs(void) const
{
	if (this->_glib->getInput(4) == Exit)
		exit (0);
	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
		(*it)->setNextDir(this->_glib->getInput((*it)->getID()));
	return ;
}

void					Engine::run(void)
{
	auto	time = Clock::now();
	auto	oldtime = Clock::now();
	long	duration = 0;
	IGlib *	(*func_lib)();
	char *	error;
	input	in = None;

	*(void**)&(func_lib) = dlsym(this->_handle, "getGlib");
	if ((error = dlerror()) != NULL)
	{
		fputs(error, stderr);
		exit(1);
	}

	this->_glib = func_lib();
	this->_glib->init(this->_width, this->_height, SQUARE);	// create window

	while (1)
	{
		this->_glib->clear();
		this->getInputs();
		this->drawPlayers();
		this->drawFoods();
		this->drawRocks();
		this->_glib->display();
		time = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
		if (duration < this->_speed * 1000000)
			continue ;
		oldtime = Clock::now();
		this->checkPlayers();
		this->resetMap();
		this->genFoods();
		this->genRocks();
		this->fillMap();
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
	int		collision = 0;

	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		//if (this->_data.in[(*it)->getID()] != None)
		//	(*it)->setDir(this->_data.in[(*it)->getID()]);
		(*it)->move();
		collision = this->checkCollision(**it);
		if (collision == 1)
		{
			--this->_nbPlayersAlive;
			(*it)->set_isAlive(0);
			delete *it;
			it = this->_listPlayers.erase(it);
		}
		else if (collision == 2)
		{
			(*it)->eat();
			++this->_score;
			if (this->_difficulty > 1 && this->_speed > 50)
			{
				this->_speed -= 2;
			}
		}
	}
	return ;
}

int						Engine::checkCollision(Snake const & snake)
{
	std::pair <int, int>	head = snake.get_elems().front();
	int						x = 0;
	int						y = 0;

	if (std::get<0>(head) >= this->get_game_width()
		|| std::get<1>(head) >= this->get_game_height()
		|| std::get<0>(head) < 0 || std::get<1>(head) < 0)
		return (1);
	

	int coord = std::get<1>(head) * this->get_game_width() + std::get<0>(head);

	if (this->_map->at(coord) == CELL_SNAKE
		|| this->_map->at(coord) == CELL_ROCK)
		return (1);

	if (this->_map->at(coord) == CELL_FOOD)
	{
		for (auto it = this->_listFoods.begin(); it != this->_listFoods.end(); ++it)
		{
			if (std::get<0>(*it) == std::get<0>(head)
				&& std::get<1>(*it) == std::get<1>(head))
			{
				it = this->_listFoods.erase(it);
				return (2);
			}
		}
	}
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
	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		if ((*it)->getID() == id)
			return (*it);
	}
	return (NULL);
}

std::list <Snake *>		Engine::get_players_list(void) const
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
