/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/15 13:03:37 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

static char	is_bracket_closed(t_input *tmp, char c)
{
	size_t	count;
	char	d;

	count = 1;
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
			count++;
		else if (tmp->c == d && (--count == 0))
			return (0);
		tmp = tmp->next;
	}
	return (d);
}

static char	check_quotes(t_input **input, char c)
{
	t_input	*tmp;

	tmp = *input;
	if (tmp->c == '\'' || tmp->c == '"' || tmp->c == '`')
	{
		if ((c = is_quote_closed(tmp, tmp->c)) != 0)
			return (c);
		c = tmp->c;
		tmp = tmp->next;
		while (tmp && tmp->c != c)
			tmp = tmp->next;
	}
	else if (tmp->c == '[' || tmp->c == '{' || tmp->c == '(')
	{
		if ((c = is_bracket_closed(tmp, tmp->c)) != 0)
			return (c);
		c = (tmp->c == '(') ? tmp->c + 1 : tmp->c + 2;
		while ((tmp = tmp->next) && tmp && tmp->c != c)
		{
			if (tmp->c == '\'' || tmp->c == '"' || tmp->c == '`')
				c = tmp->c;
		}
	}
	*input = tmp;
	return (0);
}

char		valid_input(t_input *input, char c)
{
	int		pipe_ret;
	t_input	*tmp;

	tmp = input;
	if ((pipe_ret = check_pipes(input, 0)) == -1)
		return ('|');
	if (pipe_ret == 1)
		return (cmd_error(0));
	while (tmp)
	{
		if ((c = check_quotes(&tmp, tmp->c)) != 0)
			return (c);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
