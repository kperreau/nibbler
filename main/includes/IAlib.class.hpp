/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAlib.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 19:20:40 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IALIB_CLASS_HPP
# define IALIB_CLASS_HPP
# include <iostream>
# include <list>
# include <string>
# include "Nibbler.hpp"

class IAlib
{
	public:
		virtual ~IAlib(void) {};
		//virtual IAlib &					operator=(IAlib const & rhd);
		virtual void					init(std::list <std::pair <std::string, e_sound> > sounds) = 0;
		virtual void					play(e_sound sound) = 0;
		virtual void					stop(e_sound sound) = 0;
		virtual void					exit(void) = 0;
};

#endif
