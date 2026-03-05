/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhtun <thhtun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by thhtun            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by thhtun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* memory */
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* strings */
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin(size_t count, ...);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_str_isspace(const char *s);
int		ft_str_startswith(const char *str, const char *prefix);
int		ft_str_endswith(const char *str, const char *suffix);
char	*ft_strreplace(const char *str, const char *old, const char *rep);

/* chars */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* numbers */
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);

/* output */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* linked list */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lst_foreach(t_list *lst, void (*f)(void *, void *), void *ctx);
void	ft_lst_removeif(t_list **lst, void (*del)(void *),
			int (*match)(void *, void *), void *ctx);

/* sort */
int		ft_cmp_str_asc(void *a, void *b);
int		ft_cmp_str_desc(void *a, void *b);
void	ft_arr_sort(char **arr, int (*cmp)(void *, void *));
void	ft_lst_sort(t_list **lst, int (*cmp)(void *, void *));

/* arrays */
int		ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
void	ft_arrfree(char **arr);
char	**ft_arradd(char **arr, char *new_str);

#endif
