/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 16:42:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/15 19:30:09 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_str_quoted(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (s[0] == '\'' && s[len - 1] == '\'')
		return (1);
	else if (s[0] == '"' && s[len - 1] == '"')
		return (2);
	return (0);
}

char	*str_replace_var(char *s)
{
	int		i;
	int		start;
	char	*tmp;
	char	*s1;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && !ft_isspace(s[i + 1]) && s[i + 1] != '$')
		{
			start = i;
			i++;
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			if ((tmp = env_var_to_value(ft_strsub(s, (start + 1), (i - start - 1)))))
			{
				s1 = ft_replace_str(s, start, (i - start), tmp);
				free(tmp);
				free(s);
				return (str_replace_var(s1));
			}
		}
		s[i] ? i++ : (0);
	}
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
