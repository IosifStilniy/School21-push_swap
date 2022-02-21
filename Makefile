SRCS		=	push_swap.c		\
				swap_cmnds.c	\
				cmnds.c			\
				utils.c			\

B_SRCS		=	${wildcard *_bonus.c}	\
				${wildcard GetNextLine/*.c}	\

OBJS		=	$(SRCS:.c=.o)	

B_OBJS		=	$(B_SRCS:.c=.o)	

HEADS		=	push_swap.h

B_HEADS		=	push_swap_bonus.h

LIBNAME		=	libft.a

LIB			=	libft

NAME		=	push_swap

B_NAME		=	checker

GCC			=	gcc -g -Wall -Wextra -Werror -MMD

RM			=	rm -f

%.o: 		%.c
			$(GCC) -c -I$(LIB) $< -o $@

$(NAME):	$(HEADS) $(OBJS) $(LIBNAME)
			$(GCC) $(OBJS) $(LIBNAME) -o $(NAME)

all:		$(NAME)

$(LIBNAME):	lib

lib:		
			@$(MAKE) -C $(LIB)

bonus:		$(B_HEADS) $(B_OBJS) $(LIBNAME)
			$(GCC) $(B_OBJS) $(LIBNAME) -o $(B_NAME)

clean:
			@$(MAKE) -C $(LIB) clean
			$(RM) $(OBJS)
			$(RM) $(B_OBJS)

fclean: 	clean
			@$(MAKE) -C $(LIB) fclean
			$(RM) $(wildcard *.d)
			$(RM) $(wildcard GetNextLine/*.d)
			$(RM) $(NAME)
			$(RM) $(B_NAME)

re:			fclean all bonus

.PHONY:		all bonus clean fclean re lib