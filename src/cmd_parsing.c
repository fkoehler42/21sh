/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/08/19 12:16:03 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	epur_cmd(t_shell *shell)
{
	t_input	*tmp1;
	t_input	*tmp2;

	if (!(tmp1 = shell->input))
		return (-1);
	while (tmp1 && (tmp1->c == ' ' || tmp1->c == ';'))
	{
		delete_input(shell, tmp1, 1);
		tmp1 = shell->input;
	}
	if (!tmp1)
		return (-1);
	tmp1 = shell->curs_pos;
	while (tmp1 && (tmp1->c == ' ' || tmp1->c == ';'))
	{
		tmp2 = tmp1->prev;
		delete_input(shell, tmp1, 1);
		tmp1 = tmp2;
	}
	if (!tmp1)
		return (-1);
	return (0);
}

static int	multi_lines_cmd(t_shell *shell)
{
	static t_input	*save = NULL;
	char			c;

	c = 0;
	if ((c = valid_input(shell->input, c)) > 0)
	{
		lst_cpy(shell->input, &save);
		while ((c = valid_input(save, c)) > 0)
		{
			free_tmp_inputs(shell);
			store_buffer(&save, '\n');
			read_multi_lines_input(shell, get_special_prompt(c));
			tputs(tgetstr("do", NULL), shell->fd, &putchar);
			lst_cpy(shell->input, &save);
		}
	}
	if (save)
	{
		free_tmp_inputs(shell);
		shell->input = save;
		shell->input_len = lst_len(save);
		save = NULL;
	}
	return (0);
}

static int	parse_cmd(char *str_cmd, int parent)
{
	int		i;
	char	**cmd;
	t_shell	*shell;

	i = 0;
	shell = get_struct(0);
	if (!(cmd = strsplit_args(str_cmd)) && parent == PIP)
		return (cmd_error(0));
	while (cmd[i])
	{
		if ((is_str_quoted(cmd[i]) != 1) && (ft_strchr(cmd[i], '$') != NULL))
			cmd[i] = str_replace_var(cmd[i]);
		i++;
	}
	if (builtins_cmd(cmd, &(shell->env_lst)) == -1)
		return (0);
	return (0);
}

static void	browse_btree(t_btree *cmd, int type)
{
	if (!cmd)
		return ;
	if (cmd->type == SEM)
	{
		browse_btree(cmd->left, SEM);
		browse_btree(cmd->right, SEM);
	}
	else if (cmd->type == PIP)
	{
		browse_btree(cmd->left, PIP);
		browse_btree(cmd->right, PIP);
	}
	else
		parse_cmd(cmd->cmd, type);
}

int			handle_input(t_shell *shell)
{
	char	*cmd_str;

	move_line_end(shell);
	tputs(tgetstr("do", NULL), shell->fd, &putchar);
	if (epur_cmd(shell) == -1)
		return (-1);
	if (check_pipes(shell->input, 1) == -1)
		return (cmd_error(0));
	multi_lines_cmd(shell);
	shell->hist = store_hist(shell);
	cmd_str = lst_to_str(shell->input);
	shell->cmd = store_cmd(cmd_str);
	free_tmp_inputs(shell);
	browse_btree(shell->cmd, shell->cmd->type);
	return (0);
}
