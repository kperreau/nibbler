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

class Snake
{
	public:
		Snake(void);
		Snake(Snake const & src);
		~Snake(void);
		Snake &												operator=(Snake const & rhs);
		uint32_t											get_len(void) const;
		std::list <std::pair <uint32_t, uint32_t> > const &	get_elems(void) const;

	private:
		uint32_t			_len;
		uint32_t			_dir;
		const uint32_t		_id;
		static uint32_t		_nextID;
		std::list <std::pair <uint32_t, uint32_t> >		_elems;
};

std::ostream &		operator<<(std::ostream & o, Snake const & i);

#endif
