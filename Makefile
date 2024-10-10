# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clmanouk <clmanouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 13:46:16 by nde-chab          #+#    #+#              #
#    Updated: 2024/10/10 15:55:02 by clmanouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft_all/libft_printf_gnl.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I includes
SRCS_DIR = srcs/
OBJS_DIR = obj/

# Regroupement des sources par catégorie
BUILTIN_SRCS = ft_env.c ft_pwd.c ft_echo.c ft_cd.c ft_exit.c find_exec_builting.c ft_export.c ft_unset.c
EXEC_SRCS = here_doc.c exec.c redirection.c execve_utils.c
PARSING_SRCS = token_create.c token_utils.c error_parsing.c split_input.c lexer.c quote_remove.c special_case.c handle_var_env.c handle_var_env_2.c
STRUCT_SRCS = exec_utils.c init_struct.c list_utils.c init_env.c
UTILS_SRCS = free_func.c free_struct.c get_env.c str_utils.c count_line.c
SIGNAL_SRCS = handle_signal.c
MAIN_SRCS = main.c

# Ajout des préfixes de répertoire
SRCS = $(addprefix $(SRCS_DIR)builting/, $(BUILTIN_SRCS)) \
       $(addprefix $(SRCS_DIR)exec/, $(EXEC_SRCS)) \
       $(addprefix $(SRCS_DIR)parsing/, $(PARSING_SRCS)) \
       $(addprefix $(SRCS_DIR)structs/, $(STRUCT_SRCS)) \
       $(addprefix $(SRCS_DIR)utils/, $(UTILS_SRCS)) \
       $(addprefix $(SRCS_DIR)signal/, $(SIGNAL_SRCS)) \
       $(addprefix $(SRCS_DIR)main/, $(MAIN_SRCS))

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

# Colors and styles
BLUE = \033[1;34m
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
BOLD = \033[1m
RESET = \033[0m

# Counter for progress bar
COUNTER = 0
TOTAL_FILES = $(words $(SRCS))
BAR_LENGTH = 40

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ -lreadline
	@echo "$(GREEN)Compilation terminée avec succès ! 🎉$(RESET)"
	@echo "\n$(RED)$$MINISHELL_LOGO$(RESET)"

# Règle modifiée pour la compilation des fichiers objets avec barre de progression
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
	@$(eval PERCENTAGE=$(shell echo $$(($(COUNTER) * 100 / $(TOTAL_FILES)))))
	@$(eval FILLED=$(shell echo $$(($(COUNTER) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@$(eval EMPTY=$(shell echo $$(($(BAR_LENGTH) - $(FILLED)))))
	@printf "\r$(BLUE)Compiling [%-*s%*s] %3d%% %s$(RESET)" $(BAR_LENGTH) "$$(printf '%0.s#' $$(seq 1 $(FILLED)))" $(EMPTY) " " $(PERCENTAGE) "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft_all

clean:
	@echo "$(YELLOW)Nettoyage des fichiers objets...$(RESET)"
	@$(MAKE) -C libft_all clean
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Nettoyage terminé.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Suppression de l'exécutable...$(RESET)"
	@$(MAKE) -C libft_all fclean
	@rm -f $(NAME)
	@echo "$(GREEN)Suppression complète effectuée.$(RESET)"

re: fclean all

# ASCII art logo for MINISHELL
define MINISHELL_LOGO

 ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    
▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    
▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    
▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    
▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   
       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░
                                                                      
endef
export MINISHELL_LOGO