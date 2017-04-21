/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/21 17:42:15 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_CLASS_HPP
# define SFML_CLASS_HPP
# include <iostream>
# include <string>
# include <ctime>
# include <sstream>
# include <SFML/Graphics.hpp>

enum	input {
	None,
	Left,
	Right,
	Top,
	Bottom,
};

class Sfml
{
	public:
		Sfml(int width, int height);
		Sfml(Sfml const & src);
		~Sfml(void);
		Sfml &	operator=(Sfml const & rhd);
		sf::RenderWindow &		getWindow(void);
		void					display(void);
		void					clear(void);
		void					draw(int x, int y);
		input					getInput(void);

	private:
		int							_width;
		int							_height;
		sf::RenderWindow			_window;
};

//std::ostream &		operator<<(std::ostream & o, Sfml const & i);

#endif
