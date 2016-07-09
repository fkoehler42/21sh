/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 20:57:31 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/09 12:55:24 by fkoehler         ###   ########.fr       */
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
	t_input *tmp;

	if (!shell->buffer)
		return (-1);
	if (!shell->input)
		shell->input = shell->buffer;
	else if (!shell->curs_pos)
	{
		tmp = shell->buffer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = shell->input;
		shell->input->prev = tmp;
		shell->input = shell->buffer;
	}
	else
	{
		shell->buffer->prev = shell->curs_pos;
		tmp = shell->buffer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = shell->curs_pos->next;
		shell->curs_pos->next = shell->buffer;
		shell->curs_pos->next->prev = tmp;
	}
	shell->input_len += shell->buf_len;
	return (0);
}
