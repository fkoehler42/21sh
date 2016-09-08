/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:43:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/08 15:14:47 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_shell		*get_struct(t_shell *struc)
{
	static t_shell	*shell = NULL;

	if (struc == 0)
		return (shell);
	else
		shell = struc;
	return (0);
}

void		init_shell(t_shell *shell)
{
	shell->fd[0] = 0;
	shell->fd[1] = 1;
	shell->fd[2] = 2;
	if ((shell->fd[3] = open("/dev/tty", O_RDWR)) == -1)
		quit_error(0);
	shell->col = 0;
	shell->input_len = 0;
	shell->p_len = 0;
	shell->env_lst = NULL;
	shell->hist = NULL;
	shell->hist_end = 1;
	shell->input = NULL;
	shell->buffer = NULL;
	shell->input_buf = NULL;
	shell->curs_pos = NULL;
	shell->tree = NULL;
	get_struct(shell);
}

int		main(int ac, char **av, char **environ)
{
	t_shell		shell;

	(void)ac;
	(void)av;
	init_shell(&shell);
	init_term(&shell);
	store_environ(&shell, environ);
	read_input(&shell);
	return (0);
}
