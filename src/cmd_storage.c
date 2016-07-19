/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_storage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 11:04:50 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/19 15:55:40 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_btree	*store_cmd(char *str)
{
	int		i;
	t_btree	*new;

	if (!(new = (t_btree *)malloc(sizeof(*new))))
		exit_error(9);
	new->cmd = NULL;
	if ((i = ft_strrchr_index(str, ';')) != -1)
		new->type = SEM;
	else if ((i = ft_strrchr_index(str, '|')) != -1)
		new->type = PIP;
	if (i != -1)
	{
		new->left = store_cmd(ft_strsub(str, 0, i));
		i++;
		new->right = store_cmd(ft_strsub(str, i, (ft_strlen(str) - i)));
	}
	else
	{
		new->type = CMD;
		new->cmd = str;
		new->left = NULL;
		new->right = NULL;
	}
	return (new);
}
