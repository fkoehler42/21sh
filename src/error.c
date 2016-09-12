/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 10:52:39 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/12 17:45:06 by fkoehler         ###   ########.fr       */
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
		ft_putstr_fd("21sh: unable to open the terminal device file\n", fd);
	else if (errnum == 1)
		ft_putstr_fd("21sh: unable to retrieve the terminal name\n", fd);
	else if (errnum == 2)
		ft_putstr_fd("21sh: no entry found for the specified terminal\n", fd);
	else if (errnum == 3)
		ft_putstr_fd("21sh: unable to find the terminfo database\n", fd);
	else if (errnum == 4)
		ft_putstr_fd("21sh: unable to retrieve the terminal parameters\n", fd);
	else if (errnum == 5)
		ft_putstr_fd("tcsetattr: unable to set the terminal parameters\n", fd);
	else if (errnum == 6)
		ft_putstr_fd("malloc: memory allocation has failed\n", fd);
	else if (errnum == 7)
		ft_putstr_fd("read: an error occured while reading the input\n", fd);
	else if (errnum == 8)
		ft_putstr_fd("21sh: required terminal capabilities not supported\n", fd);
	else if (errnum == 9)
		ft_putstr_fd("21sh: memory allocation has failed\n", fd);
	else if (errnum == 10)
		ft_putstr_fd("ioctl: unable to get the terminal state infos\n", fd);
	exit(EXIT_FAILURE);
}

int		exec_error(int errnum, char *arg)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(arg, 2);
	if (errnum == 0)
		ft_putstr_fd(": error on child process creation\n", 2);
	else if (errnum == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("environment variable PATH is not set or is empty\n", 2);
	else if (errnum == 3)
		ft_putstr_fd(": permission denied\n", 2);
	else if (errnum == 4)
		ft_putstr_fd(": error on child process execution\n", 2);
	else if (errnum == 5)
		ft_putstr_fd("error on pipe creation\n", 2);
	else if (errnum == 6)
		ft_putstr_fd(": error on file descriptor duplication\n", 2);
	else if (errnum == 7)
		ft_putstr_fd(": error on file descriptor closing\n", 2);
	else if (errnum == 8)
		ft_putstr_fd(": error on file opening\n", 2);
	return (-1);
}

int		cmd_error(int errnum, char c, char *s)
{
	t_shell *shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[2];
	if (errnum == 0)
	{
		ft_putstr_fd("21sh: parse error near '", fd);
		ft_putchar_fd(c, fd);
		ft_putstr_fd("'\n", fd);
	}
	else if (errnum == 1)
		ft_putstr_fd("21sh: bad file descriptor\n", fd);
	else if (errnum == 2)
	{
		ft_putstr_fd("21sh: ", fd);
		ft_putstr_fd(s, fd);
		ft_putstr_fd(": ambigous redirect\n", fd);
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
