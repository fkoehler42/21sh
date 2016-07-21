/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 13:19:51 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/21 20:11:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	parse_near_pipe(t_input *cmd, int reverse)
{
	if (reverse)
	{
		if (!(cmd = cmd->prev))
			return (-1);
		while (cmd && cmd->c != ';' && cmd->c != '|' && cmd->c != '`')
		{
			if (!ft_isspace(cmd->c)	&& cmd->c != '>' && cmd->c != '<')
				return (0);
			cmd = cmd->prev;
		}
	}
	else
	{
		if (!(cmd = cmd->next))
			return (-1);
		while (cmd && cmd->c != ';' && cmd->c != '|' && cmd->c != '`')
		{
			if (!ft_isspace(cmd->c)	&& cmd->c != '>' && cmd->c != '<')
				return (0);
			cmd = cmd->next;
		}
	}
	return (-1);
}

int				parse_pipe_cmd(t_input *cmd, int reverse)
{
	t_input	*tmp;

	if (!(tmp = cmd))
		return (-1);
	while (tmp)
	{
		if (tmp->c == '|' && (parse_near_pipe(tmp, reverse) == -1))
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
