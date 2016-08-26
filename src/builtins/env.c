/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:56:41 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/27 00:39:58 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	put_env(t_env *env_lst)
{
	t_env	*tmp;

	if (env_lst)
	{
		tmp = env_lst;
		while (tmp)
		{
			ft_putstr(tmp->var);
			ft_putchar('=');
			ft_putendl(tmp->val);
			tmp = tmp->next;
		}
	}
	return (0);
}

static int	del_env_cpy(t_env **env_lst)
{
	if ((*env_lst) != NULL)
		free_env_lst(env_lst);
	return (0);
}

static int	dup_env_lst(t_env *env_lst, t_env **env_lst_cpy)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		store_env_var(env_lst_cpy, ft_strdup(tmp->var),
		ft_strdup(tmp->val));
		tmp = tmp->next;
	}
	return (0);
}

static int	parse_env_flags(char **cmd, t_env **env_lst)
{
	if (!((*cmd)[1]))
		return (env_error(2, '\0'));
	if ((*cmd)[1] == 'i')
	{
		if ((*cmd)[2])
			return (env_error(0, (*cmd)[2]));
		free_env_lst(env_lst);
	}
	else if ((*cmd)[1] == 'u' && (*cmd)[2])
	{
		del_env_var(env_lst, ft_strdup(*cmd + 2));
		return (1);
	}
	else if ((*cmd)[1] == 'u' && *(cmd + 1))
	{
		del_env_var(env_lst, ft_strdup(*(cmd + 1)));
		return (2);
	}
	else if ((*cmd)[1] == 'u' && !(*(cmd + 1)))
		return (env_error(1, 'u'));
	else
		return (env_error(0, (*cmd)[1]));
	return (1);
}

int			ft_env(char **cmd, t_env *env_lst, int i)
{
	int		j;
	t_env	*env_lst_cpy;

	env_lst_cpy = NULL;
	dup_env_lst(env_lst, &(env_lst_cpy));
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][0] == '-')
		{
			if ((j = parse_env_flags(cmd + i, &env_lst_cpy)) == -1)
				return (del_env_cpy(&env_lst_cpy));
		}
		else if (ft_strchr(cmd[i], '=') != NULL && ++j)
			ft_setenv(&cmd[i], &env_lst_cpy, 1);
		else if ((builtins_cmd(cmd + i, env_lst_cpy) == 0) ||
/*binary_cmd*/	(builtins_cmd(cmd + i, env_lst_cpy) == -1))
			return (del_env_cpy(&env_lst_cpy));
		i += j;
	}
	env_lst_cpy != NULL ? put_env(env_lst_cpy) : (0);
	free_env_lst(&env_lst_cpy);
	return (0);
}
