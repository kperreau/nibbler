/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:32 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/05 21:19:57 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CLASS_HPP
# define MAP_CLASS_HPP
# include <iostream>
# include <string>
# include <list>
# include <sstream>
# include <cstdint>
# include <utility>
# include <vector>

enum	cell {
	CELL_DEFAULT,
	CELL_SNAKE,
	CELL_FOOD,
	CELL_ROCK,
	CELL_MALUS
};

class Map
{
	public:
		Map(void);
		Map(int width, int height);
		Map(Map const & src);
		~Map(void);
		Map &								operator=(Map const & rhs);
		int									getWidth(void) const;
		int									getHeight(void) const;
		cell								getCell(int x, int y);
		void								setCell(int x, int y, cell type);
		std::vector <cell> const &			getMap(void) const;
		std::list <std::pair <int, int> > &	getEmptyCells(void);
		void								delEmptyCell(std::pair <int, int> empty_cell);
		void								initEmptyCells(void);

	private:
		int										_width;
		int										_height;
		std::vector <cell>						_map;
		std::list <std::pair <int, int> >		_emptyCells;
};

std::ostream &		operator<<(std::ostream & o, Map const & i);

#endif
