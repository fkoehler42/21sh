/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:05:22 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/25 20:15:52 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	read_input(t_shell *shell)
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

int		parse_input(t_shell *shell, char *buf, size_t len)
{
	if (len == 3 && buf[0] == 27 && buf[1] == 91)
		parse_keys1(shell, buf);
	else
		ft_putstr_fd(buf, shell->fd);
	return (0);
}
