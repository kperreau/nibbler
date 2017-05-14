/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 20:54:16 by kperreau         ###   ########.fr       */
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
# include <GLFW/glfw3.h>

class Glib : public IGlib
{
	public:
		Glib(void);
		Glib(Glib const & src);
		~Glib(void);
		//IGlib &	operator=(IGlib const & rhd);
		GLFWwindow*				getWindow(void);
		void					display(void);
		void					init(int width, int height, int square);
		void					clear(void);
		void					exit(void);
		void					setTexture(void);
		void					draw(int x, int y, int color, cell c);
		void					write(std::string str, int color);
		std::list <std::pair <input, int> >		getInput(int id);
		int						getColor(int color, int type);
		void					centerWindow(void);

	private:
		int							_width;
		int							_height;
		int							_square;
		GLFWwindow*					_window;
		std::map<int, std::pair<input, int> >	_input;
		bool						_texture;
};

//std::ostream &		operator<<(std::ostream & o, Glib const & i);

#endif
