/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.4fd.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 16/08/17 10:45:40 by fkoehler            #+#    #+#             */
/*   Updated: 2016/09/12 16:34:40 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		cd_error(int errnum, char *arg)
{
	t_shell	*shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[3];
	ft_putstr_fd("cd: ", fd);
	if (errnum == 0)
		ft_putstr_fd("environment variable HOME is not set\n", fd);
	else if (errnum == 1)
		ft_putstr_fd("environment variable OLDPWD is not set\n", fd);
	else if (errnum == 2)
		ft_putstr_fd("too many arguments\n", fd);
	else if (errnum == 3 || errnum == 4 || errnum == 5 || errnum == 7)
		ft_putstr_fd(arg, fd);
	else if (errnum == 6 || errnum == 8)
		ft_putstr_fd("an error occured while ", fd);
	if (errnum == 3)
		ft_putstr_fd(" : permission denied\n", fd);
	else if (errnum == 4)
		ft_putstr_fd(" : no such file or directory\n", fd);
	else if (errnum == 5)
		ft_putstr_fd(" : not a directory\n", fd);
	else if (errnum == 6)
		ft_putstr_fd("switching the actual directory with 'chdir'\n", fd);
	else if (errnum == 8)
		ft_putstr_fd("checking the actual directory with 'getcwd'\n", fd);
	return (-1);
}

int		env_error(int errnum, int flag)
{
	t_shell	*shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[3];
	if (errnum == 0)
	{
		ft_putstr_fd("env: illegal option -- ", fd);
		ft_putchar_fd(flag, fd);
	}
	else if (errnum == 1)
	{
		ft_putstr_fd("env: option requires an argument -- ", fd);
		ft_putchar_fd(flag, fd);
	}
	else if (errnum == 2)
		ft_putstr_fd("env: no option specified", fd);
	ft_putstr_fd("\nusage: env [-i] [-u name] [name=value] ", fd);
	ft_putstr_fd("[utility [argument(s)]]\n", fd);
	return (-1);
}

void	env_var_error(int errnum, char *cmd, char *arg)
{
	t_shell	*shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[3];
	if (errnum == 0)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": command requires argument\n", fd);
	}
	else if (errnum == 1)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": argument is not valid: ", fd);
		ft_putendl_fd(arg, fd);
	}
}

int		exit_error(int errnum, char *arg)
{
	t_shell	*shell;
	int		fd;

	shell = get_struct(0);
	fd = shell->fd[3];
	if (errnum == 0)
		ft_putstr_fd("exit: too many arguments\n", fd);
	else if (errnum == 1)
	{
		ft_putstr_fd("exit: argument is not numeric: ", fd);
		ft_putendl_fd(arg, fd);
	}
	else if (errnum == 2)
	{
		ft_putstr_fd("exit: number is too long: ", fd);
		ft_putendl_fd(arg, fd);
	}
	if (arg[0])
		free(arg);
	return (1);
}
