/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:56:58 by juazouz           #+#    #+#             */
/*   Updated: 2018/12/18 12:10:14 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		out_init(t_output *output)
{
	output->fd = -1;
	output->size = 0;
	output->buf = NULL;
}
