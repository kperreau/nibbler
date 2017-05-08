/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 18:40:52 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"

Engine::Engine(int width, int height, int nb_players, uint32_t difficulty)
: _speed(150), _score(0), _difficulty(difficulty), _rate(0), _pause(false), _lib(F1)
{
	if (nb_players < 1 && nb_players > 4)
	{
		std::cerr << "Bad players number" << std::endl;
		return ;
	}
	
	if (width < (SQUARE + 50) * 2 * nb_players
		|| height < (SQUARE + 50) * 2 * nb_players)
	{
		std::cerr << "Window size too small" << std::endl;
		return ;
	}
	
	this->_nbPlayers = nb_players;
	this->_nbPlayersAlive = nb_players;
	this->_width = width - (width % SQUARE);
	this->_height = height - (height % SQUARE);
	
	// init map
	this->_map = Map(this->get_game_width(), this->get_game_height());
	
	// init players
	for (int i = 0; i < nb_players; ++i)
	{
		this->_listPlayers.push_back(
			new Snake(
				std::pair <int, int>(
					  this->_width / SQUARE / 2  - ((nb_players - 1) * 2) + i * 3
					, this->_height / SQUARE / 2 - 2
					)
				, this->_color[i]
				, this->_map
				)
			);
	}

	this->load_lib(this->_lib);
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
		this->_listPlayers.clear();
	this->load_lib(None);
	return ;
}

void					Engine::genFoods(void)
{
	std::srand(time(NULL));

	if (this->_nbPlayersAlive < 1
		|| static_cast<int>(this->_listFoods.size()) > this->_nbPlayersAlive)
		return ;
	
	for (int i = 0; i < this->_nbPlayersAlive - static_cast<int>(this->_listFoods.size()); ++i)
	{
		if (this->_map.getEmptyCells().size() < 1)
			return ;

		uint32_t	n = std::rand() % this->_map.getEmptyCells().size();
		auto		it = this->_map.getEmptyCells().begin();

		std::advance(it, n);

		this->_map.setCell(std::get<0>(*it), std::get<1>(*it), CELL_FOOD);
		this->_listFoods.push_back(std::pair <int, int>(std::get<0>(*it), std::get<1>(*it)));
		this->_map.getEmptyCells().erase(it);
	}
	return ;
}

void					Engine::genRocks(void)
{
	if (this->_difficulty < 3)
		return ;
	
	for (int i = 0; i < this->_score - static_cast<int>(this->_listRocks.size()); ++i)
	{
		uint32_t	n = std::rand() % this->_map.getEmptyCells().size();
		auto		it = this->_map.getEmptyCells().begin();
		std::advance(it, n);

		this->_map.setCell(std::get<0>(*it), std::get<1>(*it), CELL_ROCK);
		this->_listRocks.push_back(std::pair <int, int>(std::get<0>(*it), std::get<1>(*it)));
		this->_map.getEmptyCells().erase(it);
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
			this->_glib->draw(std::get<0>(*it2), std::get<1>(*it2), color);		// Draw snakes
		}
	}
	return ;
}

void					Engine::drawFoods(void)
{
	for (auto it = this->_listFoods.begin(); it != this->_listFoods.end(); ++it)
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0xff00ff);		// Draw foods
	return ;
}

void					Engine::drawRocks(void)
{
	for (auto it = this->_listRocks.begin(); it != this->_listRocks.end(); ++it)
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0x770033);		// Draw rocks
	return ;
}

void					Engine::getInputs(void)
{
	auto			time = Clock::now();
	static auto		oldtime = Clock::now();
	long			duration = 0;
	input			key = None;


	key = this->_glib->getInput(4);

	if (key == Exit)
		exit (0);

	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
	if (duration > this->_speed * 1000000)
	{
		if (key == Pause)
		{
			oldtime = Clock::now();
			this->_pause = !this->_pause;
		}
	}
	if (key >= F1 && key <= F3)
		this->load_lib(key);
	if (this->_pause)
		return ;
	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
		(*it)->setNextDir(this->_glib->getInput((*it)->getID()));
	return ;
}

int						Engine::load_lib(input lib)
{
	IGlib *			(*func_lib)();
	char *			error;
	static void *	handle = NULL;

	if (handle != NULL)
	{
		this->_glib->exit();
		dlclose(handle);
	}
	if (lib == None)
		return (0);
	switch (lib)
	{
		case F1:
			handle = dlopen("../mylib/sfml/libsfml.dylib", RTLD_NOW|RTLD_GLOBAL);
			break ;
		case F2:
			handle = dlopen("../mylib/sdl/libsdl.dylib", RTLD_NOW|RTLD_GLOBAL);
			break ;
		case F3:
			handle = dlopen("../mylib/glfw/libglfw_nibbler.dylib", RTLD_NOW|RTLD_GLOBAL);
			break ;
		default:
			handle = dlopen("../mylib/sfml/libsfml.dylib", RTLD_NOW|RTLD_GLOBAL);
	}
	if (!handle)
	{
		fputs (dlerror(), stderr);
		exit(1);
	}
	*(void**)&(func_lib) = dlsym(handle, "getGlib");
	if ((error = dlerror()) != NULL)
	{
		fputs(error, stderr);
		exit(1);
	}

	this->_glib = func_lib();
	this->_glib->init(this->_width, this->_height, SQUARE);		// create window
	this->_glib->clear();
	return (0);
}

void					Engine::run(void)
{
	auto	time = Clock::now();
	auto	oldtime = Clock::now();
	long	duration = 0;

	while (1)
	{
		this->getInputs();
		this->drawPlayers();
		this->drawFoods();
		this->drawRocks();
		this->_glib->display();
		time = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
		if (duration < this->_speed * 1000000 || this->_pause)
			continue ;
		oldtime = Clock::now();
		this->checkPlayers();
		this->genFoods();
		this->genRocks();
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
	int						collision = 0;
	std::pair <int, int>	head;

	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		head = (*it)->next_move();
		collision = this->checkCollision(std::get<0>(head), std::get<1>(head));
		if (collision == 1)
		{
			--this->_nbPlayersAlive;
			(*it)->set_isAlive(0);
		}
		else if (collision == 3 && (*it)->get_elems().back() != head)
		{
			(*it)->move();
			--this->_nbPlayersAlive;
			(*it)->set_isAlive(0);
		}
		else if (collision == 2)
		{
			(*it)->move();
			(*it)->eat();
			++this->_score;
			if (this->_difficulty > 1 && this->_speed > 50)
				this->_speed -= 2;
		}
		else
			(*it)->move();
	}
	
	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		if ((*it)->get_isAlive() == 0)
		{
			delete *it;
			it = this->_listPlayers.erase(it);
		}
	}
	return ;
}

int						Engine::checkCollision(int x, int y)
{
	if (x >= this->get_game_width()
		|| y >= this->get_game_height()
		|| x < 0 || y < 0)
		return (1);

	if (this->_map.getCell(x, y) == CELL_SNAKE)
		return (3);
	if (this->_map.getCell(x, y) == CELL_ROCK)
		return (1);

	if (this->_map.getCell(x, y) == CELL_FOOD)
	{
		std::pair <int, int>	head(x, y);
		auto it = std::find(this->_listFoods.begin(), this->_listFoods.end(), head);
		if (it != this->_listFoods.end())
		{
			this->_listFoods.erase(it);
			return (2);
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
