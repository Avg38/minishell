SRCS	=	\
			2d/dup_2d.c \
			2d/free_2d.c \
			2d/len_2d.c \
			2d/putchar_2d.c \
			\
			ft_fd/ft_putchar_fd.c \
			ft_fd/ft_putendl_fd.c \
			ft_fd/ft_putnbr_fd.c \
			ft_fd/ft_putstr_fd.c \
			\
			ft_list/ft_lstadd_back.c\
			ft_list/ft_lstadd_front.c\
			ft_list/ft_lstclear.c\
			ft_list/ft_lstdelone.c\
			ft_list/ft_lstiter.c\
			ft_list/ft_lstlast.c\
			ft_list/ft_lstmap.c\
			ft_list/ft_lstnew.c\
			ft_list/ft_lstsize.c\
			\
			ft_mem/ft_bzero.c\
			ft_mem/ft_calloc.c\
			ft_mem/ft_memchr.c\
			ft_mem/ft_memcmp.c\
			ft_mem/ft_memcpy.c\
			ft_mem/ft_memmove.c\
			ft_mem/ft_memset.c\
			\
			ft_others/ft_atoi.c\
			ft_others/ft_isalnum.c\
			ft_others/ft_isalpha.c\
			ft_others/ft_isascii.c\
			ft_others/ft_isdigit.c\
			ft_others/ft_isprint.c\
			ft_others/ft_isspace.c\
			ft_others/ft_itoa.c\
			\
			ft_printf/ft_printf_fd_utils.c\
			ft_printf/ft_printf_fd.c\
			ft_printf/ft_printf1.c\
			ft_printf/ft_printf2.c\
			\
			ft_str/ft_split.c \
			ft_str/ft_strcat.c \
			ft_str/ft_strchr.c\
			ft_str/ft_strcmp.c \
			ft_str/ft_strdup.c\
			ft_str/ft_striteri.c \
			ft_str/ft_strjoin.c \
			ft_str/ft_strlcat.c\
			ft_str/ft_strlcpy.c \
			ft_str/ft_strlen.c\
			ft_str/ft_strmapi.c \
			ft_str/ft_strncmp.c \
			ft_str/ft_strnstr.c \
			ft_str/ft_strrchr.c \
			ft_str/ft_strtrim.c \
			ft_str/ft_substr.c \
			ft_str/ft_tolower.c \
			ft_str/ft_toupper.c \
			\
			gc/gc_add.c\
			gc/gc_calloc.c\
			gc/gc_clear.c\
			gc/gc_del_one.c\
			gc/gc_itoa.c\
			gc/gc_lstmap.c\
			gc/gc_lstnew.c\
			gc/gc_malloc.c\
			gc/gc_ptr.c\
			gc/gc_realloc.c\
			gc/gc_split.c\
			gc/gc_strcut.c\
			gc/gc_strdup.c\
			gc/gc_strjoin.c\
			gc/gc_strmapi.c\
			gc/gc_strndup.c\
			gc/gc_strtrim.c\
			gc/gc_substr.c\
			\
			gnl/get_next_line.c\
			gnl/get_next_line_utils.c

OBJS	=	${SRCS:.c=.o}
NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

%.o:	%.c libft.h
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		@ar rc ${NAME} ${OBJS}
		@mv ${OBJS} obj/

all : 		${NAME}

clean:
		${RM} obj/*.o

fclean:		clean
			${RM} ${NAME}
re:			fclean all
