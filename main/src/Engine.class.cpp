/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 19:51:06 by kperreau         ###   ########.fr       */
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

	// sounds file
	this->_sounds.push_back(std::pair <std::string, e_sound>("./data/music.wav", S_MUSIC));
	this->_sounds.push_back(std::pair <std::string, e_sound>("./data/ouh.wav", S_COLLISION));
	this->_sounds.push_back(std::pair <std::string, e_sound>("./data/piece.wav", S_EAT));
	this->_sounds.push_back(std::pair <std::string, e_sound>("./data/malus.wav", S_MALUS));
	this->_sounds.push_back(std::pair <std::string, e_sound>("./data/end.wav", S_END));

	try {
		this->load_lib(this->_lib);
	}
	catch (std::exception const & e){
		std::cerr << "ERREUR : " << e.what() << std::endl;
		exit (-1);
	}
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
	return ;
}

// ---------
// Fonctions qui generes les foods + malus + obstacles sur la map
// ----------
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
	std::srand(time(NULL));

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

void					Engine::genMalus(void)
{
	std::srand(time(NULL));

	if (this->_difficulty < 4
		|| std::rand() % 10 < 6)
		return ;
	uint32_t	n = std::rand() % this->_map.getEmptyCells().size();
	auto		it = this->_map.getEmptyCells().begin();
	std::advance(it, n);

	this->_map.setCell(std::get<0>(*it), std::get<1>(*it), CELL_MALUS);
	this->_listMalus.push_back(std::pair <int, int>(std::get<0>(*it), std::get<1>(*it)));
	this->_map.getEmptyCells().erase(it);
	return ;
}
// ---------
// Fin des fonctions qui genere
// ---------


// ---------
// Fonctions qui dessine dans le buffer des libs graphiques
// ----------
void					Engine::drawPlayers(void)
{
	int  color = 0;

	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		auto elem = (*it)->get_elems();
		for (auto it2 = elem.begin(); it2 != elem.end(); ++it2)
		{
			color = (*it)->getColor();

			if ((*it)->getMalus() > 0)
				color /= 2;
			if (it2 == elem.begin())
			{
				color /= 2;
				this->_glib->draw(std::get<0>(*it2), std::get<1>(*it2), color, CELL_HEAD);		// Draw snakes
			}
			else
				this->_glib->draw(std::get<0>(*it2), std::get<1>(*it2), color, CELL_SNAKE);		// Draw snakes
		}
	}
	return ;
}

void					Engine::drawFoods(void)
{
	for (auto it = this->_listFoods.begin(); it != this->_listFoods.end(); ++it)
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0xff00ff, CELL_FOOD);		// Draw foods
	return ;
}

void					Engine::drawRocks(void)
{
	for (auto it = this->_listRocks.begin(); it != this->_listRocks.end(); ++it)
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0x770033, CELL_ROCK);		// Draw rocks
	return ;
}

void					Engine::drawMalus(void)
{
	for (auto it = this->_listMalus.begin(); it != this->_listMalus.end(); ++it)
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0xaa00a5, CELL_MALUS);		// Draw malus
	return ;
}

void					Engine::drawDefault(void)
{
	for (auto it = this->_map.getEmptyCells().begin(); it != this->_map.getEmptyCells().end(); ++it)
		this->_glib->draw(std::get<0>(*it), std::get<1>(*it), 0, CELL_DEFAULT);		// Draw default
	return ;
}
// ---------
// Fin des fonctions qui dessine
// ---------


// Affiche du texte
void					Engine::drawText(void)
{
	this->_glib->write("", 0xffffff);
	if (this->_pause)
		this->_glib->write("PAUSE", 0xffffff);
	return ;
}


// Gestion des touches calviers
void					Engine::getInputs(void)
{
	auto				time = Clock::now();
	static auto			oldtime = Clock::now();
	long				duration = 0;
	std::list <std::pair <input, int> >	keys;
	Snake * p = NULL;


	keys = this->_glib->getInput(0);
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		switch (std::get<0>(*it))
		{
			case Exit:
				delete this->_alib;
				delete this->_glib;
				exit (0);
			case F4:
				this->_glib->setTexture();
				break ;
			case F1:
			case F2:
			case F3:
				try {
					this->load_lib(std::get<0>(*it));
				}
				catch (std::exception const & e){
					std::cerr << "ERREUR : " << e.what() << std::endl;
					delete this->_alib;
					exit (-1);
				}
				break ;
			case Left:
			case Right:
			case Top:
			case Bottom:
				if (this->_pause)
					continue ;
				p = this->get_player_by_id(std::get<1>(*it));
				if (p != NULL)
					p->setNextDir(std::get<0>(*it));
				break ;
			case Pause:
				if (duration > this->_speed * 1000000)
				{
					oldtime = Clock::now();
					this->_pause = !this->_pause;
				}
				break ;
			default:
				break ;
		}
	}
	return ;
}

// Load des libs dynamiques graphiques avec F1 F2 F3
int						Engine::load_lib(input lib)
{
	IGlib *			(*func_lib)();
	char *			error;
	static void *	handle = NULL;

	if (handle != NULL)
	{
		this->_glib->exit();
		delete this->_glib;
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
		throw std::runtime_error(dlerror());
		return (-1);
	}
	*(void**)&(func_lib) = dlsym(handle, "getGlib");
	if ((error = dlerror()) != NULL)
	{
		throw std::runtime_error(error);
		return (-1);
	}

	this->_glib = func_lib();
	try {
		this->_glib->init(this->_width, this->_height, SQUARE);		// create window
	}
	catch (std::exception const & e) {
		std::cerr << "ERREUR : " << e.what() << std::endl;
		delete this->_glib;
		exit (-1);
	}
	this->_glib->clear();
	return (0);
}

// fonction de fin du jeu
void					Engine::end(void)
{
	std::cout << "Game over" << std::endl;
	this->_alib->stop(S_MUSIC);
	this->_alib->play(S_END);
	usleep(4000000);
	this->_alib->stop(S_END);
	delete this->_alib;
	delete this->_glib;
	return ;
}

// Fonction de l'init / load de la lib audio
void					Engine::get_lib_audio(void)
{
	IAlib*	(*func_alib)();
	char*	error;
	void*	handle;

	// lib audio
	handle = dlopen("../mylib/audio/libaudio.dylib", RTLD_NOW|RTLD_GLOBAL);
	if (!handle)
	{
		throw std::runtime_error(dlerror());
		return ;
	}
	*(void**)&(func_alib) = dlsym(handle, "getAlib");
	if ((error = dlerror()) != NULL)
	{
		throw std::runtime_error(error);
		return ;
	}
	this->_alib = func_alib();

	try {
		this->_alib->init(this->_sounds);		// init audio
	}
	catch (std::exception const & e){
		std::cerr << "ERREUR : " << e.what() << std::endl;
		delete this->_alib;
		exit (-1);
	}
	this->_alib->play(S_MUSIC);				// play music
	return ;
}


// On affiche tous a l'ecran
void					Engine::display(void)
{
	this->drawPlayers();
	this->drawFoods();
	this->drawRocks();
	this->drawDefault();
	this->drawMalus();
	this->drawText();
	this->_glib->display();
	return ;
}

void					Engine::run(void)
{
	auto	time = Clock::now();
	auto	oldtime = Clock::now();
	long	duration = 0;

	// Initialisation de la lib audio
	try {
		this->get_lib_audio();
	}
	catch (std::exception const & e){
		std::cerr << "ERREUR : " << e.what() << std::endl;
		exit (-1);
	}

	while (1)
	{
		// On recupere les inputs claviers
		this->getInputs();

		// On affiche a l'ecran
		this->display();

		// La boucle principale
		time = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time - oldtime).count();
		if (duration < this->_speed * 1000000 || this->_pause)
			continue ;
		oldtime = Clock::now();

		// collision + food + malus + etc..
		this->checkPlayers();

		// Generation des food et rocks sur la map
		this->genFoods();
		this->genRocks();

		// Fin du jeu, on quitte
		if (this->_nbPlayersAlive < 1)
		{
			this->end();
			break ;
		}
	}
	//dlclose(handle);
	return ;
}

// Gestions de toutes les colisions et conséquences (Core du jeu)
void					Engine::checkPlayers(void)
{
	int						collision = 0;
	std::pair <int, int>	head;

	for (auto it = this->_listPlayers.begin(); it != this->_listPlayers.end(); ++it)
	{
		head = (*it)->next_move();
		collision = this->checkCollision(std::get<0>(head), std::get<1>(head));
		switch (collision)
		{
			case CELL_BORDER:
			case CELL_ROCK:
				this->_alib->play(S_COLLISION);
				--this->_nbPlayersAlive;
				(*it)->set_isAlive(0);
				break ;
			case CELL_SNAKE:
				if ((*it)->get_elems().back() != head)
				{
					(*it)->move();
					this->_alib->play(S_COLLISION);
					--this->_nbPlayersAlive;
					(*it)->set_isAlive(0);
				}
				else
					(*it)->move();
				break ;
			case CELL_FOOD:
				this->_alib->play(S_EAT);
				(*it)->move();
				(*it)->eat();
				this->genMalus();
				++this->_score;
				if (this->_difficulty > 1 && this->_speed > 50)
					this->_speed -= 2;
				break ;
			case CELL_MALUS:
				this->_alib->play(S_MALUS);
				(*it)->move();
				(*it)->eatMalus();
				break ;
			default:
				(*it)->move();
		}
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

// Check le type d'une cellule et s'il y a collision
cell					Engine::checkCollision(int x, int y)
{
	cell					c_cell;
	std::pair <int, int>	head(x, y);
	std::list<std::pair <int, int> >::iterator		it;

	if (x >= this->get_game_width()
		|| y >= this->get_game_height()
		|| x < 0 || y < 0)
		return (CELL_BORDER);

	c_cell = this->_map.getCell(x, y);
	switch (c_cell)
	{
		case CELL_MALUS:
			it = std::find(this->_listMalus.begin(), this->_listMalus.end(), head);
			if (it != this->_listMalus.end())
			{
				this->_listMalus.erase(it);
				return (CELL_MALUS);
			}
			break ;
		case CELL_FOOD:
			it = std::find(this->_listFoods.begin(), this->_listFoods.end(), head);
			if (it != this->_listFoods.end())
			{
				this->_listFoods.erase(it);
				return (CELL_FOOD);
			}
			break ;
		default:
			return (c_cell);
	}
	return (CELL_DEFAULT);
}

// -------
// Les Geteurs et Seteurs
// -------

long					Engine::getRate(void) const
{
	return (this->_rate);
}

void					Engine::setRate(void)
{
	return ;
}

Snake		*			Engine::get_player_by_id(int id)
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
