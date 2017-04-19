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
# include <ctime>
# include <vector>
# include <sstream>
# include <cstdint>
# include <utility>
# include <chrono>
# include <ratio>
# include "Snake.class.hpp"

# define SQUARE 8

typedef std::chrono::high_resolution_clock Clock;



class Engine
{
	public:
		Engine(uint32_t width, uint32_t height, uint32_t nb_players);
		Engine(Engine const & src);
		~Engine(void);
		uint32_t				get_nbPlayers(void) const;
		uint32_t				get_width(void) const;
		uint32_t				get_height(void) const;
		uint32_t				get_game_width(void) const;
		uint32_t				get_game_height(void) const;
		Snake const *			get_player_by_id(uint32_t id) const;
		std::vector <Snake *>	get_players_list(void) const;
		void					run(void);
		void					checkPlayers(void);
		void					setRate(void);
		long					getRate(void) const;
		int						checkCollision(Snake const & snake);
		Engine &				operator=(Engine const & rhs);

	private:
		uint32_t					_nbPlayers;
		uint32_t					_nbPlayersAlive;
		uint32_t					_height;
		uint32_t					_width;
		long						_rate;
		// std::vector <Snake> *		_listPlayers;
		std::vector <Snake *>		_listPlayers;
};

std::ostream &		operator<<(std::ostream & o, Engine const & i);

#endif
