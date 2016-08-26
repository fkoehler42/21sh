/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 14:41:46 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/27 00:37:47 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtins_cmd(char **cmd, t_env *env)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, env);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(cmd, env, 1);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ft_setenv(++cmd, &env, 0);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ft_unsetenv(cmd, &env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	else
		return (-1);
	return (0);
}

void	handle_cmd_btree(t_btree *cmd, t_env *env)
{
	if (cmd->type == SEM)
	{
		handle_cmd_btree(cmd->left, env);
		handle_cmd_btree(cmd->right, env);
	}
	else if (cmd->type == PIP)
	{
		//create_cmd_pipe
		handle_cmd_btree(cmd->left, env);
		handle_cmd_btree(cmd->right, env);
	}
	else if (cmd->array[0])
	{
		if (builtins_cmd(cmd->array, env) == -1)
			return ;
	}
}

void	handle_cmd(t_shell *shell)
{
	handle_cmd_btree(shell->cmd, shell->env_lst);
}
