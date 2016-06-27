/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 18:19:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/27 20:10:34 by fkoehler         ###   ########.fr       */
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

void		print_input(t_shell *shell, t_input *curs_pos)
{
	int		i;
	char	buf[shell->line_len + 1];
	t_input	*tmp;

	i = 0;
	if (!shell->curs_pos->next)
		ft_putchar_fd(curs_pos->c, shell->fd);
	else
	{
		tmp = curs_pos;
		ft_bzero((void *)buf, shell->line_len + 1);
		if ((tputs(tgetstr("cd", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
		while (tmp)
		{
			buf[i++] = tmp->c;
			tmp = tmp->next;
		}
		ft_putstr_fd(buf, shell->fd);
		while (i-- > 1)
		{
			if ((tputs(tgetstr("le", NULL), shell->fd, &putchar)) == -1)
				exit_error(8);
		}
	}
}
