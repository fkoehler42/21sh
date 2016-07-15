/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/15 12:01:13 by fkoehler         ###   ########.fr       */
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

char		no_ended_input(t_shell *shell, char c)
{
	t_input	*tmp;

	if (!(tmp = shell->input))
		store_input(shell, '\n');
	while (tmp)
	{
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
			tmp = tmp->next;
			while (tmp && tmp->c != c)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
