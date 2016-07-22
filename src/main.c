/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:43:55 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 15:13:03 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

int		main(int ac, char **av, char **environ)
{
	t_shell		shell;

	(void)ac;
	(void)av;
	init_shell(&shell);
	init_term(&shell);
	store_environ(&shell, environ);
	read_input(&shell);
	return (0);
}
