/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/04 17:10:28 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLIB_CLASS_HPP
# define GLIB_CLASS_HPP
# include <iostream>
# include <string>
# include <ctime>
# include <sstream>
# include <map>
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
		void					draw(int x, int y, int color);
		input					getInput(int id);
		int						getColor(int color, int type);

	private:
		int							_width;
		int							_height;
		int							_square;
		SDL_Window*					_window;
		SDL_Renderer*				_renderer;
		std::map<int, std::map<int, input> >		_input;
};

//std::ostream &		operator<<(std::ostream & o, Glib const & i);

#endif
