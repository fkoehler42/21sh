/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 16:59:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/30 17:09:17 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_keys1(t_shell *shell, char *buf, size_t buf_len)
{
	if (buf_len == 3)
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
	else if (buf_len == 6 && buf[2] == 49 && buf[3] == 59 && buf[4] == 50)
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
	return (0);
}
