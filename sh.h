/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:07:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/27 18:49:40 by fkoehler         ###   ########.fr       */
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
	size_t				col;
	size_t				line_len;
	t_env				*env_lst;
	t_input				*input;
	t_input				*curs_pos;
	t_tree				*tree;
	struct termios		termios;
	struct termios		term_save;
}						t_shell;

void					exit_error(int errnum);
int						env_error(int errnum, char *arg);

void					init_shell(t_shell *shell);
void					init_term(t_shell *shell);
t_shell					*get_struct(t_shell *struc);

int						putchar(int c);
void					print_input(t_shell *shell, t_input *curs_pos);

void					store_environ(t_shell *shell, char **environ);
int						store_env_var(t_shell *shell, char *var, char *val);
t_env					*get_env_ptr(t_env *env_lst, char *var);
int						check_env_var(char *var);

char					*get_prompt(void);
void					put_prompt(char *prompt, int fd);

void					read_input(t_shell *shell);
int						parse_input(t_shell *shell, char *buf, size_t len);

int						parse_keys1(t_shell *shell, char *buf);

int						move_left(t_shell *shell);
int						move_right(t_shell *shell);
int						line_start(t_shell *shell);
int						line_end(t_shell *shell);

#endif
