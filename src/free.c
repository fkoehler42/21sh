/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:58:38 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/09 17:59:45 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_input_list(t_input **input, size_t *nb_elem)
{
	t_input	*tmp1;
	t_input	*tmp2;

	if (!(tmp1 = *input))
		return ;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
	*nb_elem = 0;
	*input = NULL;
}
