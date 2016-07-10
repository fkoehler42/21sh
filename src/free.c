/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:58:38 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/10 17:04:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_input_list(t_input **input, size_t *nb_elem)
{
	t_input	*tmp1;
	t_input	*tmp2;

	if (!(tmp1 = *input))
		return ;
	if (tmp1->prev)
		tmp1->prev->next = NULL;
	else
		*input = NULL;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
		--(*nb_elem);
	}
}
