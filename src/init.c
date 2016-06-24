/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:55:56 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 14:01:24 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	init_shell(t_shell *shell)
{
	if ((shell->fd = open("/dev/tty", O_RDWR)) == -1)
		exit_error(0);
	shell->pos_x = 0;
	shell->pos_y = 0;
	shell->col = 0;
	shell->env_lst = NULL;
	shell->input = NULL;
	shell->tree = NULL;
}

void	init_term(t_shell *shell)
{
	int		ret;
	char	*term_name;

	if (!(term_name = getenv("TERM")))
		exit_error(1);
	if ((ret = tgetent(NULL, term_name)) <= 0)
		ret == 0 ? exit_error(2) : exit_error(3);
	if ((tcgetattr(0, &(shell->term_save))) == -1)
		exit_error(4);
	if ((tcgetattr(0, &(shell->termios))) == -1)
		exit_error(4);
	shell->termios.c_lflag &= ~(ICANON);
	shell->termios.c_lflag &= ~(ECHO);
	shell->termios.c_cc[VMIN] = 1;
	shell->termios.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSADRAIN, &(shell->termios))) == -1)
		exit_error(5);
}
