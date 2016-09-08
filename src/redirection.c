/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 14:46:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/08 22:41:37 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	output_redir(t_redir *redir, int **fd, int fd1, int i)
{
	int		fd2;
	char	*file;

	if (redir->s[++i] == '&' && redir->s[i + 1] == '-')
		(*fd)[fd1] = -1;
	else if (redir->s[i] == '&' && redir->type == REDIR
			&& ft_isdigit(redir->s[i + 1]) && !redir->s[i + 1])
		(*fd)[fd1] = (redir->s[i] - 48);
	else
	{
		redir->s[i] == '&' ? i++ : (0);
		file = ft_strtrim(redir->s + i);
		if (redir->type == REDIR &&
			((fd2 = open(file, O_WRONLY | O_CREAT, 0644)) == -1))
			return (exec_error(8, file));
		else if (redir->type == DREDIR && ((fd2 = open(file,
				O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1))
			return (exec_error(8, file));
		(*fd)[fd1] = fd2;
	}
	return (0);
}

static int	input_redir(t_redir *redir, int *fd)
{
}

int			handle_redir(t_btree *link, int *fd)
{
	int		i;
	int		fd1;
	t_redir	*redir;

	redir = link->redir;
	while (redir)
	{
		ft_putendl(redir->s);
		if ((redir->type == REDIR) || (redir->type == DREDIR))
		{
			if (!ft_isdigit(redir->s[0]))
				fd1 = 1;
			else if ((fd1 = ft_atoi(redir->s)) > 2)
				break;
			i = ft_strrchr_index(redir->s, '>');
			output_redir(redir, &fd, fd1, i);
		}
		else if (redir->type == BREDIR)
			input_redir();
		redir = redir->next;
	}
	return (0);
}
