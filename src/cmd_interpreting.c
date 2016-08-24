/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_interpreting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/24 20:35:08 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		del_escape_char(t_input *input, char c)
{
	(void)input;
	(void)c;
}

static void	check_param_format(t_token *token, char *param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if (ft_isquote(param[i]))
		{
			if (i > 0)
			{
				create_token();
			}
		}
	}
}

char		**interpret_cmd(t_token *cmd_token, char **cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i])
	{
		check_param_format(cmd_token, cmd_tab[i]);
	}
}
