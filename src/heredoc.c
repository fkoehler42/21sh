/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 14:46:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/09/12 22:19:47 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	create_tmp_file(void)
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
	return (fd);
}

int		handle_heredoc(char *delimiter)
{
	int	fd;

	fd = create_tmp_file();

}
