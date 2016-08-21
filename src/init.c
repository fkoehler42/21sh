/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:55:56 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/21 17:34:43 by fkoehler         ###   ########.fr       */
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
	if ((shell->fd = open("/dev/tty", O_RDWR)) == -1)
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
	if ((tcgetattr(0, &(shell->term_save))) == -1)
		quit_error(4);
	if ((tcgetattr(0, &(shell->termios))) == -1)
		quit_error(4);
	shell->termios.c_lflag &= ~(ICANON | ECHO);
	shell->termios.c_cc[VMIN] = 1;
	shell->termios.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSADRAIN, &(shell->termios))) == -1)
		quit_error(5);
	if ((ioctl(0, TIOCGWINSZ, &w)) < 0)
		quit_error(10);
	shell->col = w.ws_col;
	if (check_termcaps() == -1)
		quit_error(8);
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
