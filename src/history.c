/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 18:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/11 20:17:50 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	store_hist(t_shell *shell)
{
	t_hist	*new;
	t_hist	*tmp;

	if (!(new = (t_hist *)malloc(sizeof(*new))))
		exit_error(9);
	new->next = NULL;
	new->prev = NULL;
	new->input = shell->input;
	new->input_len = shell->input_len;
	if ((tmp = shell->hist))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	shell->hist = new;
}

int		history_prev(t_shell *shell)
{
	if (!shell->hist)
		return (-1);
	if (!shell->hist->next)
	{
		store_hist(shell);
		shell->hist = shell->hist->prev;
	}
	if (shell->input)
	{
		move_line_start(shell);
		tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	}
	shell->input = shell->hist->input;
	shell->input_len = shell->hist->input_len;
	if (shell->input)
	{
		shell->curs_pos = shell->input;
		print_input(shell, shell->curs_pos, shell->p_len);
		move_line_end(shell);
	}
	if (shell->hist->prev)
		shell->hist = shell->hist->prev;
	return (0);
}

int		history_next(t_shell *shell)
{
	(void)shell;
	return (0);
}
