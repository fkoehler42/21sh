/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_interpreting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/26 23:44:09 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*replace_special_char(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			tmp = ft_replace_str(s, i, 1, "");
			free(s);
			s = tmp;
			if (s[i] == '\\' || s[i] == '$')
				i++;
		}
		else
		{
			if (s[i] == '$' && (i == 0 || (s[i - 1] != '\\')))
				s = str_replace_var(s, i);
			i++;
		}
	}
	return (s);
}

static char	*interpret_special_char(char *sub_arg)
{
	int		quote;

	if ((quote = is_str_quoted(sub_arg)))
		sub_arg = strdup_remove_quotes(sub_arg);
	if (quote == 1)
		return (sub_arg);
	return (replace_special_char(sub_arg));
}

char		*interpret_cmd_arg(char *cmd_arg)
{
	int		i;
	char	*ret;
	char	**arg_tab;

	i = 0;
	ret = NULL;
	arg_tab = str_subsplit_arg(cmd_arg);
	while (arg_tab[i])
	{
		arg_tab[i] = interpret_special_char(arg_tab[i]);
		/* ft_printf("\narg_modified : %s\n", arg_tab[i]); */
		i++;
	}
	ret = ft_multi_strjoin(arg_tab, "");
	free_tab(arg_tab);
	free(cmd_arg);
	return (ret);
}
