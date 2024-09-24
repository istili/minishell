/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:25:27 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/24 16:09:05 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <sys/ioctl.h>

# define MALLOC "Error allocating memory\n"
# define OPEN "Error with open\n"
# define FORK "Error with fork\n"
# define PIPE "Error with pipe\n"
# define DUP2 "Error with dup2\n"
# define EXC "Error with execve\n"
# define PATH "Error path not found\n"
# define ARGS "Error invalide args\n"

typedef enum e_token_type
{
	none,
	ARG,
	DELIMITER,
	file,
	COMMAND,
	CHAR,
	Pipe,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	CHARACTER,
	DOUBLE_QUOTES,
	SINGLE_QUOTES
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
	int				x;
	int				j;
	int				len;
	int				flag;
	int				exp;
	int				quotes;
	char			*content;
	char			**data;
}	t_token;

typedef struct s_cmds
{
	t_token_type	type;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	int				j;
	int				fd;
	int				fd_h;
	int				fd_in;
	int				fd_out;
	int				herdoc;
	int				herdoc_flag;
	int				red_type;
	int				exp;
	int				quotes;
	char			**data;
}	t_cmds;

typedef struct s_values
{
	int		i;
	int		len;
	char	*value;
	char	*e_status;
}	t_values;

typedef struct s_herdoc
{
	int		i;
	int		j;
	int		x;
	int		len;
	int		size;
	char	*env;
	char	*data;
}	t_herdoc;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prv;
	void			*data;
}	t_node;

typedef struct s_exc
{
	int	in;
	int	out;
	int	zero;
	int	one;
}	t_exc;
typedef struct s_link
{
	t_node			*head;
	t_node			*tail;
	t_token			*tmp;
	struct termios	*term;
	int				zero;
	int				one;
	int				size;
	int				env_indx;
	int				pipe_indx;
	int				builtin_indx;
	int				fd[2];
	int				j;
	int				len;
	int				pipe;
	char			*pwd;
	char			*save;
}	t_link;

typedef struct s_env
{
	void	*key;
	void	*val;
}	t_env;

typedef struct s_gab
{
	struct s_gab	*next;
	void			*ptr;
}	t_gab;

typedef struct s_list
{
	t_gab	*head;
}	t_list;

int				is_digit(int c);
int				alpha(char c);
int				check_before(int start, char *line);
int				heredoc(t_cmds	*command, t_link *envp);
char			*ft_strchr(const char *s, int c);
void			ft_putstr_fd(char *s, int fd);
char			*check_for_file(char *str);
void			ft_flag(t_token **last, char *line, int i);

t_token_type	ft_error(void);
int				ft_strncmp(char *s1, char *s2, int n);
t_token_type	token_content_type(t_token *token);
int				check_for_pipe(t_token	*token);
int				enumeration(t_token	*var);
bool			ft_si(t_token *token);
bool			ft_red(t_token *token);
int				ft_len(t_token	*token);
t_token			*ft_new_list(t_token *token);
void			check_for_cmd_red_args(t_token	**token);
void			convert_to_new_list(t_token	*token, t_cmds	**cmnd);

int				ft_open_files(t_cmds	*command);
int				ft_len_args(char **str);
int				ft_strcmp(const	char	*s1, const	char	*s2);
char			*ft_strjoin(char const *s1, char const *s2);
char			*heredoc_expander(char *line, t_link *envp);

int				convert_it(char *line, t_token **head_ref, t_link *envp);
t_token			*ft_tokenizer(char *line, t_link *envp);
int				is_quote(int c);
bool			is_separator(int c);
bool			is_space(int c);
bool			is_character(int c);
t_token			*lst_new(t_link *envp, int len);
int				ft_token(t_token **token, char *line, t_link *envp, int i);

void			to_next_node(t_token **token, t_token *data);
t_token			*ft_lstlast(t_token *data);
char			*ft_strdup(const char *s);
void			*ft_realloc(void *ptr, int new_size, int i);
char			*ft_replace(char *line, int start, int end, t_link *envp);

int				s_quote(t_token **token, char *line, int i, t_link *envp);
int				d_quote(t_token **token, char *line, int i, t_link *envp);
int				after_d_q(t_token **token, char *line, int i, t_link *envp);
int				after_s_q(t_token **token, char *line, int i, t_link *envp);
int				ft_quotes(t_token **token, char *line, t_link *envp, int i);

int				ft_check(t_token **last);
int				characters(t_token **token, char *line, int i, t_link *envp);
int				after_char(t_token **token, char *line, int i, t_link *envp);

int				spaces(t_token **token, char *line, int i, t_link *envp);
int				after_space(t_token **token, char *line, int i, t_link *envp);

int				separator(t_token **token, char *line, int i, t_link *envp);
int				after_separ(t_token **token, char *line, int i, t_link *envp);
void			final_enum(t_token	*token, t_token **commands);

void			f_echo(char **av);
void			f_pwd(t_link *linked);
int				f_unset(t_link *linkd, char **av);
int				f_cd(char **path, t_link *envp);
void			f_exit(t_link *envp, char **av);
void			f_export(t_link *linkedlist, char **av, int exp);
void			f_env(t_link *linkedlist);

char			**ft_split(char *str, char c);
int				ft_strlen(const char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strdup_del(void	*dir);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_atoi(const char *str);
int				is_number(char *s);
char			*ft_itoa(int n);

char			*find_home_path(t_link *envp);
int				exit_status(int new_status, int flag);
void			error(char *s, t_cmds *cmd);
int				check_arg(char *av);
char			*find_key(char *s, int *flag);
void			updatenv(t_link *link, char *key, char *val);
t_link			*env_linkedlist(char **env);
void			add_node(t_link *node, void *env);
t_link			*make_my_own_env(void);
void			handle_siginit(int sig);
void			*ft_malloc_gab(size_t size, int flag);
int				is_alpha_(char c);
int				is_alphnum(char c);
int				execution(t_link *envp, t_cmds *cmd);
int				fill_cmd(t_cmds *cmds, char **env);
int				count_cmds(t_cmds *cmds);
void			reset_terminal(t_link *envp);
void			setexit(int status, t_link *envp);
int				find_red_in(t_cmds *cmds);
int				find_red_out(t_cmds *cmds);
char			**link_to_arr(t_link *link);
void			builtins(t_cmds *commands, t_link *envp);
int				is_not_builtin(t_cmds *cmd);
int				no_red(t_cmds *cmds);
int				is_it_one_cmd(t_cmds *cmds);
int				count_pipes(t_cmds *cmds);
int				find_herdoc(t_cmds *cmds);
void			handle_herdoc(int signumber);
int				look_for_herdoc(t_cmds *cmd);
int				herdoc_c_signal(int state, int flag);

void			main_execution(t_cmds *commands, t_link *envp, int flag);
char			*find_val(t_link *envp, char *key);
void			init_env(char **env, t_link **envp);
void			infinite_lop(t_link *envp, t_exc fd);
t_cmds			*read_line(t_link *envp);
int				heredoc_is_last(t_cmds *cmd);
char			*find_value(char *s);

t_token			*n_node(t_token *current, t_token *token);
int				convert_it(char *line, t_token **head_ref, t_link *envp);
int				char_expdr(t_token **last, char *line, int i, t_link *envp);
int				ft_nrml_exp(char *data, t_link *envp, t_token **last);
void			expd_space(char *data, t_token **last, t_link *envp);
int				ft_writ(char c);
int				rideracting(t_cmds *cmd);
void			executing(t_cmds *cmd, char **env, t_link *envp);
void			close_fd(t_cmds *cmd);
int				full_space(char *s);
void			one_cmd_child(t_cmds *cmd, t_link *envp, char **env \
	, int *status);

#endif