/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:20:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/03 09:54:14 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_specs
{
	int		zero;
	int		pound;
	int		plus;
	int		minus;
	va_list	arg;
	char	format;
	int		width;
	int		precision;
	char	space;
}	t_specs;

/* Basic printf functions */

int		ft_printf(const char *str, ...);
char	*printtype(char c, va_list v);
void	specinit(t_specs *s);
int		putnewstr(t_specs *s, va_list v, int *count, int len);
int		basic_print(char c, va_list v);

/* Number handling including hexidecimal */

char	*ft_neghandle(long long int n);
char	*ft_nbrtoa(size_t n, int radix);
int		nbrcount(size_t n, int radix);
char	*nbrwidth(t_specs *s, char *str);
void	strupper(char *str);
char	*hexwidth(t_specs *s, char *str);
char	*hexprec(t_specs *s, char *str);
char	*nbrprec(t_specs *s, char *str);
char	*nbrmod(t_specs *s, char *str);

/* String Handling */

char	*strhandle(va_list v);
char	*strwidth(t_specs *s, char *str);
char	*strprec(t_specs *s, char *str);
char	*formatstr(t_specs *s, char *s2);
void	strfill(char *str, char c, int len);

/* Character Handling */

char	*chartostr(char c);
char	*charwidth(char	*str, t_specs *s);
void	charprec(t_specs *s, char *str, int *count);
int		charcheck(char *str, char c);
void	charmod(char *str, char c);

/* Checking format specifiers and flags */

int		formatspec(const char *c, t_specs *s, va_list v, int *count);
void	flagfill(t_specs *s, char *str);
void	setwidth(t_specs *s, char *str);
void	setprecision(t_specs *s, char *str);
int		ignoreprec(char *str, int i);
int		validitycheck(char *s);
int		flagcheck(char c);
int		formatcheck(char c);
char	*paramaterfill(char *s);
int		formatnull(const char *c, t_specs *s, int len, int *count);

/* Memory allocation / freeing */

char	*freejoin(char *s1, char *s2);

/* Extra fun functions */
char	*radix_print(va_list v);

#endif
