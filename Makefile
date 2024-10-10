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
MAGENTA = \033[1;35m
CYAN = \033[1;36m
BOLD = \033[1m
RESET = \033[0m

# Counter for progress bar
COUNTER = 0
TOTAL_FILES = $(words $(SRCS))
BAR_LENGTH = 50

# Animation frames
FRAMES = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

.PHONY: all clean fclean re

all: pre_compile $(NAME)

pre_compile:
	@echo "$(MAGENTA)🚀 Launching Minishell Compilation Sequence 🚀$(RESET)"
	@for i in 3 2 1; do \
		printf "\r$(YELLOW)Compiling in $$i...$(RESET)"; \
		sleep 1; \
	done
	@printf "\n$(CYAN)Initiating Awesome Compilation Process!$(RESET)\n"
	@sleep 0.5

$(NAME): $(OBJS) $(LIBFT)
	@printf "\n$(GREEN)✨ Linking objects with magic sprinkles...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ $^ -lreadline
	@echo "$(GREEN)🎉 Compilation completed successfully! 🎊$(RESET)"
	@sleep 0.5
	@echo "\n$(RED)$$MINISHELL_LOGO$(RESET)"
	@sleep 0.5
	@echo "$(YELLOW)🌟 Minishell is ready to rock! 🌟$(RESET)"

# Règle modifiée pour la compilation des fichiers objets avec barre de progression animée
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
	@$(eval PERCENTAGE=$(shell echo $$(($(COUNTER) * 100 / $(TOTAL_FILES)))))
	@$(eval FILLED=$(shell echo $$(($(COUNTER) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@$(eval FRAME=$(word $(shell echo $$(($(COUNTER) % 10 + 1))), $(FRAMES)))
	@printf "\r\033[K$(BLUE)$(FRAME) Progress: [%-*s] %3d%%$(RESET)" $(BAR_LENGTH) "$$(printf '%0.s█' $$(seq 1 $(FILLED)))" $(PERCENTAGE)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 2>/dev/null
	@sleep 0.05

$(LIBFT):
	@$(MAKE) -C libft_all >/dev/null

clean:
	@echo "$(YELLOW)🧹 Cleaning up object files...$(RESET)"
	@$(MAKE) -C libft_all clean >/dev/null
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)✨ Cleanup complete! Your project is now squeaky clean.$(RESET)"

fclean: clean
	@echo "$(YELLOW)🧨 Obliterating the executable...$(RESET)"
	@$(MAKE) -C libft_all fclean >/dev/null
	@rm -f $(NAME)
	@echo "$(GREEN)💥 Complete annihilation achieved! Your slate is wiped clean.$(RESET)"

re: fclean all

# ASCII art logo for MINISHELL with rainbow colors
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