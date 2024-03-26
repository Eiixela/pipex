# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 14:51:00 by aljulien          #+#    #+#              #
#    Updated: 2024/03/26 15:12:33 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS =	pipex.c\
		utils.c\
		ft_split.c\
		libft_utils.c\
		libft_utils2.c
            
OBJS = $(SRCS:%.c=${OBJ_D}%.o)

OBJ_D = .obj/

HEADER = pipex.h

NAME = pipex

CC = cc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${OBJS}:	${OBJ_D}%.o: %.c pipex.h
		${CC} ${FLAGS} -I. -c $< -o $@

${NAME}:	${OBJ_D} ${OBJS} Makefile 
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${OBJ_D}:
	mkdir -p ${OBJ_D}

libft:
	make --no-print-directory -C 

clean:
	make --no-print-directory -C
	rm -rf ${OBJ_D}

fclean:
	make --no-print-directory -C
	rm -rf ${OBJ_D}
	rm -f ${NAME}

re: fclean .internal_separate all

.PHONY: all clean fclean re leaks