/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 14:41:46 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/30 10:56:34 by fkoehler         ###   ########.fr       */
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

int		handle_cmd(t_shell *shell, t_btree *tree)
{
	if (parse_cmd(tree) == -1)
		return (-1);
	(void)shell;
	return (0);
}

int		handle_btree(t_shell *shell, t_btree *tree)
{
	if (tree->type == SEM)
	{
		handle_btree(shell, tree->left);
		handle_btree(shell, tree->right);
	}
	else if (tree->type == PIP)
	{
		if (!tree->left || !tree->right)
			return (cmd_error(0, "|"));
		if (tree->left->type == PIP || tree->right->type == PIP)
			handle_btree(shell, tree->left);
		else
			handle_cmd(shell, tree);
	}
	else if (tree->str && tree->str[0])
		handle_cmd(shell, tree);
	return (0);
}
