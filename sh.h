/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:07:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/07/11 14:00:40 by fkoehler         ###   ########.fr       */
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

#define debug ft_printf("file : %s, line : %d", __FILE__, __LINE__);

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

typedef	struct			s_hist
{
	size_t				input_len;
	struct s_input		*input;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

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
	size_t				input_len;
	size_t				buf_len;
	size_t				p_len;
	t_env				*env_lst;
	t_hist				*hist;
	t_input				*input;
	t_input				*buffer;
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
void					print_input(t_shell *shell, t_input *curs_pos,
						size_t p_len);

void					store_environ(t_shell *shell, char **environ);
int						store_env_var(t_shell *shell, char *var, char *val);
t_env					*get_env_ptr(t_env *env_lst, char *var);
int						check_env_var(char *var);

char					*get_prompt(void);
int						put_prompt(char *prompt, int fd);

void					read_input(t_shell *shell);
void					parse_input(t_shell *shell, char *buf,
						size_t buf_len, size_t p_len);
void					store_input(t_shell *shell, char c);
void					delete_input(t_shell *shell, t_input *input, int back);
void					free_input_list(t_input **input, size_t *nb_elem);

void					parse_keys1(t_shell *shell, char *buf);
void					parse_keys2(t_shell *shell, char *buf);
void					parse_keys3(t_shell *shell, char *buf, size_t buf_len);

int						backspace(t_shell *shell);
int						del(t_shell *shell);

int						move_left(t_shell *shell);
int						move_left_word(t_shell *shell);
int						move_right(t_shell *shell);
int						move_right_word(t_shell *shell);
int						move_line_start(t_shell *shell);
int						move_line_end(t_shell *shell);
int						move_line_up(t_shell *shell);
int						move_line_down(t_shell *shell);

int						cut_eol(t_shell *shell);
int						cut_all(t_shell *shell);
int						copy_eol(t_shell *shell);
int						copy_all(t_shell *shell);
void					store_buffer(t_input **buf, char c);
int						paste_buffer(t_shell *shell);

int						history_prev(t_shell *shell);
int						history_next(t_shell *shell);
void					store_hist(t_shell *shell);

void					replace_cursor(t_shell *shell, int print, int back);
size_t					get_cursor_x_pos(t_input *input,
						t_input *pos, size_t p_len);

int						input_lst_cmp(t_input *lst1, t_input *lst2,
						size_t len1, size_t len2);

#endif
