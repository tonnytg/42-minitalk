CLIENT = client
SERVER = server
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: $(CLIENT) $(SERVER)

$(CLIENT):
	cc $(FLAGS) client.c -o $(CLIENT)
$(SERVER):
	cc $(FLAGS) server.c -o $(SERVER)

clean:
	cc $(FLAGS) client.c -o $(CLIENT)
	cc $(FLAGS) server.c -o $(SERVER)

fclean:
	$(RM) client
	$(RM) server
	@printf "$(_WARNING) client removed.\n"
	@printf "$(_WARNING) server removed.\n"

re:
	cc $(FLAGS) client.c -o $(CLIENT)
	cc $(FLAGS) server.c -o $(SERVER)

.PHONY: all clean fclean re