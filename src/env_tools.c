/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 12:20:59 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 08:20:46 by fkoehler         ###   ########.fr       */
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

int		check_env_var(char *env_var, char *cmd)
{
	int		i;

	i = 0;
	if (!env_var[i] || env_var[i] == '=')
	{
		env_var_error(1, cmd, env_var);
		return (-1);
	}
	while (env_var[i] && env_var[i] != '=')
	{
		if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
		{
			env_var_error(1, cmd, env_var);
			return (-1);
		}
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
	t_shell	*shell;

	current_path = NULL;
	shell = get_struct(0);
	if (!(current_path = getcwd(current_path, MAXPATHLEN)))
		return (cd_error(8, ""));
	if (!(pwd = get_env_ptr(env_lst, "PWD")))
		store_env_var(&(shell->env_lst), ft_strdup("OLDPWD"), ft_strdup(""));
	else
		store_env_var(&(shell->env_lst), ft_strdup("OLDPWD"), ft_strdup(pwd->val));
	store_env_var(&(shell->env_lst), ft_strdup("PWD"), current_path);
	return (0);
}

int		del_env_var(t_env **env_lst, char *var)
{
	t_env	*tmp1;
	t_env	*tmp2;

	if (!(tmp1 = *env_lst))
	{
		free(var);
		return (-1);
	}
	if (ft_strcmp(tmp1->var, var) == 0)
	{
		*env_lst = tmp1->next;
		free_env_var(tmp1);
		free(var);
		return (0);
	}
	while (tmp1->next && ft_strcmp(tmp1->next->var, var) != 0)
		tmp1 = tmp1->next;
	if (tmp1->next)
	{
		tmp2 = tmp1->next->next;
		free_env_var(tmp1->next);
		tmp1->next = tmp2;
	}
	free(var);
	return (0);
}
