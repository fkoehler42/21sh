/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/30 21:54:43 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_valid_redir(char *s, int start, int i, t_btree *link)
{
	int	redir;

	(void)link;
	redir = 0;
	if (s[i] == '>' && s[i + 1] == '>' && (i += 2))
		redir = DREDIR;
	else if (s[i] == '<' && s[i + 1] == '<' && (i += 2))
		redir = DBREDIR;
	else if (s[i] == '>' && ++i)
		redir = REDIR;
	else if (s[i] == '<' && ++i)
		redir = BREDIR;
	if (s[i] == '&' && ++i)
	{
		if ((redir != REDIR) || (!s[i]) || (s[i + 1] && s[i + 1] != ' '))
			return (cmd_error(0, "&"));
		if ((!ft_isdigit(s[i])) && (s[i] != '-'))
			return (cmd_error(2, &s[i]));
		if (s[i] > '2')
 			return (cmd_error(1, &s[i]));
		i++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]))
		i++;
//	add_redir(get_struct(0),
	ft_putendl(ft_strsub(s, start, (i - start + 1)));
	return (0);
}

static int	check_redir(t_btree *link, int i)
{
	int	j;

	j = i;
	while (j >= 0 && ft_isdigit(link->str[j]))
		j--;
	if (j == i)
		return (check_valid_redir(link->str, i, i, link));
	else
		return (check_valid_redir(link->str, j, i, link));
	return (0);
}

int			strchr_redir(t_btree *link)
{
	int		i;
	char	c;

	i = 0;
	while (ft_isspace(link->str[i]))
		i++;
	if (link->str[i] && (link->str[i] == '>' ||	(link->str[i] == '<' &&
		(!link->str[i + 1] || link->str[i + 1] != '<'))))
		return (link->str[i] == '>') ? cmd_error(0, ">") : cmd_error(0, "<") ;
	while (link->str[i])
	{
		if (ft_isquote(link->str[i]) && (c = link->str[i++]))
		{
			while (link->str[i] && link->str[i] != c)
				i++;
		}
		else if (link->str[i] == '>' || link->str[i] == '<')
		{
			if (check_redir(link, i) == -1)
				return (-1);
			i++;
		}
		link->str[i] ? (i++) : (0);
	}
	return (0);
}
