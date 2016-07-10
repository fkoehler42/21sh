/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 18:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/10 20:57:46 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	store_hist(t_shell *shell)
{
	t_hist	*new;

	if (!(new = (t_hist *)malloc(sizeof(*new))))
		exit_error(9);
	new->next = NULL;
	new->prev = shell->hist;
	if (!shell->input)
}

int		history_prev(t_shell *shell)
{
	store_hist(shell);
	return (0);
}

int		history_next(t_shell *shell)
{
	(void)shell;
	return (0);
}
