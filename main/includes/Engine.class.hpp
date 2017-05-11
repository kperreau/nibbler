/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 14:29:59 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_CLASS_HPP
# define ENGINE_CLASS_HPP
# include <iostream>
# include <string>
# include <algorithm>
# include <ctime>
# include <vector>
# include <sstream>
# include <cstdint>
# include <utility>
# include <chrono>
# include <ratio>
# include <dlfcn.h>
# include "Snake.class.hpp"
# include "IGlib.class.hpp"
# include "IAlib.class.hpp"
# include "Map.class.hpp"
# include <unistd.h>

# define SQUARE 16

typedef std::chrono::high_resolution_clock Clock;

class Engine
{
	public:
		Engine(int  width, int height, int nb_players, uint32_t difficulty);
		Engine(Engine const & src);
		~Engine(void);
		int						get_nbPlayers(void) const;
		int						get_width(void) const;
		int						get_height(void) const;
		int						get_game_width(void) const;
		int						get_game_height(void) const;
		Snake *					get_player_by_id(int id);
		std::list <Snake *>		get_players_list(void) const;
		void					run(void);
		void					checkPlayers(void);
		void					setRate(void);
		long					getRate(void) const;
		int						checkCollision(int x, int y);
		void					drawPlayers(void);
		void					drawFoods(void);
		void					drawRocks(void);
		void					drawMalus(void);
		void					resetMap(void);
		void					genFoods(void);
		void					genRocks(void);
		void					genMalus(void);
		void					getInputs(void);
		void					end(void);
		int						load_lib(input lib);
		Engine &				operator=(Engine const & rhs);

	private:
		int							_nbPlayers;
		int							_nbPlayersAlive;
		int							_height;
		int							_width;
		uint32_t					_speed;
		int							_score;
		uint32_t					_difficulty;
		long						_rate;
		IGlib *						_glib;
		IAlib *						_alib;
		bool						_pause;
		input						_lib;
		int const					_color[4] = {0xff, 0xff00, 0xff0000};
		std::list <Snake *>			_listPlayers;
		Map							_map;
		std::list <std::pair <std::string, e_sound> >	_sounds;
		std::list <std::pair <int, int> >		_listFoods;
		std::list <std::pair <int, int> >		_listRocks;
		std::list <std::pair <int, int> >		_listMalus;
};

std::ostream &		operator<<(std::ostream & o, Engine const & i);

#endif
