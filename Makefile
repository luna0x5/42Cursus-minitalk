# -*- MakeFile -*-

SERVER = server
CLIENT = client
B_SERVER = server_bonus
B_CLIENT = client_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror

SSOURCES = mandatory/server.c \
		mandatory/libft_utils.c 
CSOURCES = mandatory/client.c \
		mandatory/libft_utils.c
SOBJ = $(SSOURCES:.c=.o)
COBJ = $(CSOURCES:.c=.o)

BSSOURCES = bonus/server_bonus.c \
		bonus/libft_utils_bonus.c \
		bonus/utils_bonus.c
BCSOURCES = bonus/client_bonus.c \
		bonus/libft_utils_bonus.c 
B_SOBJ = $(BSSOURCES:.c=.o)
B_COBJ = $(BCSOURCES:.c=.o)

all : $(SERVER) $(CLIENT)

$(SERVER) : $(SOBJ) mandatory/minitalk.h
	$(CC) $(FLAGS) $(SOBJ) -o $(SERVER)

$(CLIENT) : $(COBJ) mandatory/minitalk.h
	$(CC) $(FLAGS) $(COBJ) -o $(CLIENT)

bonus : $(B_SERVER) $(B_CLIENT)

$(B_SERVER) : $(B_SOBJ) bonus/minitalk_bonus.h
	$(CC) $(FLAGS) $(B_SOBJ) -o $(B_SERVER)

$(B_CLIENT) : $(B_COBJ) bonus/minitalk_bonus.h
	$(CC) $(FLAGS) $(B_COBJ) -o $(B_CLIENT)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean :
	rm -f $(SOBJ) $(COBJ) $(B_SOBJ) $(B_COBJ)

fclean : clean
	rm -f $(SERVER) $(CLIENT) $(B_SERVER) $(B_CLIENT)

re : fclean all

.PHONY : clean
