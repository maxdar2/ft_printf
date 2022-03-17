/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgenova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:29:54 by dgenova           #+#    #+#             */
/*   Updated: 2022/01/22 16:29:57 by dgenova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <stdarg.h>

typedef struct s_printf {

	char section;
	char type;
	int  flag_minus;
	int  flag_zero;
	int  flag_dash;
	int  flag_space;
	int  flag_plus;
	int  flag_percentage;
	int  width;
	int  precision;
	int  chars_printed;
} t_printf;

static void reset(t_printf *t) {
	t->type            = ' ';
	t->section         = ' ';
	t->flag_dash       = 0;
	t->flag_minus      = 0;
	t->flag_plus       = 0;
	t->flag_dash       = 0;
	t->flag_space      = 0;
	t->flag_zero       = 0;
	t->flag_percentage = 0;
	t->precision       = -1;
	t->width           = -1;

}

static int is_beginning(t_printf *t, char c) {
	if (!(t->section == ' ' && c == '%'))
		return (0);
	t->flag_percentage = 1;
	t->section = '%';
	return (1);
}

static int is_flags(t_printf *t, char c) {
	char str[2];
	char str_r[2];

	str[0]   = c;
	str[1]   = '\0';
	str_r[0] = t->section;
	str_r[1] = '\0';
	if (!ft_strnstr("%F", str_r, 2))
		return (0);
	if (ft_strnstr("-0# +", str, 5)) {
		if (c == '-')
			t->flag_minus = 1;
		if (c == '0')
			t->flag_zero  = 1;
		if (c == '+')
			t->flag_plus  = 1;
		if (c == ' ')
			t->flag_space = 1;
		if (c == '#')
			t->flag_dash  = 1;
		t->section        = 'F';
		return (1);
	}
	return (0);
}

static int is_width(t_printf *t, char c) {
	char str[2];
	char str_atoi[2];

	str[0] = t->section;
	str[1] = '\0';
	str_atoi[0] = c;
	str_atoi[1] = '\0';
	if (!(ft_strnstr("%FW", str, 3) && ft_isdigit(c)))
		return (0);
	if(t->width == -1)
		t->width = ft_atoi(str_atoi);
	else
		t->width = t->width * 10 + ft_atoi(str_atoi);
	t->section = 'W';
	return (1);
}

static int is_types(t_printf *t, char c) {
	char str[2];
	char str_r[2];

	str[0]   = c;
	str[1]   = '\0';
	str_r[0] = t->section;
	str_r[1] = '\0';
	if (!ft_strnstr("%FWP", str_r, 4))
		return (0);
	if (ft_strnstr("cspdiuxX%", str, 9)) {
		t->type    = c;
		t->section = 'E';
		return (1);
	}
	return (0);
}

static int is_precison(t_printf *t, char c) {
	char str[2];
	char str_atoi[2];

	str[0] = t->section;
	str[1] = '\0';
	str_atoi[0] = c;
	str_atoi[1] = '\0';
	if (ft_strnstr("%FW", str, 3) && c == '.') {
		t->section = 'P';
		t->precision = 0;
		return (1);
	}
	if (!(t->section == 'P' && ft_isdigit(c)))
		return (0);
	t->precision = t->precision * 10 + ft_atoi(str_atoi);
	t->section = 'P';
	return (1);
}

static void print_c(t_printf *t, va_list args)
{
	char *c;
	int   i;

	i = -1;
	c = va_arg(args, char*);
	if(t->flag_minus)
		write(1, &c, 1);
	while(++i < (t->width - 1))
	{
		write(1, " ", 1);
		t->chars_printed++;
	}
	if(!t->flag_minus)
		write(1, &c, 1);
	t->chars_printed++;
}

static void print_s(t_printf *t, va_list args)
{
	char      *s;
	int        i;
	int	   s_len;
	int 	diff;

	s = va_arg(args, char*);
	s_len = (int) ft_strlen(s);
	i = 0;
	diff = 0;
	if(s_len <= t->width)
		diff = t->width - s_len;
	if(t->flag_minus)
		ft_putstr_fd(s, 1);
	while(++i <= diff)
		write(1, " ", 1);
	if(!t->flag_minus)
		ft_putstr_fd(s, 1);
	t->chars_printed += s_len + diff;
}

static void print_int(t_printf *t, va_list args)
{
	int   num;
	char   *s;
	int s_len;

	num = va_arg(args, int);
	s = ft_itoa(num);
	s_len = (int) ft_strlen(s);


	ft_putstr_fd(s, 1);
	t->chars_printed += s_len;
}

static void handle_valid(t_printf *t, va_list args)
{
	if(t->type == 'c')
		print_c(t, args);
	if(t->type == 's')
		print_s(t, args);
	if(t->type == 'i' || t->type == 'd')
		print_int(t, args);
	reset(t);
}

static void handle_invalid(t_printf *t)
{
	reset(t);
}

static char scan(t_printf *t, char c) {
	if (is_beginning(t, c))
		return (t->section);
	if (is_flags(t, c))
		return (t->section);
	if (is_width(t, c))
		return (t->section);
	if (is_precison(t, c))
		return (t->section);
	if (is_types(t, c))
		return (t->section);
	return ('I');
}

int ft_print_f(const char *text, ...)
{
	static t_printf t;
	int             i;
	char            s;
	va_list         args;

	va_start(args, text);
	t.chars_printed = 0;
	reset(&t);
	i = 0;
	while (text[i] != '\0') {
		s = scan(&t, text[i]);
		if(t.section == ' ' && t.flag_percentage == 0)
		{
			write(1, &text[i], 1);
			t.chars_printed++;
		}
		else if (s == 'E')
			handle_valid(&t, args);
		else if (s == 'I')
			handle_invalid(&t);
		i++;
	}
	va_end(args);
	return t.chars_printed;
}

int main(void) {
	int n;
	char text[] = "<<%0+10i>>\n";

	n = ft_print_f(text, -123);
	printf("Numero caratteri: %d\n", n);

	n = printf(text, -123);
	printf("Numero caratteri: %d\n", n);

//	char text[] = "pippo";
//	char text[] = "% +- 0  #023s";

	// original
//	printf("Original: ");

//	printf("<<%c>>\n", '0' + 242);
//	exit(0);

	return (0);
}
