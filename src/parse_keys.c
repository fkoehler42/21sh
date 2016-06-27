/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 16:59:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/27 18:40:40 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_keys1(t_shell *shell, char *buf)
{
	if (buf[2] == 68)
		move_left(shell);
	else if (buf[2] == 67)
		move_right(shell);
	else if (buf[2] == 72)
		line_start(shell);
	else if (buf[2] == 70)
		line_end(shell);
	return (0);
}
