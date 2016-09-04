/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 18:47:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/04 22:49:59 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		fork_process(char **cmd, t_btree *link, t_env *env_lst)
{
	int		status;
	pid_t	pid;
	char	**env_array;

	(void)link;
	status = 0;
	env_array = NULL;
	if ((pid = fork()) < 0)
		return (exec_error(0, "fork"));
	if (pid == 0)
	{
		if (is_builtin(cmd[0]))
			builtins_cmd(cmd, env_lst);
		else
		{
			env_array = env_lst_to_array(env_lst);
			binary_cmd(cmd, env_array, env_lst);
			free(env_array);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}
