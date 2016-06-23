/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:55:56 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/23 20:10:16 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	init_struct(t_shell *shell)
{
	shell->pos_x = 0;
	shell->pos_y = 0;
	shell->col = 0;
	shell->env_lst = NULL;
	shell->input = NULL;
	shell->tree = NULL;
}

int		init_shell(t_shell *shell);
