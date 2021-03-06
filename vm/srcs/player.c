/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:22:34 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 14:03:30 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	read_error(const char *filename)
{
	ft_fprintf(2, "%s is not a corewar executable\n", filename);
	exit(EXIT_FAILURE);
}

static void	read_n_bytes(int fd, void *ptr, ssize_t size, const char *filename)
{
	ssize_t		read_size;

	read_size = (ssize_t)read(fd, ptr, size);
	if (read_size < 0)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (read_size != size)
	{
		read_error(filename);
	}
}

static void	player_cpy(t_player *player, t_header header, int fd)
{
	read_n_bytes(fd, &player->program, header.prog_size, player->file);
	ft_memcpy(&player->prog_name, &header.prog_name, sizeof(player->prog_name));
	ft_memcpy(&player->comment, &header.comment, sizeof(header.comment));
	player->prog_size = header.prog_size;
	if (player->prog_name[0] == '\0')
		ft_memcpy(player->prog_name, "ANONYMOUS", 8);
	if (player->comment[0] == '\0')
		ft_memcpy(player->comment, "NO COMMENTS", 8);
}

void		player_load(t_player *player)
{
	int			fd;
	t_header	header;

	fd = open(player->file, O_RDONLY);
	if (fd <= 0)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	read_n_bytes(fd, &header, sizeof(header), player->file);
	header.magic = convert_endian32(header.magic);
	header.prog_size = convert_endian32(header.prog_size);
	if (header.magic != COREWAR_EXEC_MAGIC)
		read_error(player->file);
	if (header.prog_size > CHAMP_MAX_SIZE)
	{
		ft_fprintf(2, "%s is too big\n", player->file);
		exit(EXIT_FAILURE);
	}
	player_cpy(player, header, fd);
	close(fd);
}
