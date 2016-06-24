/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 12:20:59 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 14:02:56 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	store_environ(t_shell *shell, char **environ)
{
	int		i;
	int		j;
	char	*var;
	char	*val;

	i = 0;
	while (environ[i])
	{
		if ((j = ft_strchr_index(environ[i], '=')) <= 0)
			i++;
		else
		{
			var = ft_strsub(environ[i], 0, j);
			val = ft_strsub(environ[i], j + 1, (ft_strlen(environ[i]) - j - 1));
			if (check_env_var(var) == -1)
			{
				free(var);
				free(val);
			}
			else
				store_env_var(shell, var, val);
			i++;
		}
	}
}

int		store_env_var(t_shell *shell, char *var, char *val)
{
	t_env	*new;
	t_env	*tmp;

	if ((tmp = get_env_ptr(shell->env_lst, var)))
	{
		free(var);
		free(tmp->val);
		tmp->val = val;
		return (0);
	}
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		exit_error(6);
	new->var = var;
	new->val = val;
	new->next = NULL;
	if (!(shell->env_lst))
		shell->env_lst = new;
	else
	{
		tmp = shell->env_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

t_env	*get_env_ptr(t_env *env_lst, char *var)
{
	t_env	*tmp;

	if (!env_lst)
		return (NULL);
	tmp = env_lst;
	while (tmp && (ft_strcmp(tmp->var, var) != 0))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}

int		check_env_var(char *var)
{
	int		i;

	i = 0;
	if (!var[i])
		return (env_error(0, ""));
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (env_error(1, var));
		i++;
	}
	return (0);
}
