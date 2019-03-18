/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:50:54 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/18 15:30:43 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	setup_player_at_pos(t_corewar *corewar, t_player *player, size_t pos)
{
	t_process	*entry_process;

	ft_memcpy(&corewar->memory[pos], &player->program, CHAMP_MAX_SIZE);
	corewar->id_memory[pos] = player->id;
	entry_process = process_new();
	entry_process->pc = pos;
	entry_process->player = player;
	corewar->id_memory[pos] = player->id;
	ft_lstadd(&corewar->processes, ft_lstnew(entry_process, sizeof(t_process)));
}

/*
**	Setups the initial memory and processes of players in memory.
*/

void	setup_players(t_corewar *corewar)
{
	int			i;
	size_t		offset;
	size_t		pos;
	t_player	*player;

	offset = MEM_SIZE / corewar->players_count;
	pos = 0;
	i = 0;
	while (i < corewar->players_count)
	{

		player = &corewar->players[i];
		setup_player_at_pos(corewar, player, pos);
		pos += offset;
		i++;
	}
}
