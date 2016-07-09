/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 17:10:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/09 19:55:54 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		backspace(t_shell *shell)
{
	if (!shell->input || !shell->curs_pos)
		return (-1);
	delete_input(shell, shell->curs_pos, 1);
	replace_cursor(shell, 0, 1);
	tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	if ((!(shell->curs_pos) && shell->input)
		|| (shell->curs_pos && shell->curs_pos->next))
	{
		if (!shell->curs_pos)
			print_input(shell, shell->input, shell->p_len);
		else
		{
			replace_cursor(shell, 0, 1);
			print_input(shell, shell->curs_pos, shell->p_len);
		}
	}
	return (0);
}
