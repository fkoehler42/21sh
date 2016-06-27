/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 18:19:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/27 12:46:37 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			putchar(int c)
{
	t_shell	*shell;

	shell = get_struct(0);
	write(shell->fd, &c, 1);
	return (0);
}

void		insert_char(t_shell *shell, char c)
{
	if (!shell->line_pos->next)
		ft_putchar_fd(c, shell->fd);
	else
	{
		if ((tputs(tgetstr("im", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
		ft_putchar_fd(c, shell->fd);
		if ((tputs(tgetstr("ei", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
	}
}
