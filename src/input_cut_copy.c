/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cut_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 20:29:43 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/09 18:00:14 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		copy_eol(t_shell *shell)
{
	t_input *tmp;

	if (!shell->input || (shell->curs_pos && !shell->curs_pos->next))
		return (-1);
	if (shell->buffer)
		free_input_list(&(shell->buffer), &(shell->buf_len));
	if (!(tmp = shell->curs_pos))
		copy_all(shell);
	tmp = tmp->next;
	while (tmp)
	{
		store_buffer(&(shell->buffer), tmp->c);
		tmp = tmp->next;
		shell->buf_len++;
	}
	return (0);
}

int		copy_all(t_shell *shell)
{
	t_input *tmp;

	if (shell->buffer)
		free_input_list(&(shell->buffer), &(shell->buf_len));
	if (!(tmp = shell->input))
		return (-1);
	while (tmp)
	{
		store_buffer(&(shell->buffer), tmp->c);
		tmp = tmp->next;
		shell->buf_len++;
	}
	return (0);
}
