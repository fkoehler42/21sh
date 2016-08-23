/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 20:39:30 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/21 14:13:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_exit(char **cmd)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!cmd[1])
		exit(0);
	if (cmd[2])
		return (exit_error(0, ""));
	if (cmd[1][i] == '-')
		i++;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
			return (exit_error(1, cmd[1]));
		i++;
	}
	if (i > 15)
		return (exit_error(2, cmd[1]));
	ret = ft_atoi(cmd[1]);
	exit(ret);
}