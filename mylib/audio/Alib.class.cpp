/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Alib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 19:24:59 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Alib.class.hpp"

Alib::Alib()
{

	return ;
}

Alib::~Alib(void)
{
	return ;
}

Alib::Alib(Alib const & src)
{
	//*this = src;
	return ;
}

void				Alib::init(std::list <std::pair <std::string, e_sound> > sounds)
{
	sf::Sound			sound;
	sf::SoundBuffer		buff;

	this->_music.setLoop(true);
	this->_music.setVolume(80);
	for (auto it = sounds.begin(); it != sounds.end(); ++it)
	{
		if (std::get<1>(*it) == S_MUSIC)
		{
			if (!this->_music.openFromFile(std::get<0>(*it)))
			{
				std::stringstream	ss;
				ss << "Unable to load audio file: " << std::get<0>(*it);
				throw std::runtime_error(ss.str());
				return ;
			}
		}
		else
		{
			if (!buff.loadFromFile(std::get<0>(*it)))
			{
				std::stringstream	ss;
				ss << "Unable to load audio file: " << std::get<0>(*it);
				throw std::runtime_error(ss.str());
				return ;
			}
			this->_sounds[(*it).second] = std::pair <sf::SoundBuffer, sf::Sound>(buff, sound);
			this->_sounds[(*it).second].second.setBuffer(this->_sounds[(*it).second].first);
		}
	}
	return ;
}

void			Alib::play(e_sound es)
{
	sf::Sound	sound;

	if (es == S_MUSIC)
		this->_music.play();
	else if (this->_sounds.count(es))
		this->_sounds[es].second.play();

	return ;
}

void			Alib::stop(e_sound es)
{
	if (es == S_MUSIC)
		this->_music.stop();
	else if (this->_sounds.count(es))
		this->_sounds[es].second.stop();
	return ;
}

void			Alib::exit(void)
{
	return ;
}

/*IGlib &			Glib::operator=(IGlib const & rhd)
{
	return (*this);
}
*/

extern "C" Alib *		getAlib()
{
	return (new Alib());
}
