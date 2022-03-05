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
#include <limits.h>
#include <stdlib.h>
#include <libft.h>

typedef struct s_printf {

	char section;
	char type;
	int  flag_minus;
	int  flag_zero;
	int  flag_dash;
	int  flag_space;
	int  flag_plus;
	int  width;
	int  precision;


} t_printf;

void reset(t_printf *t) {
	t->type       = ' ';
	t->section    = ' ';
	t->flag_dash  = 0;
	t->flag_minus = 0;
	t->flag_plus  = 0;
	t->flag_dash  = 0;
	t->flag_space = 0;
	t->flag_zero  = 0;
	t->precision  = -1;
	t->width      = -1;
}

int is_beginning(t_printf *t, char c) {
	if (t->section == ' ' && c == '%') {
		t->section = '%';
		return (1);
	}
	return (0);
}

int is_flags(t_printf *t, char c) {
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
		t->section = 'F';
		return (1);
	}
	return (0);
}

int is_width(t_printf *t, char c) {
	char str[2];

	str[0] = t->section;
	str[1] = '\0';
	if (ft_strnstr("%FW", str, 3) && ft_isdigit(c)) {
		t->section = 'W';
		return (1);
	}
	return (0);
}

int is_types(t_printf *t, char c) {
	char str[2];
	char str_r[2];

	str[0] = c;
	str[1] = '\0';
	str_r[0] = t->section;
	str_r[1] = '\0';
	if (!ft_strnstr("%FWP", str_r, 2))
		return (0);
	if (ft_strnstr("cspdiuxX%", str, 9)) {
		t->type = c;
		t->section = 'E';
		return (1);
	}
	return (0);
}

int is_precison(t_printf *t, char c) {
	char str[2];

	str[0] = t->section;
	str[1] = '\0';
	if (ft_strnstr("%FW", str, 3) && c == '.') {
		t->section = 'P';
		return (1);
	}
	if (t->section == 'P' && ft_isdigit(c)) {
		t->section = 'P';
		return (1);
	}
	return (0);
}

char scan(t_printf *t, char c) {
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

int main(void) {
	static t_printf t;
	int             i;
	char 			s;

	reset(&t);
	char text[] = "pippo %    +s paperino";
//	char text[] = "pippo";
//	char text[] = "% +- 0  #023s";

	i = 0;
	while (text[i] != '\0') {
		s = scan(&t, text[i]);
		if(s == 'E' || s == 'I')
			reset(&t);
		i++;
	}

	return (0);
}
