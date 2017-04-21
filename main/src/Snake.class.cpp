/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:05 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/21 17:46:29 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.class.hpp"

Snake::Snake(std::pair <int, int> const & start)
: _len(4), _isAlive(1), _dir(Top), _id(_nextID++)
{
	this->_elems.push_back(std::pair <int, int>(std::get<0>(start), std::get<1>(start)));
	this->_elems.push_back(std::pair <int, int>(std::get<0>(start), std::get<1>(start) + 1));
	this->_elems.push_back(std::pair <int, int>(std::get<0>(start), std::get<1>(start) + 2));
	this->_elems.push_back(std::pair <int, int>(std::get<0>(start), std::get<1>(start) + 3));
	std::cout << "snake id: " << _id << " is new" << std::endl;
	// std::cout << "x: " << std::get<0>(start) << std::endl;
	// std::cout << "y: " << std::get<1>(start) << std::endl;
	return ;
}

Snake::Snake(Snake const & src) : _id(_nextID++)
{
	*this = src;
	return ;
}

Snake::~Snake(void)
{
	std::cout << "snake id: " << _id << " is dead" << std::endl;
	return ;
}

uint32_t		Snake::get_len(void) const
{
	return (this->_len);
}

void		Snake::setDir(input val)
{
	this->_dir = val;
	return ;
}

void		Snake::set_isAlive(char val)
{
	this->_isAlive = val;
	return ;
}

char		Snake::get_isAlive(void) const
{
	return (this->_isAlive);
}

int			Snake::getID(void) const
{
	return (this->_id);
}

input		Snake::getDir(void) const
{
	return (this->_dir);
}

void			Snake::move(void)
{
	std::pair <int, int> head;

	std::cout << "snake id: " << _id << " is moving" << std::endl;

	switch (this->_dir)
	{
		case Top:
			std::get<0>(head) = std::get<0>(this->_elems.front());
			std::get<1>(head) = std::get<1>(this->_elems.front()) - 1;
			break ;
		case Left:
			std::get<0>(head) = std::get<0>(this->_elems.front()) - 1;
			std::get<1>(head) = std::get<1>(this->_elems.front());
			break ;
		case Bottom:
			std::get<0>(head) = std::get<0>(this->_elems.front());
			std::get<1>(head) = std::get<1>(this->_elems.front()) + 1;
			break ;
		case Right:
			std::get<0>(head) = std::get<0>(this->_elems.front()) + 1;
			std::get<1>(head) = std::get<1>(this->_elems.front());
			break ;
		default:
			std::get<0>(head) = std::get<0>(this->_elems.front());
			std::get<1>(head) = std::get<1>(this->_elems.front()) - 1;
	}
	
	//std::cout << "x: " << std::get<0>(head) << std::endl;
	//std::cout << "y: " << std::get<1>(head) << std::endl;
	
	this->_elems.pop_back();
	this->_elems.push_front(head);
	return ;
}

std::list <std::pair <int, int> > const &		Snake::get_elems(void) const
{
	return (this->_elems);
}


Snake &			Snake::operator=(Snake const & rhs)
{
	this->_len = rhs.get_len();
	this->_isAlive = rhs.get_isAlive();
	this->_elems = rhs.get_elems();
	this->_dir = Top;
	return (*this);
}

int Snake::_nextID = 0;
