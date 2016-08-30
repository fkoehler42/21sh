/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/30 12:46:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_valid_redir(char *s, int start, int explicit_fd)
{
	int		i;
	int		redir;

	redir = 0;
	i = start;
	(explicit_fd) ? (i++) : (0) ;
	if (s[i] == '>' && s[i + 1] == '>' && (i += 2))
		redir = DREDIR;
	else if (s[i] == '<' && s[i + 1] == '<' && (i += 2))
		redir = DBREDIR;
	else if (s[i] == '>' && ++i)
		redir = REDIR;
	else if (s[i] == '<' && ++i)
		redir = BREDIR;
	if (s[i] == '&')
	{
		if ((redir != REDIR) || ((!s[i + 1]) || (s[i + 1] && s[i + 2])))
			return (cmd_error(0, "&"));
		if ((!ft_isdigit(s[i + 1])) && (s[i + 1] != '-'))
			return (cmd_error(2, &s[i + 1]));
		if (s[i + 1] > '2')
			return (cmd_error(1, &s[i + 1]));
	}
	return (0);
}

static int	check_redir(char *s, int i)
{
	if (i == 0)
	{
		cmd_error(0, &s[i]);
		return (-1);
	}
	if ((s[i - 1] == '0' || s[i - 1] == '1' || s[i - 1] == '2') &&
		(i == 1 || s[i - 2] == ' '))
		return (check_valid_redir(s, i - 1, 1));
	else if (s[i] == '>' || s[i] == '<')
		return (check_valid_redir(s, i, 0));
	return (0);
}

int			strchr_redir(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (ft_isquote(s[i]) && (c = s[i++]))
		{
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == '>' || s[i] == '<')
		{
			if (check_redir(s, i) == -1)
				return (-1);
			i++;
		}
		i++;
	}
	return (0);
}
