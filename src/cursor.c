/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:13:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/28 18:10:53 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t	get_cursor_x_pos(t_input *input, t_input *pos, size_t p_len)
{
	size_t	i;
	t_input	*tmp;

	i = 1;
	if (!(tmp = input))
		return (0);
	while (tmp && tmp != pos)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + p_len);
}

void	replace_cursor(t_shell *shell)
{
	if ((tputs(tgetstr("rc", NULL), shell->fd, &putchar)) == -1)
		exit_error(8);
	if ((get_cursor_x_pos(shell->input, shell->curs_pos, shell->p_len)
	% shell->col) == 0)
	{
		if ((tputs(tgetstr("do", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
	}
	else
	{
		if ((tputs(tgetstr("nd", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
	}
}
