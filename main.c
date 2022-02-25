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
	int  flag_minus;
	int  flag_zero;
	int  flag_dash;
	int  flag_space;
	int  flag_plus;
	int  width;
	int  precision;


} t_printf;

void reset(t_printf *t) {
	t->flag_dash  = 0;
	t->flag_minus = 0;
	t->flag_plus  = 0;
	t->flag_dash  = 0;
	t->flag_space = 0;
	t->flag_zero  = 0;
	t->precision  = -1;
	t->width      = -1;
}

int is_flags(t_printf *t, char c) {
	char str[2];

	str[0] = c;
	str[1] = '\0';
	if (ft_strnstr("-0# +", str, 5)) {
		if (c == '-')
			t->flag_minus = 1;
		if (c == '0')
			t->flag_zero = 1;
		if (c == '+')
			t->flag_plus  = 1;
		if (c == ' ')
			t->flag_space = 1;
		if (c == '#')
			t->flag_dash = 1;
		return (1);
	}
	return (0);
}

char scan(t_printf *t, char c) {

	// inizio sequenza
	if (t->section == 0 && c == '%')
		return (t->section = '%');
	if ((t->section == '%' || t->section == 'f') && is_flags(t, c))
		return (t->section = 'f');

}


int main(void) {
	static t_printf t;
	int             i;

	reset(&t);
	//char text[] = "pippo %    +s paperino";
	char text[] = "% +- 0  #s";

	i = 0;
	while (text[i] != '\0') {
		scan(&t, text[i]);
		i++;
	}

	return (0);
}
