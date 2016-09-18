/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/18 14:35:51 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		**parse_cmd(t_btree *link)
{
	int		i;
	char	**cmd_tab;

	i = 0;
	if ((strchr_redir(link)) == -1)
		return (NULL);
	link->str = remove_cmd_redir(link->str, link->redir);
	cmd_tab = strsplit_args(link->str);
	if (!cmd_tab[0])
	{
		free_tab(cmd_tab);
		return (NULL);
	}
	while (cmd_tab[i])
	{
		cmd_tab[i] = interpret_cmd_arg(cmd_tab[i]);
		i++;
	}
	return (cmd_tab);
}

int			handle_input(t_shell *shell)
{
	char	c;
	char	*cmd_str;

	c = 0;
	move_line_end(shell);
	tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
	if (!shell->input)
		return (0);
	if ((c = valid_input(shell->input, c)) > 0)
	{
		c == '\\' ? delete_input(&(shell->input), shell->curs_pos, shell, 1)
		: store_input(shell, '\n');
		shell->curs_pos->EOL = 1;
		return ((int)c);
	}
	if (check_pipes(shell->input, 1) == -1)
		return (cmd_error(0, '|', NULL));
	shell->hist = store_hist(shell);
	cmd_str = lst_to_str(shell->input);
	shell->tree = store_cmd(cmd_str);
	free_tmp_inputs(shell);
	restore_term(shell);
	handle_btree(shell, shell->tree);
	reload_term(shell);
	return (0);
}
