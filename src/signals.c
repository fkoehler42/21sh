/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 15:51:02 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/17 19:24:40 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sig_handler(int signum)
{
	char	suspend;
	t_shell *shell;

	suspend = 26;
	shell = get_struct(0);
	if (signum == SIGINT)
	{
		if (shell->input)
		{
			move_line_end(shell);
			free_tmp_inputs(shell);
		}
		tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
		shell->p_len = put_prompt(get_prompt(shell->env_lst), shell->fd[3]);
	}
	else if (signum == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		restore_term(shell);
		ioctl(0, TIOCSTI, &suspend);
	}
	else if (signum == SIGCONT)
	{
		reload_term(shell);
		signal(SIGTSTP, &sig_handler);
		shell->p_len = put_prompt(get_prompt(shell->env_lst), shell->fd[3]);
		if (shell->input)
			print_input(shell, shell->input, shell->p_len);
	}
}

void	set_sig_handler(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGTSTP, &sig_handler);
	signal(SIGCONT, &sig_handler);
	signal(SIGWINCH, &sig_handler);
}
