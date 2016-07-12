/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 18:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/13 00:04:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	store_input_buf(t_input *input, size_t len, char **buffer)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = input;
	if (*buffer)
		free(*buffer);
	if (!(*buffer = ft_strnew(len)))
		exit_error(9);
	while (tmp)
	{
		(*buffer)[i++] = tmp->c;
		tmp = tmp->next;
	}
}

static void	store_hist_input(char c, t_hist *hist)
{
	t_input *new;
	t_input *tmp;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		exit_error(9);
	new->c = c;
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
}

t_hist		*store_hist(t_shell *shell)
{
	t_hist	*new;
	t_hist	*tmp1;
	t_input	*tmp2;

	if (!(new = (t_hist *)malloc(sizeof(*new))))
		exit_error(9);
	new->prev = NULL;
	new->next = NULL;
	new->input = NULL;
	tmp2 = shell->input;
	while (tmp2)
	{
		store_hist_input(tmp2->c, new);
		tmp2 = tmp2->next;
	}
	if ((tmp1 = shell->hist))
	{
		while (tmp1->next)
			tmp1 = tmp1->next;
		tmp1->next = new;
		new->prev = tmp1;
	}
	return (new);
}

int			history_prev(t_shell *shell)
{
	t_input	*tmp;

	if (!shell->hist)
		return (-1);
	if (!shell->hist->next && shell->input)
		store_input_buf(shell->input, shell->input_len, &(shell->input_buf));
	if (shell->input)
	{
		move_line_start(shell);
		tputs(tgetstr("cd", NULL), shell->fd, &putchar);
		free_input_list(&(shell->input), &(shell->input_len));
	}
	tmp = shell->hist->input;
	while (tmp)
	{
		store_input(shell, tmp->c);
		print_input(shell, shell->curs_pos, shell->p_len);
		tmp = tmp->next;
	}
	if (shell->hist->prev)
		shell->hist = shell->hist->prev;
	return (0);
}

int			history_next(t_shell *shell)
{
	int		i;
	t_input	*tmp;

	i = 0;
	if (!shell->hist)
		return (-1);
	move_line_start(shell);
	tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	free_input_list(&(shell->input), &(shell->input_len));
	if (!(shell->hist->next) && shell->input_buf)
	{
		while (shell->input_buf[i])
		{
			store_input(shell, shell->input_buf[i++]);
			print_input(shell, shell->curs_pos, shell->p_len);
		}
		free(shell->input_buf);
		shell->input_buf = NULL;
	}
	if (shell->hist->next && (shell->hist = shell->hist->next)
		&& (tmp = shell->hist->input))
	{
		while (tmp)
		{
			store_input(shell, tmp->c);
			print_input(shell, shell->curs_pos, shell->p_len);
			tmp = tmp->next;
		}
	}
	return (0);
}
