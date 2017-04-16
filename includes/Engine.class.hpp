/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 19:13:57 by kperreau         ###   ########.fr       */
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
		Engine(uint32_t nb_players);
		Engine(Engine const & src);
		~Engine(void);
		uint32_t	get_nbPlayers(void) const;
		Engine &	operator=(Engine const & rhs);

	private:
		uint32_t	_nbPlayers;
};

std::ostream &		operator<<(std::ostream & o, Engine const & i);

#endif
