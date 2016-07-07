/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 16:59:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/07 19:58:41 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_keys1(t_shell *shell, char *buf)
{
	if (buf[1] == 91)
	{
		if (buf[2] == 68)
			move_left(shell);
		else if (buf[2] == 67)
			move_right(shell);
		else if (buf[2] == 72)
			move_line_start(shell);
		else if (buf[2] == 70)
			move_line_end(shell);
	}
}

void	parse_keys2(t_shell *shell, char *buf)
{
	if (buf[0] == 27 && buf[1] == 91 &&
		buf[2] == 49 && buf[3] == 59 && buf[4] == 50)
	{
		if (buf[5] == 68)
			move_left_word(shell);
		else if (buf[5] == 67)
			move_right_word(shell);
		else if (buf[5] == 65)
			move_line_up(shell);
		else if (buf[5] == 66)
			move_line_down(shell);
	}
}

void	parse_keys4(t_shell *shell, char *buf, size_t buf_len)
{
	if (buf_len == 2 && buf[0] == -61 && buf[1] == -89)
		copy_eol(shell);
	else if (buf_len == 3 && buf[0] == -30 && buf[1] == -120 && buf[2] == -126)
		copy_all(shell);
	else if (buf_len == 3 && buf[0] == -30 && buf[1] == -120 && buf[2] == -102)
	{
		paste_buffer(shell);
			/* print_input(shell, shell->curs_pos->next, shell->p_len); */
	}
}
