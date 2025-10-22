#ifndef MINISHELL_H
#define MINISHELL_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


// ENV STRUCTS
typedef struct s_envlist t_envlist;

struct s_envlist
{
    char    *key;
    char    *value;
    t_envlist  *next;
    t_envlist  *prev;
};

typedef struct s_map t_map;

struct s_map
{
    void (*put)(t_map *t, char * k,char * v);
    char *(*get)(t_map *t, char *k);
    void (*remove)(t_map *t, char * k);
};

typedef struct s_extra t_extra;

struct s_extra
{
    void (*put)(t_extra *t, char * k,char * v);
    char *(*get)(t_extra *t, char *k);
    void (*remove)(t_extra *t, char * k);
    t_envlist *head;
    t_envlist *tail;
    int size;
};


//Lists


#endif
