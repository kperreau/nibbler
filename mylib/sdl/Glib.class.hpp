/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 20:53:43 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLIB_CLASS_HPP
# define GLIB_CLASS_HPP
# include <iostream>
# include <string>
# include <ctime>
# include <sstream>
# include <map>
# include <list>
# include <../../main/includes/IGlib.class.hpp>
# include <SDL.h>

class Glib : public IGlib
{
	public:
		Glib(void);
		Glib(Glib const & src);
		~Glib(void);
		//IGlib &	operator=(IGlib const & rhd);
		SDL_Window*				getWindow(void);
		void					display(void);
		void					init(int width, int height, int square);
		void					clear(void);
		void					exit(void);
		void					setTexture(void);
		void					draw(int x, int y, int color, cell c);
		void					write(std::string str, int color);
		std::list <std::pair <input, int> >		getInput(void);
		int						getColor(int color, int type);
		void					drawSqure(int x, int y);

	private:
		const Uint8					*_state;
		int							_width;
		int							_height;
		int							_square;
		SDL_Window*					_window;
		SDL_Renderer*				_renderer;
		std::map<int, std::pair<input, int> >		_input;
		bool						_texture;
};

//std::ostream &		operator<<(std::ostream & o, Glib const & i);

#endif
