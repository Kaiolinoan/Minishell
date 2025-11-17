/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:05:44 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/15 13:55:25 by klino-an         ###   ########.fr       */
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
	void					(*print)(t_map *t);
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
	void					(*print)(t_extra *t);
	void					(*set_var_as_exported)(t_extra *t, char *key);
	t_envlist				*head;
	t_envlist				*tail;
	int						size;
};

typedef struct s_redirect
{
	char type;
	char *filename;
	struct s_redirect *next;
}	t_redirect;

typedef struct s_commands
{
	char 				**command;
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
void						__print(t_extra *t);
char 						**__to_string(t_extra *t);


// env list
t_map						*new_map(void);
t_envlist					*new_node(char *k, char *v, bool exported);
t_command					*new_command(char **command);
t_redirect					*new_redirect(char *filename, char type);
t_var						*new_var(char *k, char *v, bool exported, bool commands);

// env create
void						create_env(t_map *env, char **enviroment);
char						**ft_split_env(char *env);


//env path
char						*get_path(t_map *env, char *str);

//variables
// void					    create_variable(t_map *env, t_command *commands, t_var *var);

//built-ins
int							built_in_cd(char **args, t_map *env);
void						built_in_echo(t_command *commands);
void    					built_in_export(t_command *commands, t_map *env);
void						built_in_pwd(t_map *env);
void						built_in_unset(t_command *commands, t_map *env);
void    					built_in_exit(t_command *commands, t_map *env, char *str);


//start
bool						is_built_in(char *str, t_map *env, t_command *commands);
void						process_input(char *str, t_map *env, char **environment);

//#################################    PARSING    #################################################
// parse input
char						*parse_input(char *str);


// utils
bool						space_only(char *str);
void						clear_matriz(char **matriz);
size_t						list_len(t_extra *env);
int							ft_strcmp(char *s1, char *s2);
void						sort_str(char **matriz);
void						print_error(char *str, char *filename);
size_t						ft_array_len(char **arr);


#endif
