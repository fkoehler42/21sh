/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 18:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/11 13:39:12 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	store_hist(t_shell *shell)
{
	t_hist	*new;

	if (!(new = (t_hist *)malloc(sizeof(*new))))
		exit_error(9);
	new->next = NULL;
	new->prev = shell->hist;
	new->input = shell->input;
	new->input_len = shell->input_len;
	if (!shell->hist)
		shell->hist = new;
	else
		shell->hist->next = new;
}

int		history_prev(t_shell *shell)
{
	int	diff;

	if (!shell->hist)
		return (-1);
	diff = input_lst_cmp(shell->hist->input, shell->input,
	shell->hist->input_len, shell->input_len);
	if (!shell->hist->next && diff != 0)
		store_hist(shell);
	if (shell->input && diff != 0)
	{
		move_line_start(shell);
		tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	}
	shell->input = shell->hist->input;
	shell->input_len = shell->hist->input_len;
	if (shell->input && diff != 0)
		print_input(shell, shell->curs_pos, shell->p_len);
	if (shell->hist->prev)
		shell->hist = shell->hist->prev;
	return (0);
}

int		history_next(t_shell *shell)
{
	(void)shell;
	return (0);
}
