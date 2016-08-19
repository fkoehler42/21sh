/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 12:20:59 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 08:07:21 by fkoehler         ###   ########.fr       */
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
			store_env_var(&(shell->env_lst), var, val);
			i++;
		}
	}
}

int		store_env_var(t_env **env_lst, char *var, char *val)
{
	t_env	*new;
	t_env	*tmp;

	if ((tmp = get_env_ptr(*env_lst, var)))
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
	if (!(*env_lst))
		*env_lst = new;
	else
	{
		tmp = *env_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}
