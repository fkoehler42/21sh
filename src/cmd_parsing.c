/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/12 15:03:04 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		handle_cmd(t_shell *shell)
{
	if (!shell->input)
		return (-1);
	shell->hist = store_hist(shell, 0);
	move_line_start(shell);
	tputs(tgetstr("cd", NULL), shell->fd, &putchar);
	free_input_list(&(shell->input), &(shell->input_len));
	return (0);
}
