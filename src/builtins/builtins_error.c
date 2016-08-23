/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 12:45:24 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 09:32:47 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		cd_error(int errnum, char *arg)
{
	ft_putstr_fd("cd: ", 2);
	if (errnum == 0)
		ft_putstr_fd("environment variable HOME is not set\n", 2);
	else if (errnum == 1)
		ft_putstr_fd("environment variable OLDPWD is not set\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("too many arguments\n", 2);
	else if (errnum == 3 || errnum == 4 || errnum == 5 || errnum == 7)
		ft_putstr_fd(arg, 2);
	else if (errnum == 6 || errnum == 8)
		ft_putstr_fd("an error occured while ", 2);
	if (errnum == 3)
		ft_putstr_fd(" : permission denied\n", 2);
	else if (errnum == 4)
		ft_putstr_fd(" : no such file or directory\n", 2);
	else if (errnum == 5)
		ft_putstr_fd(" : not a directory\n", 2);
	else if (errnum == 6)
		ft_putstr_fd("switching the actual directory with 'chdir'\n", 2);
	else if (errnum == 8)
	{
		ft_putstr_fd("checking the actual directory with 'getcwd'\n", 2);
		ft_putstr_fd("send an absolute path to cd could fix the problem\n", 2);
	}
	return (-1);
}

int		env_error(int errnum, int flag)
{
	if (errnum == 0)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(flag, 2);
	}
	else if (errnum == 1)
	{
		ft_putstr_fd("env: option requires an argument -- ", 2);
		ft_putchar_fd(flag, 2);
	}
	else if (errnum == 2)
		ft_putstr_fd("env: no option specified", 2);
	ft_putstr_fd("\nusage: env [-i] [-u name] [name=value] ", 2);
	ft_putstr_fd("[utility [argument(s)]]\n", 2);
	return (-1);
}

void	env_var_error(int errnum, char *cmd, char *arg)
{
	if (errnum == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command requires argument\n", 2);
	}
	else if (errnum == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": argument is not valid: ", 2);
		ft_putendl_fd(arg, 2);
	}
}

int		exit_error(int errnum, char *arg)
{
	if (errnum == 0)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else if (errnum == 1)
	{
		ft_putstr_fd("exit: argument is not numeric: ", 2);
		ft_putendl_fd(arg, 2);
	}
	else if (errnum == 2)
	{
		ft_putstr_fd("exit: number is too long: ", 2);
		ft_putendl_fd(arg, 2);
	}
	if (arg[0])
		free(arg);
	return (1);
}