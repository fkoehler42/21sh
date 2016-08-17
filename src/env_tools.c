/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 12:20:59 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/17 17:16:45 by fkoehler         ###   ########.fr       */
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

int		set_new_pwd(t_env *env_lst)
{
	char	*current_path;
	t_env	*pwd;

	current_path = NULL;
	if (!(current_path = getcwd(current_path, MAXPATHLEN)))
		return (cd_error(8, ""));
	if (!(pwd = get_env_ptr(env_lst, "PWD")))
		store_env_var(get_struct(0), ft_strdup("OLDPWD"), ft_strdup(""));
	else
		store_env_var(get_struct(0), ft_strdup("OLDPWD"), ft_strdup(pwd->val));
	store_env_var(get_struct(0), ft_strdup("PWD"), current_path);
	return (0);
}
