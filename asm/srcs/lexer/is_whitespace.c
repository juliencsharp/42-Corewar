/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:15:42 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

_Bool	is_whitespace(char *tok)
{
	if (tok[0] == ' ' || tok[0] == '\t')
		return (true);
	return (false);
}
