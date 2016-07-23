/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 16:42:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/23 17:19:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*str_replace_var(char *s)
{
//	int		i;
	int		start;

	if ((start = ft_strchr_index(s, '$')) == -1)
		return (s);
//	i = start;
	/* while (s[i] && s[i] != ) */
	return (s);
}

int		strrchr_outside_quotes(char *s, char c)
{
	int		i;
	int		j;
	char	quote;

	quote = 0;
	if (((i = ft_strrchr_index(s, c)) == -1))
	{
		free(s);
		return (-1);
	}
	j = ft_strlen(s);
	while (--j > i)
	{
		if (s[j] == quote)
			quote = 0;
		else if ((s[j] == '\'' || s[j] == '"') && !quote)
			quote = s[j];
	}
	if (quote && --j)
	{
		while (j >= 0 && s[j] != quote)
			j--;
		i = (j > 1) ? strrchr_outside_quotes(ft_strsub(s, 0, j), c) : -1;
	}
	free(s);
	return (i);
}
