# ================================= NAME =================================== #

NAME = minishell

# =============================== DIRECTORIES =============================== #

SRCDIR		= srcs/
OBJDIR		= objs/
INCDIR		= includes/
LIBFTDIR	= Libft/

# ================================= FILES =================================== #

SRC_FILES	= main.c exc_env_functions.c exc_env_list.c exc_env_create.c \
			  exc_env_path.c utils.c
SRC			= $(addprefix $(SRCDIR), $(SRC_FILES))

# ================================ OBJECTS =================================== #

OBJS		= $(addprefix $(OBJDIR), $(SRC_FILES:.c=.o))

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
	@mkdir -p $(OBJDIR)
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

r:
	make re && clear && ./$(NAME)

v:
	make re && clear && valgrind --leak-check=full  --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)
# ------------------------------- Phony Targets ----------------------------- #
.PHONY: all clean fclean re