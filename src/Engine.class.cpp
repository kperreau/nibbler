/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 19:16:06 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"

Engine::Engine(void) : _nbPlayers(1)
{
	return ;
}


Engine::Engine(uint32_t nb_players)
{
	if (nb_players > 0 && nb_players < 5)
		this->_nbPlayers = nb_players;
	return ;
}

Engine::Engine(Engine const & src)
{
	*this = src;
	return ;
}

uint32_t		Engine::get_nbPlayers(void) const
{
	return (this->_nbPlayers);
}

Engine &			Engine::operator=(Engine const & rhs)
{
	this->_nbPlayers = rhs.get_nbPlayers();
	return (*this);
}
