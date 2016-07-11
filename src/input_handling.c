/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:05:22 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/11 15:43:13 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	store_input(t_shell *shell, char c)
{
	t_input	*new;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		exit_error(9);
	new->c = c;
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

void	delete_input(t_shell *shell, t_input *input, int i)
{
	if (!input->prev && !input->next)
		shell->input = NULL;
	else if (!input->prev)
	{
		shell->input = input->next;
		shell->input->prev = NULL;
	}
	else if (!input->next)
		input->prev->next = NULL;
	else
	{
		input->prev->next = input->next;
		input->next->prev = input->prev;
	}
	if (i)
		shell->curs_pos = input->prev;
	free(input);
	shell->input_len--;
}

void	read_input(t_shell *shell)
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

void	parse_input(t_shell *shell, char *buf, size_t buf_len, size_t p_len)
{
	if (buf_len == 3 && buf[0] == 27)
		parse_keys1(shell, buf);
	else if (buf_len == 6)
		parse_keys2(shell, buf);
	else if (buf_len == 1 && ft_isprint(buf[0]))
	{
		store_input(shell, buf[0]);
		shell->input_len++;
		print_input(shell, shell->curs_pos, p_len);
	}
	else
		parse_keys3(shell, buf, buf_len);
}
