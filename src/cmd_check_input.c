/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/21 20:17:01 by fkoehler         ###   ########.fr       */
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
		else if (tmp->c == d)
			return (0);
		tmp = tmp->next;
	}
	return (d);
}

static char	check_quote_type(t_input **tmp, char c)
{
	if ((*tmp)->c == '\'' || (*tmp)->c == '"' || (*tmp)->c == '`')
	{
		if ((c = is_quote_closed(*tmp, (*tmp)->c)) != 0)
			return (c);
		c = (*tmp)->c;
		*tmp = (*tmp)->next;
		while (*tmp && (*tmp)->c != c)
			*tmp = (*tmp)->next;
	}
	else if ((*tmp)->c == '[' || (*tmp)->c == '{' || (*tmp)->c == '(')
	{
		if ((c = is_bracket_closed(*tmp, (*tmp)->c)) != 0)
			return (c);
		c = ((*tmp)->c == '(') ? (*tmp)->c + 1 : (*tmp)->c + 2;
		*tmp = (*tmp)->next;
		while (*tmp && (*tmp)->c != c)
		{
			if ((*tmp)->c == '\'' || (*tmp)->c == '"' || (*tmp)->c == '`')
				c = (*tmp)->c;
			*tmp = (*tmp)->next;
		}
	}
	return (0);
}

char		valid_input(t_input *input, char c)
{
	t_input	*tmp;

	tmp = input;
	if (parse_pipe_cmd(input, 0) == -1)
		return ('|');
	while (tmp)
	{
		if ((c = check_quote_type(&tmp, tmp->c)) != 0)
			return (c);
		tmp = tmp->next;
	}
	return (0);
}
