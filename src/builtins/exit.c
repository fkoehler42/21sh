/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 20:39:30 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 09:32:39 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_exit(char **cmd)
{
	int		i;
	int		ret;
	char	*arg;

	i = 0;
	ret = 0;
	if (!cmd[1])
		exit(0);
	if (cmd[2])
		return (exit_error(0, ""));
	arg = strdup_remove_quotes(cmd[1]);
	if (arg[0] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (exit_error(1, arg));
		i++;
	}
	if (i > 15)
		return (exit_error(2, arg));
	ret = ft_atoi(arg);
	free(arg);
	exit(ret);
}
