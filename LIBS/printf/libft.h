/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:13:56 by bribot            #+#    #+#             */
/*   Updated: 2026/02/18 10:52:40 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

/* STRUCT */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* MANDATORY PART*/
int					ft_strlen(const char *str);
void				ft_bzero(void *src, size_t size);
int					ft_atoi(const char *s);
void				*ft_calloc(size_t size, size_t nbr);
int					ft_isalnum(int n);
int					ft_isalpha(int n);
int					ft_isascii(int n);
int					ft_isdigit(int n);
int					ft_isprint(int n);
char				*ft_itoa(int n);
void				*ft_memchr(const void *src, int to_find, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_memmove(void *dest, const void *src, size_t size);
void				*ft_memset(void *src, int value, size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char *s, char c);
char				*ft_strchr(const char *str, int to_find);
char				*ft_strdup(const char *src);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(char *s1, char *s2, size_t size);
char				*ft_strnstr(const char *to_searched, const char *to_find,
						size_t size);
char				*ft_strrchr(char *str, int to_find);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int i);
int					ft_toupper(int i);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list	*lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstnew(void	*content);
int					ft_lstsize(t_list *lst);

#endif