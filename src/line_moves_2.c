/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_moves_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 17:07:36 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/30 17:36:37 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_left_word(t_shell *shell)
{

	if (!shell->input || !shell->curs_pos)
		return (-1);
	while (shell->curs_pos
			&& shell->curs_pos->c != ' ' && shell->curs_pos->c != '\t')
	{
		shell->curs_pos = shell->curs_pos->prev;
		replace_cursor(shell, 0, 1);
	}
	while (shell->curs_pos
			&& (shell->curs_pos->c == ' ' || shell->curs_pos->c == '\t'))
	{
		shell->curs_pos = shell->curs_pos->prev;
		replace_cursor(shell, 0, 1);
	}
	if (shell->curs_pos)
	{
		shell->curs_pos = shell->curs_pos->prev;
		replace_cursor(shell, 0, 1);
	}
	return (0);
}

int		move_right_word(t_shell *shell)
{
	(void)shell;
	return (0);
}

int		move_line_up(t_shell *shell)
{
	(void)shell;
	return (0);
}

int		move_line_down(t_shell *shell)
{
	(void)shell;
	return (0);
}
