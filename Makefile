# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 13:46:16 by nde-chab          #+#    #+#              #
#    Updated: 2024/09/18 15:35:43 by nde-chab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft_all/libft_printf_gnl.a
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I .

SRCS_DIR = srcs/*/

FUNC = main.c print_all.c free_func.c free_struct.c init_struct.c list_utils.c pipe_utils.c
FUNC += special_case.c token.c token_utils.c
SRCS = $(addprefix $(SRCS_DIR), $(FUNC))

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

# Rule to compile .c files to .o files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "\033[1;34mCompilation de $<...\033[0m"
	$(MAKE) -C libft_all/
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;32mFichier objet $@ créé avec succès !\033[0m"




# Rule to create the final executable
$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[1;32mLinking objects...\033[0m"
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "\033[1;32mCompilation terminée avec succès ! 🎉\033[0m"

	
# Default target	
all : $(NAME)

# Clean object files
clean:
	@echo "\033[1;33mNettoyage des fichiers objets...\033[0m"
	$(MAKE) -C libft_all/ clean
	rm -rf $(OBJS_DIR)
	@echo "\033[1;32mNettoyage terminé.\033[0m"

# Full clean
fclean: clean
	@echo "\033[1;33mSuppression de l'exécutable...\033[0m"
	$(MAKE) -C libft_all/ fclean
	rm -f $(NAME)
	@echo "\033[1;32mSuppression complète effectuée.\033[0m"

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
