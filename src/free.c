/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:58:38 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/14 18:54:29 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_redirs(t_redir **redirs)
{
	t_redir	*tmp1;
	t_redir	*tmp2;

	if (!(tmp1 = *redirs))
		return ;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1->s);
		free(tmp1);
		tmp1 = tmp2;
	}
	*redirs = NULL;
}

void	free_input_list(t_input **input, size_t *nb_elem)
{
	t_input	*tmp1;
	t_input	*tmp2;

	if (!(tmp1 = *input))
		return ;
	if (tmp1->prev)
		tmp1->prev->next = NULL;
	else
		*input = NULL;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
		if (nb_elem)
			--(*nb_elem);
	}
}

void	free_tmp_inputs(t_shell *shell)
{
	if (shell->input)
		free_input_list(&(shell->input), &(shell->input_len));
	if (shell->buffer)
		free_input_list(&(shell->buffer), NULL);
	if (shell->input_buf)
	{
		free(shell->input_buf);
		shell->input_buf = NULL;
	}
	shell->curs_pos = NULL;
}

void	free_env_var(t_env *env_var)
{
	free(env_var->var);
	free(env_var->val);
	free(env_var);
}

void	free_env_lst(t_env **env_lst)
{
	t_env *tmp1;
	t_env *tmp2;

	if (!env_lst || !(*env_lst))
		return ;
	tmp1 = *env_lst;
	while (tmp1)
	{
		tmp2 = (tmp1)->next;
		free_env_var(tmp1);
		tmp1 = tmp2;
	}
	*env_lst = NULL;
}
