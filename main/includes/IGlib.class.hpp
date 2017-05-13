/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 14:42:47 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGLIB_CLASS_HPP
# define IGLIB_CLASS_HPP
# include <iostream>
# include <list>
# include <string>

enum	input {
	None,
	Left,
	Right,
	Top,
	Bottom,
	Exit,
	Pause,
	F1,
	F2,
	F3
};

class IGlib
{
	public:
		virtual ~IGlib(void) {};
		//virtual IGlib &					operator=(IGlib const & rhd);
		virtual void					init(int width, int height, int square) = 0;
		virtual void					display(void) = 0;
		virtual void					clear(void) = 0;
		virtual void					exit(void) = 0;
		virtual void					draw(int x, int y, int color) = 0;
		virtual void					write(std::string str, int color) = 0;
		virtual std::list <std::pair <input, int> >		getInput(int id) = 0;
		virtual int						getColor(int color, int type) = 0;
};

#endif
