# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 18:01:25 by zel-ghab          #+#    #+#              #
#    Updated: 2025/06/23 16:46:45 by zel-ghab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########################################
## ARGUMENTS

NAME 		= pipex
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g

###########################################
## LIBRARIES

PRINTF        = ./functions/ft_printf
LIBFT         = ./functions/libft

IFLAGS        = -I $(PRINTF) -I $(LIBFT)
LDFLAGS       = -L $(PRINTF) -L $(LIBFT) -lft -lftprintf

###########################################
## SOURCES

SRC_FILES	= pipex.c \
		cmd.c \
		utils.c

###########################################
## OBJECTS

OBJ_DIR = .cache
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

###########################################
## RULES

all : ${NAME}

${NAME} : ${OBJ_FILES}
	@echo "🛠️  Compiling libraries..."
	@make -s -C ${PRINTF}
	@make -s -C ${LIBFT}
	@${CC} ${CFLAGS} ${OBJ_FILES} ${LDFLAGS} -o ${NAME}
	@echo "✅ Compilation successful !"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean :
	@rm -rf ${OBJ_DIR}
	@make -s clean -C $(PRINTF)
	@make -s clean -C $(LIBFT)
	@echo "🧹 Object files removed."

fclean : clean
	@make -s fclean -C $(LIBFT)
	@make -s fclean -C $(PRINTF)
	@rm -rf ${NAME}
	@echo "🧹 Everything is cleaned."

re : fclean all

.PHONY: all clean fclean re
