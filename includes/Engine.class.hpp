/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 20:16:16 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_CLASS_HPP
# define ENGINE_CLASS_HPP
# include <iostream>
# include <string>
# include <list>
# include <sstream>
# include <cstdint>
# include <utility>

class Engine
{
	public:
		Engine(void);
		Engine(uint32_t width, uint32_t height, uint32_t nb_players);
		Engine(Engine const & src);
		~Engine(void);
		uint32_t	get_nbPlayers(void) const;
		uint32_t	get_width(void) const;
		uint32_t	get_height(void) const;
		Engine &	operator=(Engine const & rhs);

	private:
		uint32_t	_nbPlayers;
		uint32_t	_height;
		uint32_t	_width;
};

std::ostream &		operator<<(std::ostream & o, Engine const & i);

#endif
