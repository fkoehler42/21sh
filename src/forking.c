/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 18:47:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/08 17:53:24 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

pid_t	simple_fork(t_btree *link)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return ((pid_t)exec_error(0, "fork"));
	if (pid == 0)
	{
		(void)link;
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (pid);
}

pid_t	exec_fork(char **cmd, char **env_array, t_env *env_lst)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return ((pid_t)exec_error(0, "fork"));
	if (pid == 0)
	{
		if (is_builtin(cmd[0]))
			builtins_cmd(cmd, env_lst);
		else
			binary_cmd(cmd, env_array, env_lst);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (pid);
}

pid_t	pipe_fork_father(t_shell *shell, t_btree *link)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return ((pid_t)exec_error(0, "fork"));
	if (pid > 0)
			waitpid(pid, NULL, 0);
	else if (pid == 0)
		pipe_fork_child(shell, link);
	return (pid);
}

pid_t	pipe_fork_child(t_shell *shell, t_btree *link)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	if ((pid = fork()) < 0)
		return ((pid_t)exec_error(0, "fork"));
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return ((pid_t)exec_error(6, "dup2"));
		close(fd[0]);
		if (link->left->type == PIP)
			pipe_fork_child(shell, link->left);
		if (link->left->type == CMD)
			handle_cmd(shell, link->left, 1);
	}
	else if (pid > 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return ((pid_t)exec_error(6, "dup2"));
		close(fd[1]);
		if (link->right->type == CMD)
			handle_cmd(shell, link->right, 1);
	}
	return (pid);
}
