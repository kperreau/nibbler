/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:29:32 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/14 19:51:14 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_CLASS_HPP
# define NIBBLER_CLASS_HPP

enum	cell {
	CELL_DEFAULT,
	CELL_SNAKE,
	CELL_FOOD,
	CELL_ROCK,
	CELL_MALUS,
	CELL_BORDER
};

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
	F3,
	F4
};

enum e_sound
{
	S_COLLISION,
	S_EAT,
	S_MALUS,
	S_MUSIC,
	S_END
};

#endif
