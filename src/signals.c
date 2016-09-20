/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 15:51:02 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/20 18:19:03 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	sig_int_handler(t_shell *shell)
{
	if (shell->input)
	{
		move_line_end(shell);
		free_tmp_inputs(shell, 1);
	}
	tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
	shell->p_len = put_prompt(get_prompt(shell->env_lst), shell->fd[3]);
}

static void	sig_winch_handler(t_shell *shell)
{
	struct winsize	w;

	if ((ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) < 0)
		quit_error(10);
	shell->col = w.ws_col;
}

void		sig_handler(int signum)
{
	char	suspend;
	t_shell *shell;

	suspend = 26;
	shell = get_struct(0);
	if (signum == SIGINT)
		sig_int_handler(shell);
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
	else if (signum == SIGWINCH)
		sig_winch_handler(shell);
}

void		sig_handler1(int signum)
{
	t_shell *shell;

	(void)signum;
	shell = get_struct(0);
	tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
}

void		set_sig_handler(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGTSTP, &sig_handler);
	signal(SIGCONT, &sig_handler);
	signal(SIGWINCH, &sig_handler);
}
