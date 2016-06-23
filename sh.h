/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:07:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/23 20:10:20 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <libft.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <term.h>
# include <sys/ioctl.h>

typedef struct			s_env
{
	char				*var;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_input
{
	char				c;
	struct s_input		*prev;
	struct s_input		*next;
}						t_input;

typedef struct			s_tree
{
	int					type;
	char				*cmd;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct			s_shell
{
	size_t				pos_x;
	size_t				pos_y;
	size_t				col;
	t_env				*env_lst;
	t_input				*input;
	t_tree				*cmd_tree;
}						t_shell;

void					init_struct(t_shell *shell);

#endif
