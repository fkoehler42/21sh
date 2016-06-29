/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:05:22 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/29 20:30:16 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	store_input(t_shell *shell, char *buf)
{
	t_input	*new;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		exit_error(9);
	new->c = buf[0];
	new->prev = shell->curs_pos != NULL ? shell->curs_pos : NULL;
	if (!(shell->input))
	{
		new->next = NULL;
		shell->input = new;
	}
	else if (!(shell->curs_pos))
	{
		new->next = shell->input;
		new->next->prev = new;
		shell->input = new;
	}
	else
	{
		new->next = shell->curs_pos->next;
		new->prev->next = new;
		new->next != NULL ? new->next->prev = new : (0);
	}
	shell->curs_pos = new;
}

void		read_input(t_shell *shell)
{
	char	buf[7];
	size_t	buf_len;

	shell->p_len = put_prompt(get_prompt(), shell->fd);
	while (42)
	{
		ft_bzero((void *)buf, 7);
		if (read(0, buf, 7) == -1)
			exit_error(7);
		if ((buf_len = ft_strlen(buf)) > 0)
			parse_input(shell, buf, buf_len, shell->p_len);
	}
}

int			parse_input(t_shell *shell, char *buf, size_t buf_len, size_t p_len)
{
	if (buf_len == 3 && buf[0] == 27 && buf[1] == 91)
		parse_keys1(shell, buf);
	else if (buf_len == 1)
	{
		store_input(shell, buf);
		shell->input_len++;
		print_input(shell, shell->curs_pos, p_len);
	}
	return (0);
}
