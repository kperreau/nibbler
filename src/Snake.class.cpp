/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:05 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 20:18:55 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.class.hpp"

Snake::Snake(void) : _len(1), _id(_nextID++)
{
	std::cout << "snake id: " << _id << std::endl;
	return ;
}

Snake::Snake(Snake const & src) : _id(_nextID++)
{
	*this = src;
	return ;
}

Snake::~Snake(void)
{
	return ;
}

uint32_t		Snake::get_len(void) const
{
	return (this->_len);
}

std::list <std::pair <uint32_t, uint32_t> > const &		Snake::get_elems(void) const
{
	return (this->_elems);
}


Snake &			Snake::operator=(Snake const & rhs)
{
	this->_len = rhs.get_len();
	this->_elems = rhs.get_elems();
	return (*this);
}

uint32_t Snake::_nextID = 0;