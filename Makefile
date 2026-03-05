# **************************************************************************** #
#    Makefile — Minishell                                                      #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I include -I libft/includes
LDFLAGS		= -lreadline -L libft -lft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/signals.c \
	$(SRC_DIR)/signals_utils.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/lexer_utils.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/expander.c \
	$(SRC_DIR)/expander_utils.c \
	$(SRC_DIR)/executor.c \
	$(SRC_DIR)/executor_pipe.c \
	$(SRC_DIR)/executor_path.c \
	$(SRC_DIR)/executor_redir.c \
	$(SRC_DIR)/executor_heredoc.c \
	$(SRC_DIR)/executor_heredoc_utils.c \
	$(SRC_DIR)/executor_child.c \
	$(SRC_DIR)/builtins.c \
	$(SRC_DIR)/builtin_echo.c \
	$(SRC_DIR)/builtin_cd.c \
	$(SRC_DIR)/builtin_pwd.c \
	$(SRC_DIR)/builtin_export.c \
	$(SRC_DIR)/builtin_export_utils.c \
	$(SRC_DIR)/builtin_unset.c \
	$(SRC_DIR)/builtin_env.c \
	$(SRC_DIR)/builtin_exit.c \
	$(SRC_DIR)/builtin_history.c \
	$(SRC_DIR)/env.c \
	$(SRC_DIR)/env_set.c \
	$(SRC_DIR)/env_utils.c \
	$(SRC_DIR)/str_utils.c \
	$(SRC_DIR)/error.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN		= \033[32m
YELLOW		= \033[33m
CYAN		= \033[36m
RESET		= \033[0m
BOLD		= \033[1m
DIM			= \033[2m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(BOLD)$(GREEN)  Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "$(BOLD)$(GREEN)  ✓ $(NAME) ready!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/minishell.h
	@mkdir -p $(dir $@)
	@printf "$(DIM)  Compiling $(CYAN)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@printf "$(YELLOW)  Cleaned object files$(RESET)\n"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@printf "$(YELLOW)  Removed $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
