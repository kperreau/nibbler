/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:32 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/21 17:42:33 by kperreau         ###   ########.fr       */
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

class Snake
{
	public:
		Snake(std::pair <int, int> const & start, int const color);
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
		void					eat(void);
		std::pair <int, int>	next_move(void);
		int						checkDir(input val);
		std::list <std::pair <int, int> > const &	get_elems(void) const;

	private:
		uint32_t			_len;
		char				_isAlive;
		input				_dir;
		input				_nextDir;
		const int			_id;
		uint32_t			_speed;
		int					_color;
		static int			_nextID;
		std::pair <int, int>_last;
		std::list <std::pair <int, int> >		_elems;
};

std::ostream &		operator<<(std::ostream & o, Snake const & i);

#endif
