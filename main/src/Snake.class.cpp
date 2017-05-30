/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:05 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 20:20:47 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.class.hpp"

Snake::Snake(std::pair <int, int> start, int const color, Map & map)
: map(map), _id(_nextID++), _len(4), _isAlive(1), _dir(Top)
, _nextDir(None), _malus(0), _color(color)
{
	this->_elems.push_back(this->addElem(std::get<0>(start), std::get<1>(start)));
	++std::get<1>(start);
	this->_elems.push_back(this->addElem(std::get<0>(start), std::get<1>(start)));
	++std::get<1>(start);
	this->_elems.push_back(this->addElem(std::get<0>(start), std::get<1>(start)));
	++std::get<1>(start);
	this->_elems.push_back(this->addElem(std::get<0>(start), std::get<1>(start)));
	return ;
}

Snake::Snake(Snake const & src) : map(src.map), _id(_nextID++)
{
	*this = src;
	return ;
}

Snake::~Snake(void)
{
	for (auto it = this->_elems.begin(); it != this->_elems.end(); ++it)
	{
		this->map.setCell(std::get<0>(*it), std::get<1>(*it), CELL_DEFAULT);
		this->map.getEmptyCells().push_back(*it);
	}
	return ;
}

std::pair <int, int>	Snake::addElem(int x, int y)
{
	std::pair <int, int>	elem(x, y);
	this->map.delEmptyCell(elem);
	this->map.setCell(x, y, CELL_SNAKE);
	return (elem);
}

uint32_t		Snake::get_len(void) const
{
	return (this->_len);
}

int		Snake::checkDir(input val)
{
	if ((val == Top && this->_dir == Bottom)
		|| (val == Bottom && this->_dir == Top)
		|| (val == Left && this->_dir == Right)
		|| (val == Right && this->_dir == Left))
		return (0);
	return (1);
}

void		Snake::setDir(input val)
{
	if (this->checkDir(val) == 1)
		this->_dir = val;
	return ;
}

void		Snake::set_isAlive(char val)
{
	this->_isAlive = val;
	return ;
}

void		Snake::setNextDir(input val)
{
	if (val != None
		&& val != this->_nextDir.back())
		this->_nextDir.push_back(val);

	if (this->_nextDir.size() > 4)
		this->_nextDir.pop_front();

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

int			Snake::getColor(void) const
{
	return (this->_color);
}

int			Snake::getMalus(void) const
{
	return (this->_malus);
}

input		Snake::getDir(void) const
{
	return (this->_dir);
}

std::pair <int, int>	Snake::next_move(void)
{
	std::pair <int, int>	head;
	input					nextDir = this->_dir;

	if (this->_malus > 0)
	{
		if (this->_nextDir.front() == Left)
			this->_nextDir.front() = Right;
		else if (this->_nextDir.front() == Right)
			this->_nextDir.front() = Left;
		--this->_malus;
	}

	if (this->_nextDir.front() != None
		&& this->checkDir(this->_nextDir.front()) == 1)
		nextDir = this->_nextDir.front();
	switch (nextDir)
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
	return (head);
}

void			Snake::move(void)
{
	std::pair <int, int> head;

	if (this->_malus > 0)
	{
		if (this->_nextDir.front() == Left)
			this->_nextDir.front() = Right;
		else if (this->_nextDir.front() == Right)
			this->_nextDir.front() = Left;
		--this->_malus;
	}

	head = this->next_move();

	if (this->_nextDir.front() != None)
	{
		this->setDir(this->_nextDir.front());
		this->_nextDir.pop_front();
	}

	this->_last = this->_elems.back();
	this->map.getEmptyCells().push_back(this->_last);
	this->map.delEmptyCell(head);
	this->map.setCell(std::get<0>(this->_last), std::get<1>(this->_last), CELL_DEFAULT);
	this->map.setCell(std::get<0>(head), std::get<1>(head), CELL_SNAKE);
	this->_elems.pop_back();
	this->_elems.push_front(head);
	return ;
}

void			Snake::eat(void)
{
	this->map.setCell(std::get<0>(this->_last), std::get<1>(this->_last), CELL_SNAKE);
	this->map.delEmptyCell(this->_last);
	this->_elems.push_back(this->_last);
	return ;
}

void			Snake::eatMalus(void)
{
	this->map.setCell(
		  std::get<0>(this->_elems.front())
		, std::get<1>(this->_elems.front())
		, CELL_SNAKE
		);
	if (this->_malus < 100)
		this->_malus += 30;
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
	this->map = rhs.map;
	//this->_nextDir = Top;
	return (*this);
}

int Snake::_nextID = 0;
