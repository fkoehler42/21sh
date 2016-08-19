/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:56:41 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 08:52:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_unsetenv(char **cmd, t_env **env_lst)
{
	int		i;
	char	*dup_var;

	i = 1;
	if (!cmd[1])
	{
		env_var_error(0, cmd[0], "");
		return (-1);
	}
	while (cmd[i])
	{
		dup_var = strdup_remove_quotes(cmd[i]);
		if (check_env_var(dup_var, cmd[0]) == -1)
		{
			free(dup_var);
			return (-1);
		}
		del_env_var(env_lst, dup_var);
		i++;
	}
	return (0);
}
