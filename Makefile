# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 14:51:00 by aljulien          #+#    #+#              #
#    Updated: 2024/04/20 16:21:32 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	pipex.c\
		utils.c\
		split.c\
		libft_utils.c\
		libft_utils2.c\
		error.c\

OBJS = $(SRCS:%.c=${OBJ_D}%.o)

OBJ_D = .obj/

HEADER = pipex.h

NAME = pipex

CC = cc

FLAGS = -Wall -Wextra -Werror -g3

all: ${NAME}

${OBJS}:	${OBJ_D}%.o: %.c pipex.h
		${CC} ${FLAGS} -I. -c $< -o $@

${NAME}:	${OBJ_D} ${OBJS} Makefile 
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${OBJ_D}:
	mkdir -p ${OBJ_D}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all

.PHONY: all clean fclean re leaks