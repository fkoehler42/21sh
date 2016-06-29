/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 17:27:02 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/29 21:35:12 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_left(t_shell *shell)
{
	if (!(shell->input) || !(shell->curs_pos))
		return (-1);
	replace_cursor(shell, 0, 1);
	shell->curs_pos = shell->curs_pos->prev;
	return (0);
}

int		move_right(t_shell *shell)
{
	if (!(shell->input) || (shell->curs_pos && !(shell->curs_pos->next)))
		return (-1);
	if (!(shell->curs_pos))
		shell->curs_pos = shell->input;
	else
		shell->curs_pos = shell->curs_pos->next;
	replace_cursor(shell, 0, 0);
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
