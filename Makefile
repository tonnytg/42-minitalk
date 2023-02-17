LIBS    = ./libs
SRC     = ./src
SERVER  = $(SRC)/server.c
CLIENT  = $(SRC)/client.c

CC = gcc
CFLAGS = -Wextra -Wall -Werror

all: server client

server: $(SRC)/server.o
	$(CC) -o $@ $< -L $(LIBS)/libft -lft

client: $(SRC)/client.o
	$(CC) -o $@ $< -L $(LIBS)/libft -lft

%.o: %.c
	make -C $(LIBS)/libft
	cp $(LIBS)/libft/libft.h $(SRC)/libft.h
	$(CC) -c $(CFLAGS) $? -o $@

clean:
	rm -f $(SRC)/*.o
	make -C $(LIBS)/libft clean
	
fclean: clean
	rm server
	rm client
	rm $(SRC)/libft.h
	rm -f server client $(LIBS)/libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re
