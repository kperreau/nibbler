/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:32 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 18:52:58 by kperreau         ###   ########.fr       */
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
		Snake(std::string const & str);
		Snake(Snake const & src);
		~Snake(void);

	private:
		uint32_t									_len;
		std::list <std::pair <uint32_t, uint32_t>>	_elems;
};

std::ostream &		operator<<(std::ostream & o, Snake const & i);

#endif
