NAME_C = client
NAME_S = server
NAME_CB = client_bonus
NAME_SB = server_bonus
CC = cc
CFLAGS = -Wextra -Werror -Wall -fsanitize=address
LIBFT_PATH = ./libft
LIBFT = ./libft/libft.a

SRCS_C = client.c
SRCS_S = server.c 

SRCS_CB = client_bonus.c 
SRCS_SB = data_process.c \
		  server_bonus_utils.c \
		  server_bonus.c

OBJS_C = ${SRCS_C:.c=.o}
OBJS_S = ${SRCS_S:.c=.o}
OBJS_CB = ${SRCS_CB:.c=.o}
OBJS_SB = ${SRCS_SB:.c=.o}

all: $(NAME_C) $(NAME_S)
bonus: $(NAME_CB) $(NAME_SB)

$(NAME_C): $(OBJS_C) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_C) -o $@
$(NAME_S): $(OBJS_S) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_S) -o $@
$(NAME_CB): $(OBJS_CB) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_CB) -o $@
$(NAME_SB): $(OBJS_SB) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_SB) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	
$(LIBFT):
	make -C $(LIBFT_PATH) all
	make -C $(LIBFT_PATH) bonus

clean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(OBJS_C) $(OBJS_S) $(OBJS_CB) $(OBJS_SB)

fclean:clean
	rm -f $(NAME_C) $(NAME_S) $(NAME_CB) $(NAME_SB)

re: fclean all

.PHONY: all bonus clean fclean re