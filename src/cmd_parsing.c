/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/01 21:13:26 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	multi_lines_cmd(t_shell *shell)
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
			c == '\\' ? delete_input(&save, lst_rchr(save, '\\'), NULL, 0)
			: store_buffer(&save, '\n');
			read_multi_lines_input(shell, get_special_prompt(c));
			tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
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
}

int			parse_cmd(t_btree *link)
{
	int		i;
	char	**cmd_tab;

	i = 0;
	if ((strchr_redir(link)) == -1)
		return (-1);
	cmd_tab = strsplit_args(link->str);
	if (!cmd_tab[0])
	{
		free_tab(cmd_tab);
		return (-1);
	}
	while (cmd_tab[i])
	{
		ft_printf("\narg %d : %s\n", i + 1, cmd_tab[i]);
		cmd_tab[i] = interpret_cmd_arg(cmd_tab[i]);
		i++;
	}
	return (0);
}

int			handle_input(t_shell *shell)
{
	char	*cmd_str;

	move_line_end(shell);
	tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
	if (!shell->input)
		return (0);
	if (check_pipes(shell->input, 1) == -1)
		return (cmd_error(0, '|', NULL));
	multi_lines_cmd(shell);
	shell->hist = store_hist(shell);
	cmd_str = lst_to_str(shell->input);
	shell->cmd = store_cmd(cmd_str);
	free_tmp_inputs(shell);
	handle_btree(shell, shell->cmd);
	return (0);
}
