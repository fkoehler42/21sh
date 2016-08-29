/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 10:52:39 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/29 17:28:05 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	quit_error(int errnum)
{
	t_shell *shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[2];
	if (errnum == 0)
		ft_putstr_fd("21sh: Unable to open the terminal device file\n", fd);
	else if (errnum == 1)
		ft_putstr_fd("21sh: Unable to retrieve the terminal name\n", fd);
	else if (errnum == 2)
		ft_putstr_fd("21sh: No entry found for the specified terminal\n", fd);
	else if (errnum == 3)
		ft_putstr_fd("21sh: Unable to find the terminfo database\n", fd);
	else if (errnum == 4)
		ft_putstr_fd("21sh: Unable to retrieve the terminal parameters\n", fd);
	else if (errnum == 5)
		ft_putstr_fd("tcsetattr: Unable to set the terminal parameters\n", fd);
	else if (errnum == 6)
		ft_putstr_fd("malloc: Memory allocation has failed\n", fd);
	else if (errnum == 7)
		ft_putstr_fd("read: An error occured while reading input\n", fd);
	else if (errnum == 8)
		ft_putstr_fd("21sh: Required terminal capabilities not supported\n", fd);
	else if (errnum == 9)
		ft_putstr_fd("21sh: Memory allocation has failed\n", fd);
	else if (errnum == 10)
		ft_putstr_fd("ioctl: Unable to get the terminal state infos\n", fd);
	exit(EXIT_FAILURE);
}

int		cmd_error(int errnum, char c)
{
	t_shell *shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[2];
	if (errnum == 0)
	{
		ft_putstr_fd("21sh: Parse error near '", fd);
		ft_putchar_fd(c, fd);
		ft_putstr_fd("'\n", fd);
	}
	return (-1);
}
/*
int		env_error(int errnum, char *arg)
{
	ft_putstr_fd("21sh: ", fd);
	if (errnum == 0)
		ft_putstr_fd("variable is empty\n", fd);
	else if (errnum == 1)
	{
		ft_putstr_fd(arg, fd);
		ft_putstr_fd(": variable is not valid\n", fd);
	}
	return (-1);
}*/
