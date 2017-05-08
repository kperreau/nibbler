/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:05 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 14:10:03 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.class.hpp"

Map::Map(void)
{
	return ;
}

Map::Map(int width, int height) : _width(width), _height(height)
{
	this->_map.assign(
		  this->_width * this->_height
		, CELL_DEFAULT
		);
	this->initEmptyCells();
	return ;
}


Map::Map(Map const & src)
{
	*this = src;
	return ;
}

Map::~Map(void)
{
	return ;
}

void						Map::initEmptyCells(void)
{
	this->_emptyCells.clear();
	for (int i = 0; i < static_cast<int>(this->_map.size()); ++i)
	{
		if (this->_map.at(i) != CELL_DEFAULT)
			continue ;
		this->_emptyCells.push_back(
			std::pair <int, int>(
				  i % this->_width
				, i / this->_width
				)
			);
	}
	return ;
}

cell						Map::getCell(int x, int y)
{
	return (this->_map.at(y * this->_width + x));
}

int						Map::getWidth(void) const
{
	return (this->_width);
}

std::list <std::pair <int, int> > &	Map::getEmptyCells(void)
{
	return (this->_emptyCells);
}

void					Map::delEmptyCell(std::pair <int, int> empty_cell)
{
	for (auto it = this->_emptyCells.begin(); it != this->_emptyCells.end(); ++it)
	{
		if (empty_cell == *it)
			it = this->_emptyCells.erase(it);
	}

	return ;
}

int						Map::getHeight(void) const
{
	return (this->_height);
}

void						Map::setCell(int x, int y, cell type)
{
	this->_map.at(y * this->_width + x) = type;
	return ;
}

std::vector <cell> const &	Map::getMap(void) const
{
	return (this->_map);
}

Map &				Map::operator=(Map const & rhs)
{
	this->_width = rhs.getWidth();
	this->_height = rhs.getHeight();
	this->_map = rhs.getMap();
	this->initEmptyCells();
	//this->_emptyCells = rhs.getEmptyCells();
	return (*this);
}
