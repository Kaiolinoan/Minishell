/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:05:44 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/29 19:15:54 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
#include <sys/wait.h>
# include <stdio.h>

// ENV STRUCTS
typedef struct s_envlist	t_envlist;

struct						s_envlist
{
	char					*key;
	char					*value;
	t_envlist				*next;
	t_envlist				*prev;
};

typedef struct s_map		t_map;

struct						s_map
{
	void					(*put)(t_map *t, char *k, char *v);
	char					*(*get)(t_map *t, char *k);
	void					(*remove)(t_map *t, char *k);
	void					(*destroy)(t_map *t);
	void					(*print)(t_map *t);
};

typedef struct s_extra		t_extra;

struct						s_extra
{
	void					(*put)(t_extra *t, char *k, char *v);
	char					*(*get)(t_extra *t, char *k);
	void					(*remove)(t_extra *t, char *k);
	void					(*destroy)(t_extra *t);
	void					(*print)(t_extra *t);
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
}t_command;



// enviroment functions
t_envlist					*find(t_extra *t, char *key);
char						*__get(t_extra *t, char *k);
void						__remove(t_extra *t, char *k);
void						__put(t_extra *t, char *k, char *v);
void						__destroy(t_extra *t);
void						__print(t_extra *t);


// env list
t_map						*new_map(void);
t_envlist					*new_node(char *k, char *v);
t_command					*new_command(char **command);
t_redirect					*new_redirect(char *filename, char type);


// env create
void						create_env(t_map *env, char **enviroment);

//env path
char						*get_path(t_map *env, char *str);

// utils
void						clear_matriz(char **matriz);



#endif
