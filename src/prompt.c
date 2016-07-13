/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 20:01:15 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/13 22:23:00 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*get_relative_path(char *home, char *pwd)
{
	int		i;
	char	*prompt;

	i = 0;
	while (home[i] && pwd[i] && home[i] == pwd[i])
		i++;
	if (!home[i])
		prompt = ft_strjoin("~", (pwd + i));
	else if (!pwd[i] || access(pwd, F_OK) == 0)
		prompt = ft_strdup(pwd);
	else
		prompt = ft_strdup("$");
	return (prompt);
}

char		*get_prompt(void)
{
	static char	*prompt = NULL;
	char		*home;
	char		*pwd;
	char		*oldpwd;

	if (prompt != NULL)
		free(prompt);
	home = getenv("HOME");
	pwd = getenv("PWD");
	oldpwd = getenv("OLDPWD");
	if (!pwd)
		prompt = ft_strdup("$");
	else if (!home)
		prompt = ft_strdup(pwd);
	else
		prompt = get_relative_path(home, pwd);
	return (prompt);
}

int			put_prompt(char *prompt, int fd)
{
	ft_putstr_fd(CYAN, fd);
	ft_putstr_fd(prompt, fd);
	ft_putstr_fd(" -> ", fd);
	ft_putstr_fd(OFF, fd);
	return (4 + ft_strlen(prompt));
}
