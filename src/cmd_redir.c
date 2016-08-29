/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/29 21:07:39 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_valid_redir(char *s, int start, int explicit_fd)
{
	int	i;
	int	redir;

	redir = 0;
	(explicit_fd) ? (i++) : (0) ;
	if (s[i] == '>' && s[i + 1] == '>')
		redir = DREDIR;
	else if (s[i] == '>')
		redir = REDIR;
	else if (s[i] == '<' && s[i + 1] == '<')
		redir = DBREDIR;
	else if (s[i] == '<')
		redir = BREDIR;
	(redir == (DREDIR || DBREDIR)) ? (i += 2) : (0) ;
	(redir == (REDIR || BREDIR)) ? (i++) : (0) ;
	((s[i] == '&') && (redir != REDIR)) ? (return (cmd_error(0, '&'))) : (0) ;
}

static char	*check_redir(char *s, int i)
{
	int	start;

	if (i == 0)
	{
		cmd_error(0, s[i]);
		return (NULL);
	}
	if ((s[i - 1] == '0' || s[i - 1] == '1' || s[i - 1] == '2') &&
		(i == 1 || s[i - 2] == ' '))
		check_valid_redir(s, i - 1, 1)
	else if (s[i] == '>' || s[i] == '<')
		check_valid_redir(s, i, 0);
}

int			strchr_redir(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (ft_isquote(s[i]) && (c = s[i]))
		{
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == '>' || s[i] == '<')
			strchr_redir(check_redir(s, i));
		i++;
	}
}
