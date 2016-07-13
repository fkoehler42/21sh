/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:13:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/13 22:10:24 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t	get_cursor_x_pos(t_input *input, t_input *pos, size_t p_len)
{
	size_t	i;
	t_input	*tmp;

	i = 1;
	if (!(tmp = input) || !(pos))
		return (p_len + 1);
	while (tmp && tmp != pos)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + p_len);
}

void	replace_cursor(t_shell *shell, int print, int back)
{
	size_t	x_pos;
	size_t	col;

	col = shell->col;
	x_pos = get_cursor_x_pos(shell->input, shell->curs_pos, shell->p_len);
	if ((!print && back && ((x_pos % col) == 0)) || (print == 42))
	{
		tputs(tgetstr("up", NULL), shell->fd, &putchar);
		while (col--)
			tputs(tgetstr("nd", NULL), shell->fd, &putchar);
	}
	else if (back)
		tputs(tgetstr("le", NULL), shell->fd, &putchar);
	else if ((x_pos % shell->col) == 0)
		tputs(tgetstr("do", NULL), shell->fd, &putchar);
	else
		tputs(tgetstr("nd", NULL), shell->fd, &putchar);
}
