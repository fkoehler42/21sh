/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 20:01:15 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/22 15:36:43 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*get_relative_path(t_env *home, t_env *pwd)
{
	int		i;
	char	*prompt;

	i = 0;
	while (home->val[i] && pwd->val[i]
			&& home->val[i] == pwd->val[i])
		i++;
	if (!home->val[i])
		prompt = ft_strjoin("~", (pwd->val + i));
	else if (!pwd->val[i] || access(pwd->val, F_OK) == 0)
		prompt = ft_strdup(pwd->val);
	else
		prompt = ft_strdup("$");
	return (prompt);
}

char		*get_prompt(t_env *env_lst)
{
	static char	*prompt = NULL;
	t_env		*home;
	t_env		*pwd;

	if (prompt != NULL)
		free(prompt);
	home = get_env_ptr(env_lst, "HOME");
	pwd = get_env_ptr(env_lst, "PWD");
	if (!pwd || !pwd->val || !pwd->val[0])
		prompt = ft_strdup("$");
	else if (!home || !home->val || !home->val[0])
		prompt = ft_strdup(pwd->val);
	else
		prompt = get_relative_path(home, pwd);
	return (prompt);
}

char		*get_special_prompt(char c)
{
	static char	*prompt = NULL;

	if (prompt != NULL)
		free(prompt);
	if (c == '\'')
		prompt = ft_strdup("quote> ");
	else if (c == '"')
		prompt = ft_strdup("dquote> ");
	else if (c == '`')
		prompt = ft_strdup("bquote> ");
	else if (c == ']')
		prompt = ft_strdup("hook> ");
	else if (c == ')')
		prompt = ft_strdup("parenth> ");
	else if (c == '}')
		prompt = ft_strdup("bracket> ");
	else if (c == '|')
		prompt = ft_strdup("pipe> ");
	else if (c == '\\')
		prompt = ft_strdup("> ");
	return (prompt);
}

int			put_prompt(char *prompt, int fd)
{
	ft_putstr_fd(CYAN, fd);
	ft_putchar_fd('[', fd);
	ft_putstr_fd(prompt, fd);
	ft_putstr_fd("]-> ", fd);
	ft_putstr_fd(OFF, fd);
	return (5 + ft_strlen(prompt));
}
