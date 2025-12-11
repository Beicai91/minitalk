NAME_C = client
NAME_S = server
CC = cc
CFLAGS = -Wextra -Werror -Wall -fsanitize=address
LIBFT_PATH = ../lib/libft
LIBFT = ../lib/libft/libft.a

SRCS_C = client.c
SRCS_S = server.c 


OBJS_C = ${SRCS_C:.c=.o}
OBJS_S = ${SRCS_S:.c=.o}


all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJS_C) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_C) -o $@
$(NAME_S): $(OBJS_S) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_S) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	
$(LIBFT):
	make -C $(LIBFT_PATH) all
	make -C $(LIBFT_PATH) bonus

clean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(OBJS_C) $(OBJS_S) 

fclean:clean
	rm -f $(NAME_C) $(NAME_S) 

re: fclean all

.PHONY: all bonus clean fclean re