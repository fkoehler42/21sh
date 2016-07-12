/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 18:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/12 15:34:05 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	store_hist_input(t_input *input, t_hist *hist)
{
	t_input *new;
	t_input *tmp;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		exit_error(9);
	new->c = input->c;
	new->prev = NULL;
	new->next = NULL;
	if (!(tmp = hist->input))
		hist->input = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	hist->input_len++;
}

t_hist		*store_hist(t_shell *shell, int prev)
{
	t_hist	*new;
	t_hist	*tmp1;
	t_input	*tmp2;

	if (!(new = (t_hist *)malloc(sizeof(*new))))
		exit_error(9);
	new->prev = NULL;
	new->next = NULL;
	new->input = NULL;
	new->input_len = 0;
	tmp2 = shell->input;
	while (tmp2)
	{
		store_hist_input(tmp2, new);
		tmp2 = tmp2->next;
	}
	if ((tmp1 = shell->hist))
	{
		while (tmp1->next)
			tmp1 = tmp1->next;
		tmp1->next = new;
		new->prev = tmp1;
	}
	return prev ? new->prev : new;
}

int			history_prev(t_shell *shell)
{
	t_input	*tmp;

	if (!shell->hist)
		return (-1);
	if (!shell->hist->next && shell->input)
		shell->hist = store_hist(shell, 1);
	if (shell->input)
	{
		move_line_start(shell);
		tputs(tgetstr("cd", NULL), shell->fd, &putchar);
		free_input_list(&(shell->input), &(shell->input_len));
		shell->curs_pos = NULL;
	}
	if ((tmp = shell->hist->input))
	{
		while (tmp)
		{
			store_input(shell, tmp->c);
			print_input(shell, shell->curs_pos, shell->p_len);
			tmp = tmp->next;
		}
	}
	if (shell->hist->prev)
		shell->hist = shell->hist->prev;
	return (0);
}

int			history_next(t_shell *shell)
{
	(void)shell;
	return (0);
}
