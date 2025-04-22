/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:30:15 by vandre            #+#    #+#             */
/*   Updated: 2024/01/16 00:10:52 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdarg.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *str, const char *s, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
bool	ft_atoi(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_iswhitespace(char c);

int		ft_printf(const char *str, ...);
void	len_convertbase(unsigned long nb, char index, size_t *len);
size_t	len_putchar(char c);
void	len_putnbr(int nb, size_t *len);
size_t	len_putstr(char *str);

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
size_t	ft_strlen_gnl(const char *str);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size);
size_t	ft_strlcat_gnl(char *dst, const char *src, size_t n);
void	swap_buffer(char *buffer);
void	cut_line(char *line);
char	*init_line(char *line, char *buffer);
int		in_line(char *str);
void	*ft_calloc_gnl(size_t count, size_t size);

#endif
