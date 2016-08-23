/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_interpreting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/23 14:10:53 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	del_escape_char(t_input *input, char c)
{
	(void)input;
	(void)c;
}

char	*interpret_cmd_param(char *param)
{
/*	int		i;
	int		start;
	int		end;
	char	*tmp;

	i = 0;
	while (param[i])
	{
		if (param[i] == '\'' || param[i] == '"' || param[i] == '`')
		{
			start = i;
			if ((end = ft_strchr_index(&param[i], param[i])) == -1)
				break;
			if (param[i] != '\'')
		}
	}
	is_quoted = is_str_quoted(param);
	if ((is_quoted != 1) && (ft_strchr(param, '$') != NULL))
		param = str_replace_var(param);
	if (is_quoted > 0)
	{
		tmp = param;
		param = strdup_remove_quotes(param);
		free(tmp);
	}
*/	return (param);
}
