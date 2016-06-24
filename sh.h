/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:07:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/24 14:04:59 by fkoehler         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/ioctl.h>

typedef struct			s_env
{
	char				*var;
	char				*val;
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
	int					fd;
	size_t				pos_x;
	size_t				pos_y;
	size_t				col;
	t_env				*env_lst;
	t_input				*input;
	t_tree				*tree;
	struct termios		termios;
	struct termios		term_save;
}						t_shell;

void					exit_error(int errnum);
int						env_error(int errnum, char *arg);

void					init_shell(t_shell *shell);
void					init_term(t_shell *shell);

void					store_environ(t_shell *shell, char **environ);
int						store_env_var(t_shell *shell, char *var, char *val);
t_env					*get_env_ptr(t_env *env_lst, char *var);
int						check_env_var(char *var);

#endif
