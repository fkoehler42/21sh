/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 12:46:08 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/15 14:27:11 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t	lst_len(t_input *lst)
{
	size_t	len;
	t_input	*tmp;

	len = 0;
	if (!(tmp = lst))
		return (0);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	lst_cpy(t_input *src, t_input **dst)
{
	t_input	*tmp;

	if (!(tmp = src))
		return ;
	while (tmp)
	{
		store_buffer(dst, tmp->c);
		tmp = tmp->next;
	}
}

char	*lst_to_str(t_input *lst)
{
	int		i;
	size_t	len;
	char	*str;

	i = 0;
	len = lst_len(lst);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		exit_error(9);
	while (len--)
	{
		str[i] = lst->c;
		lst = lst->next;
		i++;
	}
	str[i] = 0;
	return (str);
}
