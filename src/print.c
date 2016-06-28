/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 18:19:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/28 18:01:42 by fkoehler         ###   ########.fr       */
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

static void	print_eol(t_shell *shell, char *buf, size_t p_len, int b_len)
{
	if ((shell->col % (shell->input_len + p_len)) == 0)
	{
		ft_putstr_fd(buf, shell->fd);
		ft_putchar_fd('\n', shell->fd);
	}
	else if ((shell->col % (shell->input_len + p_len)) == (shell->col - 1))
	{
		ft_putnstr_fd(buf, b_len - 1, shell->fd);
		ft_putchar_fd(buf[b_len - 1], shell->fd);
	}
	else
		ft_putstr_fd(buf, shell->fd);
	replace_cursor(shell);
}

void		print_input(t_shell *shell, t_input *curs_pos, size_t p_len)
{
	int		i;
	char	buf[shell->input_len + 1];
	t_input	*tmp;

	i = 0;
	if (!shell->curs_pos->next)
		ft_putchar_fd(curs_pos->c, shell->fd);
	else
	{
		tmp = curs_pos;
		ft_bzero((void *)buf, shell->input_len + 1);
		if ((tputs(tgetstr("cd", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
		if ((tputs(tgetstr("sc", NULL), shell->fd, &putchar)) == -1)
			exit_error(8);
		while (tmp)
		{
			buf[i++] = tmp->c;
			tmp = tmp->next;
		}
		print_eol(shell, buf, p_len, i);
	}
}
