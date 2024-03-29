/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 19:16:21 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 14:23:23 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <dlfcn.h>
#include <regex>
#include "Engine.class.hpp"
#include "Snake.class.hpp"

typedef struct	s_opts
{
	bool		verbose = false;
	int			width = 0;
	int			height = 0;
	uint32_t	players = 1;
	uint32_t	difficulty = 1;
}				t_opts;

void		put_error(std::string error)
{
	std::cerr << "Error: " << error << std::endl;
	exit(1);
}

void		usage(char *name)
{
	std::cout << "usage: " << name << " [xyph]" << std::endl;
	std::cout << "'-d' for difficulty. 1 - easy, 2 - Normal, 3 - Medium, 4 - Hard" << std::endl;
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
	std::regex regex_pattern("(-?|\\+?)[0-9]+");

	while ((ch = getopt(ac, av, "hx:y:vp:d:")) != -1)
	{
		switch (ch)
		{
			case 'h':
				usage(av[0]);
			case 'x':
				if (!regex_match(optarg, regex_pattern))
					put_error("Wrong window value");
				opts.width = atoi(optarg);
				break;
			case 'y':
				if (!regex_match(optarg, regex_pattern))
					put_error("Wrong window value");
				opts.height = atoi(optarg);
				break;
			case 'd':
				if (!regex_match(optarg, regex_pattern))
					put_error("Wrong difficulty value");
				opts.difficulty = atoi(optarg);
				break;
			case 'p':
				if (!regex_match(optarg, regex_pattern))
					put_error("Wrong players number");
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
	if (opts.width < 0 || opts.height < 0)
		put_error("Please type positives values for window format");
	if (opts.difficulty < 1 || opts.difficulty > 4)
		put_error("Wrong value for difficulty");
	if (opts.players < 1 || opts.players > 4)
		put_error("Wrong players number");
	return (opts);
}

int		main(int ac, char **av)
{
	t_opts		opts;

	if (ac < 2)
	{
		usage(av[0]);
		return (0);
	}
	opts = options(ac, av);

	Engine	engine(opts.width, opts.height, opts.players, opts.difficulty);
	return (0);
}
