/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/15 16:20:44 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	epur_cmd(t_shell *shell)
{
	t_input	*tmp;

	if (!(tmp = shell->input))
		return (-1);
	while (tmp && (tmp->c == ' ' || tmp->c == ';'))
	{
		delete_input(shell, tmp, 0);
		tmp = tmp->next;
	}
	if (!tmp)
		return (-1);
	while (tmp->next)
		tmp = tmp->next;
	while (tmp && (tmp->c == ' ' || tmp->c == ';'))
	{
		delete_input(shell, tmp, 0);
		tmp = tmp->prev;
	}
	if (!tmp)
		return (-1);
	return (0);
}

static int	multi_lines_cmd(t_shell *shell)
{
	static t_input	*save = NULL;
	char			c;

	c = 0;
	if ((c = not_ended_input(shell, shell->input, c)) != 0)
	{
		lst_cpy(shell->input, save);
		store_buffer(&(save), '\n');
		tputs(tgetstr("do", NULL), shell->fd, &putchar);
		read_multi_lines_input(shell, get_special_prompt(c));
		lst_cpy(shell->input, save);
		while ((c = not_ended_input(shell, shell->save, c)) != 0)
		{
			store_buffer(&(save), '\n');
			lst_cpy(shell->input, save);
			free_tmp_inputs(shell);
			tputs(tgetstr("do", NULL), shell->fd, &putchar);
			read_multi_lines_input(shell, get_special_prompt(c));
		}
	}
	if (save)
	{
		lst_cpy(shell->input, save);
		free_tmp_inputs(shell);
		shell->input = save;
		shell->input_len = lst_len(shell->input);
		save = NULL;
	}
	return (0);
}

int			handle_cmd(t_shell *shell)
{
	move_line_end(shell);
	if (epur_cmd(shell) == -1)
		return (-1);
	multi_lines_cmd(shell);
	shell->hist = store_hist(shell);
	clear_input(shell); //to remove
	free_tmp_inputs(shell);
	return (0);
}
