/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:05:22 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/27 12:46:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	store_input(t_shell *shell, char *buf)
{
	t_input	*new;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		exit_error(9);
	new->c = buf[0];
	if (!(shell->line_pos))
	{
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		new->prev = shell->line_pos;
		new->next = shell->line_pos->next;
		shell->line_pos->next = new;
	}
	shell->line_pos = new;
}

void		read_input(t_shell *shell)
{
	char	buf[7];
	size_t	buf_len;

	put_prompt(get_prompt(), shell->fd);
	while (42)
	{
		ft_bzero((void *)buf, 7);
		if (read(0, buf, 7) == -1)
			exit_error(7);
		if ((buf_len = ft_strlen(buf)) > 0)
			parse_input(shell, buf, buf_len);
	}
}

int			parse_input(t_shell *shell, char *buf, size_t len)
{
	if (len == 3 && buf[0] == 27 && buf[1] == 91)
		parse_keys1(shell, buf);
	else if (len == 1)
	{
		store_input(shell, buf);
		insert_char(shell, shell->line_pos->c);
	}
	return (0);
}
