/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:40:40 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/20 14:59:54 by agoulas          ###   ########.fr       */
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
	player->id = -1;
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

static void		players_init_color(t_corewar *corewar)
{
	int cpt;

	cpt = 0;
	while (cpt < corewar->players_count && cpt < MAX_PLAYERS)
	{
		corewar->players[cpt].color = cpt % MAX_PLAYERS;
		cpt++;
	}
}

static int		id_has_duplicate(t_corewar *corewar, int id)
{
	int cpt;
	int nb;

	nb = 0;
	cpt = corewar->players_count - 1;
	while (cpt >= 0)
	{
		if (corewar->players[cpt].id == id)
			nb++;
		cpt--;
	}
	return (nb);
}

static void		players_init_id(t_corewar *corewar)
{
	int cpt;
	int i;

	cpt = 0;
	while (cpt < corewar->players_count)
	{
		i = 0;
		while (corewar->players[cpt].id == -1 && i < corewar->players_count)
		{
			if (corewar->players[cpt].id == -1 && id_has_duplicate(corewar, i) == 0)
				corewar->players[cpt].id = i;
					i++;
		}
		//ft_printf("player %d id : %d\n",cpt, corewar->players[cpt].id );
		if (id_has_duplicate(corewar, corewar->players[cpt].id) > 1)
			corewar_die("Error player : duplicate id");
		cpt++;
	}
}

void			parse_parameters(t_corewar *corewar, int ac, const char *av[])
{
	int	i;

	i = 1;
	parse_dump(corewar, &i, av);
	if (ac == 1)
	{
		corewar_die("ERROR: no argument");
	}
	while (i < ac)
	{
		parse_champion(corewar, &i, av);
	}
	players_init_color(corewar);
	players_init_id(corewar);

}
