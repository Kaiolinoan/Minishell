/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:05:44 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/27 01:40:52 by klino-an         ###   ########.fr       */
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


# define CD_ERROR "bash: cd: "

extern int g_exit_code;

// ENV STRUCTS
typedef struct s_envlist	t_envlist;

struct						s_envlist
{
	char					*key;
	char					*value;
	bool					exported;
	t_envlist				*next;
	t_envlist				*prev;
};

typedef struct s_variables
{
	char				*key;
	char				*value;
	bool				is_exported;
	bool				commands;
	struct s_variables	*next;
}	t_var;

typedef struct s_map		t_map;

struct						s_map
{
	void					(*put)(t_map *t, char *k, char *v, bool exported);
	char					*(*get)(t_map *t, char *k);
	char					**(*to_string)(t_map *t);
	void					(*remove)(t_map *t, char *k);
	void					(*destroy)(t_map *t);
	int						(*print)(t_map *t);
	void					(*set_var_as_exported)(t_map *t, char *key);
};

typedef struct s_extra		t_extra;

struct						s_extra
{
	void					(*put)(t_extra *t, char *k, char *v, bool exported);
	char					*(*get)(t_extra *t, char *k);
	char					**(*to_string)(t_extra *t);
	void					(*remove)(t_extra *t, char *k);
	void					(*destroy)(t_extra *t);
	int						(*print)(t_extra *t);
	void					(*set_var_as_exported)(t_extra *t, char *key);
	t_envlist				*head;
	t_envlist				*tail;
	int						size;
};

typedef enum e_type
{
    NONE = 0,
    OUTPUT = 60,
    INPUT = 62,
    OUTPUT_APPEND,
    HEREDOC,
}   t_type;

typedef struct s_redirect
{
	char	*filename;
	t_type	type;
	int		fd;
	struct s_redirect *next;
}	t_redirect;

typedef struct s_commands
{
	pid_t				pid;
	char 				**args;
	char				*path;
	t_redirect 			*infile;
	t_redirect 			*outfile;
	struct s_commands 	*next;
}	t_command;

//#################################    EXECUTION    #################################################

// enviroment functions
t_envlist					*find(t_extra *t, char *key);
char						*__get(t_extra *t, char *k);
void						__remove(t_extra *t, char *k);
void						__put(t_extra *t, char *k, char *v, bool exported);
void						__set_var_as_exported(t_extra *t, char *key);
void						__destroy(t_extra *t);
int							__print(t_extra *t);
char 						**__to_string(t_extra *t);


// env list
t_map						*new_map(void);
t_envlist					*new_node(char *k, char *v, bool exported);
t_command					*new_command(char **args);
t_redirect					*new_redirect(char *filename, char type);
t_var						*new_var(char *k, char *v, bool exported, bool commands);

// env create
void						create_env(t_map *env, char **enviroment);
char						**ft_split_env(char *env);


//env path
char						*get_path(t_map *env, char **commands);

//variables
// void					    create_variable(t_map *env, t_command *commands, t_var *var);

//built-ins
int							built_in_cd(char **args, t_map *env);
int							built_in_echo(t_command *commands);
int	    					built_in_export(t_command *commands, t_map *env);
int							built_in_pwd(t_map *env);
int							built_in_unset(t_command *commands, t_map *env);
int	    					built_in_exit(t_command *commands, t_map *env);


//start, close, redir and pipes 
void						exec_all (t_command*cmd, t_map *env);
void 						ft_close(int *fd);
int 						change_fd(int old, int new);
void						check_redir(t_redirect *input, t_redirect *output, int *in, int *out);
int							exec_here_doc(t_command *cmd, t_map *env);

//helpers
void 						wait_all(t_command *cmd);
bool						check_here_doc(t_command *cmd, t_map *env);

//#################################    PARSING    #################################################
// parse input
char						*parse_input(char *str);

// parse main
t_command					*parse_main(char *input, t_command  *head, t_map *env);

// parse utils
bool						space_only(char *str);

//#################################    UTILS    #################################################
bool						space_only(char *str);
void						clear_matriz(char **matriz);
size_t						list_len_extra(t_extra *env);
size_t						list_len_command(t_command *commands);
int							ft_strcmp(char *s1, char *s2);
void						sort_str(char **matriz);
void						print_error(char *str, char *filename);
size_t						ft_array_len(char **arr);
long long					ft_atoll(const char *str);
void						free_grid(char **grid);
void						list_clear_redir(t_redirect *head);
void						ft_exit(t_map *env, t_command *cmd, int nb);
void						free_all(t_command *commands);

#endif