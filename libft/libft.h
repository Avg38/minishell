#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdio.h>

/*------------------------file-------------------------*/
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
/*------------------------list-------------------------*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
/*-----------------------ft_printf-----------------------*/
void	ft_print_char(int c, size_t *len);
void	ft_print_str(char *str, size_t *len);
void	ft_print_ptr(unsigned long long addr, size_t *len);
void	ft_print_nbr(int nb, size_t *len);
void	ft_print_hexa(unsigned int nb, char *base, size_t *len);
void	ft_print_unsigned(unsigned int nb, size_t *len);
int		ft_printf(const char *str, ...);
/*--------------------------gnl--------------------------*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_fd
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
}	t_fd;

char	*get_next_line(int fd);
size_t	check_newline(char *str);
size_t	ft_strlen_gnl(char *str);
char	*str_init(char	*line);
char	*buffer_init(int fd, t_fd *buffer_memory);
/*--------------------garbage_collector--------------------*/
# ifndef GC_SIZE
#  define GC_SIZE 42
# endif

void	*gc_add(void *ptr, int gc_id);
void	*gc_calloc(size_t nmemb, size_t size, int id_gc);
void	gc_clear(int gc_id, void (*del)(void*));
void	gc_del_one(void *ptr_to_free, int gc_id);
char	*gc_itoa(int n, int gc_id);
t_list	*gc_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *),
	int id_gc);
t_list	*gc_lstnew(void *content, int gc_id);
void	*gc_malloc(size_t size, int id_gc);
t_list	**gc_ptr(int gc_id);
void	*gc_realloc(void *ptr, size_t old_size, size_t new_size, int id_gc);
char	**gc_split(char const *s, char c, int id_gc);
char	*gc_strcut(char const *str, size_t cut_begin, size_t cut_end, int gc_id);
char	*gc_strdup(const char *str, int id_gc);
char	*gc_strjoin(char const *s1, char const *s2, int id_gc);
char	*gc_strmapi(char const *s, char (*f)(unsigned int, char), int id_gc);
char	*gc_strndup(char *buffer, int len, int id_gc);
char	*gc_strtrim(char const *s1, char const *set, int id_gc);
char	*gc_substr(char const *s, unsigned int start, size_t len, int id_gc);
/*-------------------------mem-------------------------*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
/*-----------------------others------------------------*/
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
int		ft_isspace(char c);
/*-----------------------printf------------------------*/
void	ft_print_ptr(unsigned long long addr, size_t *len);
void	ft_print_nbr(int nb, size_t *len);
void	ft_print_hexa(unsigned int nb, char *base, size_t *len);
void	ft_print_unsigned(unsigned int nb, size_t *len);
int		ft_printf(const char *str, ...);
void	print_ptr_fd(int fd, void *ptr, size_t *count_char);
void	print_hexa_fd(int fd, unsigned int nbr, size_t *count_char, char *base);
void	print_nbr_fd(int fd, int nbr, size_t *count_char);
void	print_unbr_fd(int fd, unsigned int nbr, size_t *count_char);
void	print_char_fd(int fd, char c, size_t *count_char);
void	print_str_fd(int fd, char *s, size_t *count_char);
void	print_flag_fd(int fd, va_list args, char *str, size_t *count_char);
int		ft_printf_fd(int fd, const char *str, ...);
/*-------------------------str-------------------------*/
char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
/*-------------------------gnl-------------------------*/
char	*get_next_line(int fd);
/*-------------------------2d-------------------------*/
char	**dup_2d(char **tab);
void	free_2d(char **tab);
size_t	len_2d(char **tab);
void	putchar_2d(char **tab);

#endif
