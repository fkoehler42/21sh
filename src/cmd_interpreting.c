/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_interpreting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/21 17:03:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*interpret_cmd_param(char *param)
{
	char	*tmp;
	int		is_quoted;

	is_quoted = is_str_quoted(param);
	if ((is_quoted != 1) && (ft_strchr(param, '$') != NULL))
		param = str_replace_var(param);
	if (is_quoted > 0)
	{
		tmp = param;
		param = strdup_remove_quotes(param);
		free(tmp);
	}
	return (param);
}
