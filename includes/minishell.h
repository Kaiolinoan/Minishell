/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:05:44 by klino-an          #+#    #+#             */
/*   Updated: 2026/02/24 23:20:43 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>

# define PWD_ERROR "pwd: error retrieving current directory:\
 getcwd: cannot access parent directories: "
# define CD_ERROR "cd: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory\n"
# define BASH_CD "bash: cd: "

extern int					g_sig;
// ENV STRUCTS
typedef struct s_extra		t_extra;
typedef struct s_map		t_map;
typedef struct s_envlist	t_envlist;

struct s_envlist
{
	char					*key;
	char					*value;
	bool					exported;
	t_envlist				*next;
	t_envlist				*prev;
};

typedef enum e_type
{
	OUTPUT = 60,
	INPUT = 62,
	OUTPUT_APPEND,
	HEREDOC,
}	t_type;

typedef struct s_redirect
{
	char				*filename;
	t_type				type;
	int					fd;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_exec
{
	int			in;
	int			out;
	int			temp_in;
	int			temp_out;
	int			fds[2];
	size_t		len;
	int			fake_status;
}	t_exec;

typedef struct s_commands
{
	pid_t				pid;
	char				**cmd;
	char				**args;
	char				*path;
	t_redirect			*infile;
	t_redirect			*outfile;
	struct s_commands	*next;
	struct s_commands	*prev;
}	t_command;

struct						s_map
{
	void		(*put)(t_map *t, char *k, char *v, bool exported);
	char		*(*get)(t_map *t, char *k);
	char		**(*to_string)(t_map *t);
	void		(*remove)(t_map *t, char *k);
	void		(*destroy)(t_map *t);
	int			(*print)(t_map *t, t_command *cmd);
	void		(*set_var_as_exported)(t_map *t, char *key);
};

struct						s_extra
{
	void		(*put)(t_extra *t, char *k, char *v, bool exported);
	char		*(*get)(t_extra *t, char *k);
	char		**(*to_string)(t_extra *t);
	void		(*remove)(t_extra *t, char *k);
	void		(*destroy)(t_extra *t);
	int			(*print)(t_extra *t, t_command *cmd);
	void		(*set_var_as_exported)(t_extra *t, char *key);
	t_envlist	*head;
	t_envlist	*tail;
	int			size;
};

// ###########################    EXECUTION    ###########################

// enviroment functions
t_envlist		*find(t_extra *t, char *key);
char			*__get(t_extra *t, char *k);
void			__remove(t_extra *t, char *k);
void			__put(t_extra *t, char *k, char *v, bool exported);
void			__set_var_as_exported(t_extra *t, char *key);
void			__destroy(t_extra *t);
int				__print(t_extra *t, t_command *cmd);
char			**__to_string(t_extra *t);

// env list
t_map			*new_map(void);
t_envlist		*new_node(char *k, char *v, bool exported);
t_command		*new_command(char **args);
t_redirect		*new_redirect(char *filename, char type);
t_exec			*new_exec(void);

// env create
t_map			*create_env(char **enviroment);
char			**ft_split_env(char *env);

//env path
char			*get_path(t_map *env, char **commands);

//built-ins
int				is_built_in(t_map *env, t_command *commands, t_exec *exec);
int				built_in_cd(char **args, t_map *env);
int				built_in_echo(t_command *commands);
int				built_in_export(t_command *commands, t_map *env);
int				built_in_pwd(t_map *env);
int				built_in_unset(t_command *commands, t_map *env);
int				built_in_exit(t_command *commands, t_map *env, t_exec *exec);

//start, redir and pipes 
void			exec_all(t_command*cmd, t_map *env, t_exec *exec);
void			handle_command(t_map *env, t_command *cmd, t_exec *exec);
int				check_redir(t_redirect *input, t_redirect *output,\
				int *in, int *out);
void			init_exec(t_exec *exec, t_command *cmd);
void			print_inside_redir(t_redirect *ptr); //apagar aqui

//heredoc
char			*clean_limiter(t_redirect *redir, bool *expand_vars);
char			*expand_here_doc(char *line, t_map *env);
void			heredoc_write_line(int fd, char *line,\
				bool expand_vars, t_map *env);
bool			heredoc_loop(int fd, char *limiter,
					bool expand_vars, t_map *env);
bool			check_here_doc(t_command *cmd, t_map *env, t_exec *exec);

//close
void			close_fds(t_exec *exec, t_command *cmd, bool is_parent);
void			ft_close(int *fd);
int				change_fd(int old, int new);

//signals
void			signals_init(void);
void			child_signal(void);
void			heredoc_sigint(int sig);
void			sigint_handler(int signal);
void			handle_heredoc_signals(void);

// ##############################    PARSING    ##############################
// parse cmdlist
int				parse_redirection(t_command *head);

// parse expansion
char			*remove_quotes(char *str);
char			*expand_word(char *result, t_map *env, char quote, int i);
char			*expand_variable(char *str, int i, t_map *env,\
				char *quote_state);
char			*expand(char *str, t_map *env);
int				expand_and_shi(t_command *head, t_map *env);
char			**split_on_marker(char *str);
int				count_expanded_args(char **args, t_map *env, int i, int j);
char			**fill_expanded_args(char **args, char **new_args,\
				t_map *env, int i);
char			**expand_with_splitting(char **args, t_map *env);

// parse input
char			*parse_input(char *str);

// parse main
t_command		*parse_main(char *input, t_map *env, t_exec *exec);

// parse redir syntax error
int				check_redir_error(t_command *current, int i, char redir_type);

// parse pipe syntax error
int				check_pipe_syntax(char *input);

//parse redirection
int				handle_redirection(t_command *cmdnode, int i, char redir);

// parse utils
bool			space_only(char *str);
char			identify_quote(char flag, char c);
void			print_nodes_after_input(t_command *head);
bool			var_start(char c);
bool			var_char(char c);

// ################################    UTILS    ################################
bool			space_only(char *str);
void			clear_matriz(char **matriz);
size_t			list_len_extra(t_extra *env);
size_t			list_len_command(t_command *commands);
int				ft_strcmp(char *s1, char *s2);
void			sort_str(char **matriz);
size_t			ft_array_len(char **arr);
long long		ft_atoll(const char *str);
void			free_grid(char **grid);
void			list_clear_redir(t_redirect *head);
void			ft_exit(t_map *env, t_command *cmd, t_exec *exec, int nb);
void			free_all(t_command *commands, t_exec *exec);
void			clear_exec(t_exec *exec);
void			clear_matriz2(char **matriz);
char			*process_cd_path(char *arg, t_map *env);
void			put_exit_code_in_env(t_map *env, int status);

#endif