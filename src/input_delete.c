/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 17:10:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/10 01:54:40 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		backspace(t_shell *shell)
{
	if (!shell->input || !shell->curs_pos)
		return (-1);
	replace_cursor(shell, 0, 1);
	delete_input(shell, shell->curs_pos, 1);
	tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	if (!(shell->curs_pos) && shell->input)
	{
		shell->curs_pos = shell->input;
		print_input(shell, shell->curs_pos, shell->p_len);
		replace_cursor(shell, 0, 1);
		shell->curs_pos = NULL;
	}
	else if (shell->curs_pos && shell->curs_pos->next)
	{
		replace_cursor(shell, 0, 1);
		print_input(shell, shell->curs_pos, shell->p_len);
	}
	return (0);
}
