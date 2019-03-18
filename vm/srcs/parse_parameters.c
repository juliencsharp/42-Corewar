/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:40:40 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/18 16:21:43 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		parse_number(int *pos, const char *av[])
{
	char	*str;
	int		i;
	int		res;

	if (av[*pos] == NULL || av[*pos][0] == '\0')
		corewar_die(MSG_COMMAND_LINE_ERROR);
	str = (char*)av[*pos];
	res = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			corewar_die(MSG_COMMAND_LINE_ERROR);
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	(*pos)++;
	return (res);
}

static void		parse_champion(t_corewar *corewar, int *pos, const char *av[])
{
	t_player	*player;

	player = &corewar->players[corewar->players_count];
	if (ft_strequ("-n", av[*pos]))
	{
		(*pos)++;
		player->id = parse_number(pos, av);
	}
	if (av[*pos] == NULL)
		corewar_die(MSG_COMMAND_LINE_ERROR);
	if (corewar->players_count >= MAX_PLAYERS)
	{
		ft_fprintf(2, "Up to %d max players allowed\n", MAX_PLAYERS);
		exit(EXIT_FAILURE);
	}
	player->file = av[*pos];
	(*pos)++;
	corewar->players_count++;
}

static void		parse_dump(t_corewar *corewar, int *pos, const char *av[])
{
	if (ft_strequ("-dump", av[*pos]))
	{
		(*pos)++;
		corewar->dump_nbr_cycle = parse_number(pos, av);
	}
}

void			parse_parameters(t_corewar *corewar, int ac, const char *av[])
{
	int	i;

	i = 1;
	parse_dump(corewar, &i, av);
	if (ac == 1)
	{
		ft_printf("\033[1;31m");
		ft_printf("ERROR: there is'nt a argument.\n");
		ft_printf("\033[0m");
		exit(EXIT_FAILURE);
	}
	while (i < ac)
	{
		parse_champion(corewar, &i, av);
	}
}
