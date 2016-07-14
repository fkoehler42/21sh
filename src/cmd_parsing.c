/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/14 19:52:01 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	is_bracket_closed(t_input *tmp, char c)
{
	char	d;

	d = (c == '(') ? c + 1 : c + 2;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->c == '\'' || tmp->c == '"' || tmp->c == '`')
		{
			if ((d = is_quote_closed(tmp, tmp->c)) != 0)
				return (d);
			d = tmp->c;
			tmp = tmp->next;
			while (tmp && tmp->c != d)
				tmp = tmp->next;
			d = (c == '(') ? c + 1 : c + 2;
		}
		else if (tmp->c == c)
			return (0);
		tmp = tmp->next;
	}
	return (d);
}

static char	is_quote_closed(t_input *tmp, char c)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->c == c)
			return (0);
		tmp = tmp->next;
	}
	return (c);
}

static char	ended_input(t_input *input)
{
	char	c;
	t_input	*tmp;

	if (!(tmp = input))
		store_input(shell, '\n');
	while (tmp)
	{
		if (tmp->c == '\'' || tmp->c == '"' || tmp->c == '`')
		{
			if ((c = is_quote_closed(tmp, tmp->c)) != 0)
				return (c);
			c = tmp->c;
			tmp = tmp->next;
			while (tmp && tmp->next != c)
				tmp = tmp->next;
		}
		else if (tmp->c = '[' || tmp->c == '{' || tmp->c == '(')
		{
			if ((c = is_bracket_closed(tmp, tmp->c)) != 0)
				return (c);
			c = (tmp->c == '(') ? tmp->c + 1 : tmp->c + 2;
			tmp = tmp->next;
			while (tmp && tmp->next != c)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_empty_input(t_input *input)
{
	t_input	*tmp;

	if (!(tmp = input))
		return (-1);
	while (tmp)
	{
		if ((ft_isprint(tmp->c) && tmp->c != ' ' && tmp->c != ';'))
			return (0);
	}
	return (-1);
}

static int	check_cmd(t_shell *shell)
{
	char	c;

	if (check_empty_input(shell->input) == -1)
		return (-1);
	if ((c = ended_input(shell->input) != 0))
		return (1);
	return (0);
}

int			handle_cmd(t_shell *shell)
{
	int	test;

	move_line_end(shell);
	if ((test = check_cmd(shell) == -1))
		return (-1);
	shell->hist = store_hist(shell);
	clear_input(shell); //to remove
	free_tmp_inputs(shell);
	return (0);
}
