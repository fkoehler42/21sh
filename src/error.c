/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 10:52:39 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 08:27:15 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	exit_error(int errnum)
{
	if (errnum == 0)
		ft_putstr_fd("21sh: Unable to open the terminal device file\n", 2);
	else if (errnum == 1)
		ft_putstr_fd("21sh: Unable to retrieve the terminal name\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("21sh: No entry found for the specified terminal\n", 2);
	else if (errnum == 3)
		ft_putstr_fd("21sh: Unable to find the terminfo database\n", 2);
	else if (errnum == 4)
		ft_putstr_fd("21sh: Unable to retrieve the terminal parameters\n", 2);
	else if (errnum == 5)
		ft_putstr_fd("tcsetattr: Unable to set the terminal parameters\n", 2);
	else if (errnum == 6)
		ft_putstr_fd("malloc: Memory allocation has failed\n", 2);
	else if (errnum == 7)
		ft_putstr_fd("read: An error occured while reading input\n", 2);
	else if (errnum == 8)
		ft_putstr_fd("21sh: Required terminal capabilities not supported\n", 2);
	else if (errnum == 9)
		ft_putstr_fd("21sh: Memory allocation has failed\n", 2);
	else if (errnum == 10)
		ft_putstr_fd("ioctl: Unable to get the terminal state infos\n", 2);
	exit(EXIT_FAILURE);
}

int		cmd_error(int errnum)
{
	if (errnum == 0)
		ft_putstr_fd("21sh: Parse error near `|'", 2);
	return (-1);
}
/*
int		env_error(int errnum, char *arg)
{
	ft_putstr_fd("21sh: ", 2);
	if (errnum == 0)
		ft_putstr_fd("variable is empty\n", 2);
	else if (errnum == 1)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": variable is not valid\n", 2);
	}
	return (-1);
}*/
