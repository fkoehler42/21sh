/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 17:27:02 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/27 18:40:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_left(t_shell *shell)
{
	if (!(shell->curs_pos))
		return (-1);
	if ((tputs(tgetstr("le", NULL), shell->fd, &putchar)) == -1)
		exit_error(8);
	shell->curs_pos = shell->curs_pos->prev;
	return (0);
}

int		move_right(t_shell *shell)
{
	(void)shell;
	return (0);
}

int		line_start(t_shell *shell)
{
	(void)shell;
	return (0);
}

int		line_end(t_shell *shell)
{
	(void)shell;
	return (0);
}
