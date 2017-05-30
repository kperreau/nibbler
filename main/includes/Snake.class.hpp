/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:32 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 19:21:13 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_CLASS_HPP
# define SNAKE_CLASS_HPP
# include <iostream>
# include <string>
# include <list>
# include <sstream>
# include <cstdint>
# include <utility>
# include "IGlib.class.hpp"
# include "Map.class.hpp"

class Snake
{
	public:
		Snake(std::pair <int, int> start, int const color, Map & map);
		Snake(Snake const & src);
		~Snake(void);
		Snake &					operator=(Snake const & rhs);
		uint32_t				get_len(void) const;
		void					move(void);
		void					set_isAlive(char val);
		char					get_isAlive(void) const;
		input					getDir(void) const;
		void					setNextDir(input val);
		void					setDir(input val);
		int						getID(void) const;
		int						getColor(void) const;
		int						getMalus(void) const;
		void					eat(void);
		void					eatMalus(void);
		std::pair <int, int>	next_move(void);
		std::pair <int, int>	addElem(int x, int y);
		int						checkDir(input val);
		std::list <std::pair <int, int> > const &	get_elems(void) const;

		Map &				map;

	private:
		const int			_id;
		uint32_t			_len;
		char				_isAlive;
		input				_dir;
		std::list <input>	_nextDir;
		int					_malus;
		//uint32_t			_speed;
		int					_color;
		static int			_nextID;
		std::pair <int, int>_last;
		std::list <std::pair <int, int> >		_elems;
};

std::ostream &		operator<<(std::ostream & o, Snake const & i);

#endif
