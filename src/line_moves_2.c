/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_moves_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 17:07:36 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/06 13:38:41 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_left_word(t_shell *shell)
{

	if (!shell->input || !shell->curs_pos)
		return (-1);
	while (shell->curs_pos && shell->curs_pos->c == ' ')
	{
		replace_cursor(shell, 0, 1);
		shell->curs_pos = shell->curs_pos->prev;
	}
	while (shell->curs_pos && shell->curs_pos->c != ' ')
	{
		replace_cursor(shell, 0, 1);
		shell->curs_pos = shell->curs_pos->prev;
	}
	return (0);
}

int		move_right_word(t_shell *shell)
{
	if (!shell->input || (shell->curs_pos && !shell->curs_pos->next))
		return (-1);
	if (!shell->curs_pos)
	{
		replace_cursor(shell, 0, 0);
		shell->curs_pos = shell->input;
	}
	while (shell->curs_pos->c == ' ' && shell->curs_pos->next->c  ' ')
	{

	}
	while (shell->curs_pos->next &&	shell->curs_pos->c != ' ')
	{
		replace_cursor(shell, 0, 0);
		shell->curs_pos = shell->curs_pos->next;
	}
	while (shell->curs_pos->next && shell->curs_pos->next->c == ' ')
	{
		replace_cursor(shell, 0, 0);
		shell->curs_pos = shell->curs_pos->next;
	}
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
