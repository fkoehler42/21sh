/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 20:01:15 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 15:26:52 by fkoehler         ###   ########.fr       */
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
	char	*home;
	char	*pwd;
	char	*oldpwd;

	if (g_prompt)
		free(g_prompt);
	g_prompt = NULL;
	home = getenv("HOME");
	pwd = getenv("PWD");
	oldpwd = getenv("OLDPWD");
	if (!pwd)
		g_prompt = ft_strdup("$");
	else if (!home)
		g_prompt = ft_strdup(pwd);
	else
		g_prompt = get_relative_path(home, pwd);
	return (g_prompt);
}
