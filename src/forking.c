/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 18:47:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/07 03:18:38 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		exec_fork(char **cmd, t_btree *link, char **env_array, t_env *env_lst)
{
	int		status;
	pid_t	pid;

	(void)link;
	status = 0;
	if ((pid = fork()) < 0)
		return (exec_error(0, "fork"));
	if (pid == 0)
	{
		if (is_builtin(cmd[0]))
			builtins_cmd(cmd, env_lst);
		else
			binary_cmd(cmd, env_array, env_lst);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}

pid_t	pipe_fork_father(t_shell *shell, t_btree *link, int *fd)
{
	pid_t	pid;
	pid_t	child_pid;

	if ((pid = fork()) < 0)
		return (exec_error(0, "fork"));
	if (pid > 0)
	{
		child_pid = pipe_fork_child(shell, link->left, fd);
		waitpid(child_pid, NULL, 0);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		close(fd[0]);
	}
	else if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (exec_error(6, "dup2"));
		close(fd[1]);
		handle_cmd(shell, link->right, 1);
	}
	return (pid);
}

pid_t	pipe_fork_child(t_shell *shell, t_btree *link, int *fd)
{
	int		child_fd[2];
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (exec_error(0, "fork"));
	if (pid > 0)
	{
		/*
		if (link->left && (link->left->type == PIP) && (link = link->left))
		{
			if (pipe(child_fd) == -1)
				return (exec_error(5, ""));
			if (dup2(child_fd[0], fd[0]))
				return (exec_error(6, "dup2"));
			close(child_fd[1]);
			waitpid(pipe_fork_child(shell, link->left, child_fd), NULL, 0);
		}*/
		if (link->left && (link->left->type == PIP))
		{
			pipe(child_fd);
			pipe_fork_father(shell, link->left, child_fd);
		}
	}
	else if (pid == 0)
	{
		/* if (link->type == PIP) */
			/* link = link->right; */
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (exec_error(6, "dup2"));
		close(fd[0]);
		if (link->type == CMD)
			handle_cmd(shell, link, 1);
	}
	return (pid);
}
