/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:55:56 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/05 18:52:18 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_termcaps(void)
{
	if (!(tgetstr("do", NULL)))
		return (-1);
	if (!(tgetstr("up", NULL)))
		return (-1);
	if (!(tgetstr("le", NULL)))
		return (-1);
	if (!(tgetstr("nd", NULL)))
		return (-1);
	if (!(tgetstr("cd", NULL)))
		return (-1);
	if (!(tgetstr("mr", NULL)))
		return (-1);
	if (!(tgetstr("me", NULL)))
		return (-1);
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
	shell->cmd = NULL;
	get_struct(shell);
}

void		init_term(t_shell *shell)
{
	int				ret;
	char			*term_name;
	struct winsize	w;

	if (!(term_name = getenv("TERM")))
		quit_error(1);
	if ((ret = tgetent(NULL, term_name)) <= 0)
		ret == 0 ? quit_error(2) : quit_error(3);
	if ((tcgetattr(STDIN_FILENO, &(shell->term_save))) == -1)
		quit_error(4);
	if ((tcgetattr(STDIN_FILENO, &(shell->termios))) == -1)
		quit_error(4);
	shell->termios.c_lflag &= ~(ICANON | ECHO);
	shell->termios.c_cc[VMIN] = 1;
	shell->termios.c_cc[VTIME] = 0;
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &(shell->termios))) == -1)
		quit_error(5);
	if ((ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) < 0)
		quit_error(10);
	shell->col = w.ws_col;
	if (check_termcaps() == -1)
		quit_error(8);
}

void		restore_term(t_shell *shell)
{
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &(shell->term_save))) == -1)
			quit_error(5);
}

t_shell		*get_struct(t_shell *struc)
{
	static t_shell	*shell = NULL;

	if (struc == 0)
		return (shell);
	else
		shell = struc;
	return (0);
}
