/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_interpreting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/25 12:00:17 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		del_escape_char(t_input *input, char c)
{
	(void)input;
	(void)c;
}

char		*interpret_cmd_arg(char *cmd_arg)
{/*
	int	i;
	int	chr;

	i = 0;
	if ((chr = (ft_strchr_index(cmd_arg, '$') != -1)))
	while (cmd_arg[i] && i < chr)
	{
		if (cmd_arg[i] == '"' || cmd_arg[i] == '`' || i == (chr - 1))

	}*/
	return (cmd_arg);
}
