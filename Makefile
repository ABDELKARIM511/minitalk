NAME = server

NAME1 = client

FILES = server.c

FILES1 = client.c

INCLUDE = minitalk.h

CC = cc 

CFLAGS = -Wall -Wextra -Werror

OBJS = ${FILES:.c=.o}

OBJS1 = ${FILES1:.c=.o}

all:$(NAME)

$(NAME): $(OBJS) $(OBJS1)
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDE) -o $(NAME)
	@$(CC) $(CFLAGS) $(OBJS1) -I $(INCLUDE) -o $(NAME1)
	@echo "SUUUUUUUUIIIIIII"

%.o : %.c $(INCLUDE)
	gcc  $(CFLAGS) -o $@ -c $<

clean:
	@rm -f ${OBJS}
	@rm -f ${OBJS1}
	@echo "SUUUUUUUUIIIIIII"

fclean: clean
	@rm -f ${NAME}
	@rm -f ${NAME1}
	@echo "SUUUUUUUUIIIIIII"

re: fclean all
