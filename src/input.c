/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:05:22 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 18:52:59 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	read_input(t_shell *shell)
{
	char	buf[7];
	int	i = 0;

	(void)shell;
	g_prompt = get_prompt();
	while (42)
	{
		ft_bzero((void *)buf, 7);
		if (read(0, buf, 7) == -1)
			exit_error(7);
		if (buf[0])
		{
			ft_putchar_fd('-', 2);
			i = 0;
			while (buf[i])
			{
				ft_putnbr(buf[i]);
				i++;
			}
			ft_putchar_fd(' ', 2);
		}
			/* parse_input(shell, buf); */
	}
}
