/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 12:46:08 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/13 22:01:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		input_lst_cmp(t_input *lst1, t_input *lst2, size_t len1, size_t len2)
{
	t_input *tmp1;
	t_input *tmp2;

	if ((len1 != len2) || (len1 == 0 && len2 == 0))
		return (len1 - len2);
	tmp1 = lst1;
	tmp2 = lst2;
	while (tmp1 && tmp2)
	{
		if (tmp1->c != tmp2->c)
			return (tmp1->c - tmp2->c);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return (0);
}

void	clear_input(t_shell *shell)
{
	if (shell->input)
	{
		move_line_start(shell);
		tputs(tgetstr("cd", NULL), shell->fd, &putchar);
		free_input_list(&(shell->input), &(shell->input_len));
	}
}
