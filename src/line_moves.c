/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 17:27:02 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/25 20:15:54 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_left(t_shell *shell)
{
	if (!(shell->line_pos) || !(shell->line_pos->prev))
		return (-1);
	if ((tputs(tgetstr("le", NULL), shell->fd, &putchar)) == -1)
		exit_error(8);
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
