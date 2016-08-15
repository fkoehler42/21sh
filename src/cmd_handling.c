/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 14:41:46 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/15 18:20:21 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd(char *str_cmd, int parent)
{
	int		i;
	char	**cmd;

	i = 0;
	if (!(cmd = strsplit_args(str_cmd)) && parent == PIP)
		return (cmd_error(0));
	while (cmd[i])
	{
		if ((is_str_quoted(cmd[i]) != 1) && (ft_strchr(cmd[i], '$') != NULL))
			cmd[i] = str_replace_var(cmd[i]);
		ft_putendl(cmd[i++]);
	}
	return (0);
}
