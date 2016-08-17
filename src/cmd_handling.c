/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 14:41:46 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/17 15:38:46 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtins_cmd(char **cmd, t_env *env_lst)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, env_lst);
	/* else if (ft_strcmp(cmd[0], "echo") == 0) */
		/* ft_echo(cmd, *env_lst, 1); */
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(cmd, *env_lst, 1);/*
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ft_setenv(++cmd, env_lst, 0);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ft_unsetenv(cmd, env_lst);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);*/
	else
		return (-1);
	return (0);
}
