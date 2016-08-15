/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 12:20:59 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/15 19:29:57 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

char	*env_var_to_value(char *var)
{
	char	*tmp;
	char	*value;

	value = NULL;
	if ((tmp = (getenv(var))))
		value = ft_strdup(tmp);
	free(var);
	return (value);
}
