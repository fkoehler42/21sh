/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/01 21:22:48 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_valid_redir_param(char *s, int start, int i, t_btree *link)
{
	(void)link;
	if (ft_str_isempty(s + i))
		return (cmd_error(0, s[i - 1], NULL));
	if (s[i] == ' ')
		i++;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '>' && s[i] != '<')
		i++;
	ft_putendl(ft_strsub(s, start, (i - start + 1)));
	return (0);
}

static int	check_valid_redir(char *s, int start, int i, t_btree *link)
{
	int	redir;

	(void)link;
	redir = 0;
	if (s[i] == '>' && s[i + 1] == '>' && (i += 2))
		redir = DREDIR;
	else if (s[i] == '<' && s[i + 1] == '<' && (i += 2))
		redir = HEREDOC;
	else if ((s[i] == '>' || s[i] == '<') && ++i)
		redir = (s[i - 1] == '>') ? REDIR : BREDIR ;
	if (s[i] == '&' && ++i)
	{
		if ((redir != REDIR) || (!s[i]) || (s[i + 1] && s[i + 1] != ' '))
			return (cmd_error(0, s[i - 1], NULL));
		if ((!ft_isdigit(s[i])) && (s[i] != '-'))
			return (cmd_error(2, 0, s + i));
		if (s[i] > '2')
 			return (cmd_error(1, 0, s + i));
		i++;
	}
	else
		return (check_valid_redir_param(s, start, i, link));
	ft_putendl(ft_strsub(s, start, (i - start + 1)));
	return (0);
}

static int	check_redir_start(t_btree *link, int i)
{
	int	j;

	j = i;
	while (j >= 0 && ft_isdigit(link->str[j]))
		j--;
	return (check_valid_redir(link->str, j, i, link));
}

int			strchr_redir(t_btree *link)
{
	int		i;
	char	c;

	i = 0;
	while (link->str[i] && ft_isspace(link->str[i]))
		i++;
	if (link->str[i] && (link->str[i] == '>' ||	(link->str[i] == '<' &&
		(!link->str[i + 1] || link->str[i + 1] != '<'))))
		return (cmd_error(0, link->str[i], NULL));
	while (link->str[i])
	{
		if (ft_isquote(link->str[i]) && (c = link->str[i++]))
		{
			while (link->str[i] && link->str[i] != c)
				i++;
		}
		else if (link->str[i] == '>' || link->str[i] == '<')
		{
			if (check_redir_start(link, i) == -1)
				return (-1);
			i++;
		}
		link->str[i] ? (i++) : (0);
	}
	return (0);
}
