/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Alib.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:24:09 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 14:43:01 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIB_CLASS_HPP
# define ALIB_CLASS_HPP
# include <iostream>
# include <string>
# include <ctime>
# include <list>
# include <map>
# include <sstream>
# include <../../main/includes/IAlib.class.hpp>
# include <SFML/Audio.hpp>

class Alib : public IAlib
{
	public:
		Alib(void);
		Alib(Alib const & src);
		~Alib(void);
		//IAlib &	operator=(AGlib const & rhd);
		void					play(e_sound sound);
		void					init(std::list <std::pair <std::string, e_sound> > sounds);
		void					stop(e_sound sound);
		void					exit(void);

	private:
		std::map <e_sound, std::pair <sf::SoundBuffer, sf::Sound> >	_sounds;
		sf::Music						_music;
		//sf::SoundBuffer					_buffer;
};

//std::ostream &		operator<<(std::ostream & o, Alib const & i);

#endif
