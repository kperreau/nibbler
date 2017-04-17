/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 19:16:21 by kperreau          #+#    #+#             */
/*   Updated: 2017/04/16 20:16:54 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include "Engine.class.hpp"
#include "Snake.class.hpp"

typedef struct	s_opts
{
	bool		verbose = false;
	uint32_t	width = 0;
	uint32_t	height = 0;
	uint32_t	players = 1;
}				t_opts;

void		put_error(std::string error)
{
	std::cerr << "Error: " << error << std::endl;
	exit(1);
}

void		usage(char *name)
{
	std::cout << "usage: " << name << " [rsvnf] [file]" << std::endl;
	std::cout << "'-v' for a verbose output" << std::endl;
	std::cout << "'-x size' to set width of window" << std::endl;
	std::cout << "'-y size' to set height of window" << std::endl;
	std::cout << "'-p' to specify number of players " << std::endl;
	std::cout << "'-h' to print this help" << std::endl;
	std::exit(0);
}

t_opts		options(int ac, char **av)
{
	t_opts	opts;
	int		ch;

	while ((ch = getopt(ac, av, "hx:y:vp:")) != -1)
	{
		switch (ch)
		{
			case 'h':
				usage(av[0]);
			case 'x':
				opts.height = atoi(optarg);
				break;
			case 'y':
				opts.width = atoi(optarg);
				break;
			case 'p':
				opts.players = atoi(optarg);
				break;
			case 'v':
				opts.verbose = true;
				break;
			case '?':
			default:
				usage(av[0]);
				break;
		}
	}
	ac -= optind;
	av += optind;
	if (!opts.width || !opts.height)
		put_error("You have to specify the window size");
	return (opts);
}

int		main(int ac, char **av)
{
	t_opts		opts;

	opts = options(ac, av);

	Engine	engine(opts.width, opts.height, opts.players);
	return (0);
}
