/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 20:57:31 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/07 14:18:18 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	store_buffer(t_input **buf, char c)
{
	t_input	*new;
	t_input	*tmp;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		exit_error(9);
	new->c = c;
	new->next = NULL;
	if (!(*buf))
	{
		new->prev = NULL;
		*buf = new;
	}
	else
	{
		tmp = *buf;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

int		paste_buffer(t_shell *shell)
{
	t_input *tmp1;
	t_input *tmp2;

	if (!shell->buffer)
		return (-1);
	if (!shell->curs_pos && !shell->input)
	{
		shell->input = shell->buffer;
		shell->input_len = shell->buf_len;
	}
	if (!shell->curs_pos)
	{
		tmp1 = shell->input;
		shell->input = shell->buffer;
		tmp2 = shell->input;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = shell->buffer;
	}
	return (0);
}
