/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:44:16 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 16:31:40 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	countwords(char const *s, int i, int n)
{
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' && ++i)
		{
			while (s[i] && s[i] != '"')
				i++;
			!s[i] || !s[i + 1] || s[i + 1] == ' ' || s[i + 1] == '\t' ? n++ : 0;
		}
		else if (s[i] == '\'' && ++i)
		{
			while (s[i] && s[i] != '\'')
				i++;
			!s[i] || !s[i + 1] || s[i + 1] == ' ' || s[i + 1] == '\t' ? n++ : 0;
		}
		else if (s[i] != ' ' && s[i] != '\t')
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\'' && s[i] != '"')
				i++;
			s[i] && (s[i] == '\'' || s[i] == '"') ? i-- : n++;
		}
		s[i] != 0 ? ++i : 0;
	}
	return (n);
}

static int	word_len(char const *s, int i)
{
	if (!s[i])
		return (i);
	if (s[i] == '\'' && ++i)
	{
		while (s[i] && s[i] != '\'')
			i++;
		if (s[i] && s[++i] && s[i] != ' ' && s[i] != '\t')
			i = word_len(s, i);
	}
	else if (s[i] == '"' && ++i)
	{
		while (s[i] && s[i] != '"')
			i++;
		if (s[i] && s[++i] && s[i] != ' ' && s[i] != '\t')
			i = word_len(s, i);
	}
	else
	{
		while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\'' && s[i] != '"')
			i++;
		if (s[i] && (s[i] == '\'' || s[i] == '"') && s[i + 1])
			i = word_len(s, i);
		else if (s[i] && (s[i] == '\'' || s[i] == '"'))
			i++;
	}
	return (i);
}

char		**strsplit_args(char const *s)
{
	int		i;
	int		j;
	int		start;
	char	**array;

	i = 0;
	j = 0;
	if (!(array = (char **)malloc(sizeof(char *) * (countwords(s, 0, 0) + 1))))
		quit_error(9);
	/* ft_putnbr(countwords(s, 0, 0)); */
	if (!s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		start = i;
		i = word_len(s, start);
		if (start != i)
			array[j++] = ft_strsub(s, start, (i - start));
	}
	/* ft_putnbr(j); */
	array[j] = NULL;
	return (array);
}
