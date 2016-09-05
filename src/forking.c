/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 18:47:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/05 21:00:10 by fkoehler         ###   ########.fr       */
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

int		pipe_fork(t_shell *shell, t_btree *link, int *fd)
{
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	status = 0;
	if ((pid1 = fork()) < 0)
		return (exec_error(0, "fork"));
	if (pid1 == 0)
	{
		if (dup2(fd2, fd1) == -1)
			return (exec_error(6, "dup2"));
		close(fd2);
		handle_cmd(shell, link, 1);
	}
	else if (pid1 > 0)
		waitpid(pid, &status, 0);
	return (0);
}
