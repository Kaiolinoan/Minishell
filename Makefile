# ================================= NAME =================================== #

NAME = minishell

# =============================== DIRECTORIES =============================== #

SRCDIR		= srcs/
OBJDIR		= objs/
INCDIR		= includes/
LIBFTDIR	= Libft/
BUILTIN_DIR	= built-in/
UTILS_DIR	= utils/
EXC_DIR		= execution/
PARSE_DIR	= parsing/
ENV_DIR		= env/

# ================================= FILES =================================== #

SRC_UTILS	= utils.c utils_2.c
SRC_PARSE	= parse_input.c parse_main.c parse_utils.c
SRC_FILES	= main.c 
SRC_BUILTIN = exc_ft_cd.c exc_ft_export.c exc_ft_echo.c exc_ft_pwd.c \
			  exc_ft_unset.c exc_ft_exit.c 
SRC_ENV		= exc_env_functions.c  exc_env_functions_2.c exc_env_list.c  \
			  exc_env_create.c exc_env_path.c
SRC_EXC		= exc_start.c exc_close.c exc_pipes.c exc_redir.c exc_helpers.c exc_heredoc.c

SRC = $(addprefix $(SRCDIR), $(SRC_FILES)) \
      $(addprefix $(SRCDIR)$(ENV_DIR), $(SRC_ENV)) \
      $(addprefix $(SRCDIR)$(EXC_DIR), $(SRC_EXC)) \
      $(addprefix $(SRCDIR)$(UTILS_DIR), $(SRC_UTILS)) \
      $(addprefix $(SRCDIR)$(PARSE_DIR), $(SRC_PARSE)) \
      $(addprefix $(SRCDIR)$(BUILTIN_DIR), $(SRC_BUILTIN)) 

# ================================ OBJECTS =================================== #

OBJS = $(addprefix $(OBJDIR), $(SRC:$(SRCDIR)%.c=%.o))

# ================================ LIBRARY =================================== #

LIBFT		= $(LIBFTDIR)libft.a

# =============================== COMPILER ================================== #

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3
INCLUDES		= -I$(INCDIR)
RM				= rm -f
MAKE			= make
READLINE_LIBS	= -lreadline -lncurses

# ================================= COLORS =================================== #

DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
LIGHT_BLUE	= \033[38;2;85;205;252m
PINK		= \033[38;2;247;168;184m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# ================================= RULES ==================================== #

all: $(NAME)

# --------------------------------- Targets ---------------------------------- #
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Linking $(NAME)...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(DEF_COLOR)"

# ----------------------------- Object Files -------------------------------- #
$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I$(LIBFTDIR) -c $< -o $@

# ------------------------------- Library ----------------------------------- #
$(LIBFT):
	@echo "$(MAGENTA)Building libft...$(DEF_COLOR)"
	@$(MAKE) -s -C $(LIBFTDIR)
	@echo "$(GREEN)✓ libft built successfully!$(DEF_COLOR)"

# ------------------------------ Clean Rules -------------------------------- #
clean:
	@echo "$(RED)Cleaning object files...$(DEF_COLOR)"
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -s -C $(LIBFTDIR)
	@echo "$(GREEN)✓ Object files cleaned!$(DEF_COLOR)"

fclean: clean
	@echo "$(RED)Cleaning executables...$(DEF_COLOR)"
	@$(RM) $(NAME)
	@$(MAKE) fclean -s -C $(LIBFTDIR)
	@echo "$(GREEN)✓ All files cleaned!$(DEF_COLOR)"

re: fclean all

reclear: 
	@make re && clear

r: reclear
	@./$(NAME) || true

v: reclear
	valgrind --leak-check=full  --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)
# ------------------------------- Phony Targets ----------------------------- #
.PHONY: all clean fclean re