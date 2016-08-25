/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_interpreting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 15:21:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/25 19:43:08 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*interpret_cmd_arg(char *cmd_arg)
{
	int		i;
	char	**arg_tab;

	i = 0;
	arg_tab = str_subsplit_arg(cmd_arg);
	while (arg_tab[i])
	{
		i++;
	}
	return (cmd_arg);
}
