/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/11 18:16:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		handle_cmd(t_shell *shell)
{
	if (!shell->input)
		return (-1);
	store_hist(shell);
	move_line_start(shell);
	tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	shell->input = NULL;
	shell->input_len = 0;
	return (0);
}
