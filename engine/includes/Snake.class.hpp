/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:32 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 19:39:20 by kperreau         ###   ########.fr       */
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

enum	input {
	Left,
	Right,
	Top,
	Bottom,
};

class Snake
{
	public:
		Snake(std::pair <int, int> const & start);
		Snake(Snake const & src);
		~Snake(void);
		Snake &				operator=(Snake const & rhs);
		uint32_t			get_len(void) const;
		void				move(void);
		void				set_isAlive(char val);
		char				get_isAlive(void) const;
		input				getDir(void) const;
		uint32_t			getID(void) const;
		std::list <std::pair <int, int> > const &	get_elems(void) const;

	private:
		uint32_t			_len;
		char				_isAlive;
		input				_dir;
		const uint32_t		_id;
		uint32_t			_speed;
		static uint32_t		_nextID;
		std::list <std::pair <int, int> >		_elems;
};

std::ostream &		operator<<(std::ostream & o, Snake const & i);

#endif
