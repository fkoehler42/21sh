/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 14:46:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/12 22:14:30 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	handle_heredoc(char *delimiter)
{
	char	*file;
	char	*nb_file;
	int		i;
	int		fd;

	i = 1000;
	nb_file = ft_itoa(i);
	file = ft_strjoin("/tmp/t_heredoc", nb_file);
	while (access(file, F_OK) == 0)
	{
		free(file);
		free(nb_file);
		nb_file = ft_itoa(++i);
		file = ft_strjoin("/tmp/t_heredoc", nb_file);
	}
	if ((fd = open(file, O_RDWR | O_CREAT, 0644)) == -1)
		return (exec_error(8, file));
	free(file);
	free(nb_file);
}

static int	open_file(char *file, int redir_type)
{
	int		fd;

	fd = -1;
	if (redir_type == REDIR)
		fd = open(file, O_WRONLY | O_CREAT, 0644);
	else if (redir_type == DREDIR)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == BREDIR)
		fd = open(file, O_RDONLY);
	else if (redir->type == HEREDOC)
		handle_heredoc(file);
	return (fd);
}

static int	parse_redir(t_redir *redir, int **fd, int fd1, int i)
{
	int		fd2;
	char	*file;

	if (redir->s[++i] == '&' && redir->s[i + 1] == '-')
		(*fd)[fd1] = -1;
	else if (redir->s[i] == '&' && redir->type != DREDIR
			&& ft_isdigit(redir->s[i + 1]) && !redir->s[i + 1])
		(*fd)[fd1] = (redir->s[i] - 48);
	else
	{
		redir->s[i] == '&' ? i++ : (0);
		file = ft_strtrim(redir->s + i);
		if ((fd2 = open_file(file, redir->type)) == -1)
		{
			free(file);
			return (exec_error(8, file));
		}
		free(file);
		(*fd)[fd1] = fd2;
	}
	return (0);
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
		if (!ft_isdigit(redir->s[0]))
			fd1 = (redir->type == BREDIR) ? 0 : 1;
		else
			fd1 = ft_atoi(redir->s);
		i = (redir->type == REDIR || redir->type == DREDIR) ?
		ft_strrchr_index(redir->s, '>') : ft_strrchr_index(redir->s, '<');
		if (parse_redir(redir, &fd, fd1, i) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
