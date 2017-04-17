/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 20:18:36 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"

Engine::Engine(uint32_t width, uint32_t height, uint32_t nb_players)
{
	if (nb_players < 1 && nb_players > 4)
		exit (-1);
	
	this->_nbPlayers = nb_players;
	this->_listPlayers = new std::vector <Snake> (nb_players);
	this->_width = width;
	this->_height = height;
	// this->run();		// run the game
	return ;
}

Engine::Engine(Engine const & src)
{
	*this = src;
	return ;
}

Engine::~Engine(void)
{
	this->_listPlayers->clear();
	return ;
}

void					Engine::run(void)
{
	while (1)
	{
		
	}
	return ;
}

Snake const &			Engine::get_player_by_id(uint32_t id) const
{
	return (this->_listPlayers->at(id));
}

std::vector <Snake> *	Engine::get_players_list(void) const
{
	return (this->_listPlayers);
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
