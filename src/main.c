/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:43:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 13:53:17 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

int		main(int ac, char **av, char **environ)
{
	t_shell		shell;
	t_env		*tmp;

	(void)ac;
	(void)av;
	init_shell(&shell);
	init_term(&shell);
	store_environ(&shell, environ);
	tmp = shell.env_lst;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}
