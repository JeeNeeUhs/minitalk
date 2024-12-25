NAME				= minitalk

CLIENT				= client
SERVER				= server

CLIENT_BONUS		= client_bonus
SERVER_BONUS		= server_bonus

CLIENT_SRC			= client.c
SERVER_SRC			= server.c

CLIENT_BONUS_SRC	= client_bonus.c
SERVER_BONUS_SRC	= server_bonus.c

CFLAGS				= -Wall -Wextra -Werror

all: $(NAME)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_BONUS_SRC)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_SRC) -o $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_SRC)
	$(CC) $(CFLAGS) $(SERVER_BONUS_SRC) -o $(SERVER_BONUS)

$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT)

$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER)

$(NAME): $(CLIENT) $(SERVER)

clean:
	$(RM) $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

fclean: clean

re: fclean all

.PHONY: all clean fclean re