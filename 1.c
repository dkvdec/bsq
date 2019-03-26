/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:13:56 by dheredat          #+#    #+#             */
/*   Updated: 2019/03/20 14:55:12 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#define BUFF_SIZE 4096

struct		s_head {
	int		size;
	int		length;
	char	empty;
	char	block;
	char 	square;
}			t_head;

//extern		t_head;

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int ft_sqr_paint(char **map_array, int isqr, int jsqr, int sqr_max)
{
	int i;
	int j;

	i = 0;
	while (map_array[i++])
	{
		j = 0;
		while (map_array[i][j++])
		{
			if(((i >= isqr) && (j >= jsqr))
					&& ((i <= isqr + sqr_max - 1) && (j <= jsqr + sqr_max - 1)))
			{
				ft_putchar(t_head.square);
			}
			else
			{
				ft_putchar(map_array[i][j]);
			}
		}
	}
	return(1);
}

int ft_sqr_test(char **map_array, int i, int j)
{
	int counter;
	int step;

	counter = 1;
	while(map_array[i][j])
	{
		step = 0;
		while(step != counter + 1)
		{
			if(map_array[i+counter][j+step] == t_head.block)
				return(counter);
			step++;
		}
		step = 0;
		while(step != counter + 1)
		{
			if(map_array[i+step][j+counter] == t_head.block)
				return(counter);
			step++;
		}
		counter++;
	}
	return(counter);
}

int ft_get_nbr(char *line_char)
{
	int line_int;
	int i;
	int step;

	line_int = 0;
	i = 0;
	step = 1;
	while(line_char[i])
	{
		line_int = line_int + ((line_char[i] - '0') * step);
		step *= 10;
		i++;
	}
	return (line_int);
}

int ft_head_check(char *buff)
{
	char *line_char;
	int i;
	int j;

	i = 0;
	while (buff[i] != '\n')
		i++;
	t_head.square = buff[i - 1];
	t_head.block = buff[i - 2];
	t_head.empty  = buff[i - 3];
	line_char = (char*)malloc(sizeof(char) * (i - 1));
	i -= 3;
	j = 0;
	while (i-- >= -1)
	{
		if (i == -1)
			line_char[j] = '\0';
		else
		{
			line_char[j++] = buff[i];
		}
	}
	t_head.size = (ft_get_nbr(line_char));
	return(0);
}

char **ft_map_cut(char *buff)
{
	int i;
	char **map_array;
	int x;
	int y;
	int line_length;

	i = 0;
	map_array = malloc(sizeof(char *) * (t_head.size + 1));
	while (buff[i] != '\n')
		i++;
	y = i;
	line_length = 0;
	while (buff[++y] != '\n')
		line_length++;
	y = 0;
	while (y++ <= t_head.size)
	{
		x = 0;
		map_array[y] = (char *)malloc(sizeof(char) * (line_length + 1));
		while(x <= line_length)
		{
			map_array[y][x++] = buff[++i];
		}
		map_array[y][x] = '\0';
		i++;
	}
	map_array[y] = NULL;
//
	y = 0;
	while(map_array[y++])
	{
		x = 0;
		while(map_array[y][x++])
		{
			ft_putchar(map_array[x][y]);
		}
		ft_putchar('\n');
	}
//
	return (map_array);
}

int ft_stalker(char **map_array)
{
	int i;
	int j;
	int isqr;
	int jsqr;
	int sqr_max;
	int sqr_cur;

	i = 1;
	sqr_max = 0;
	while (map_array[i])
	{
		j = 0;
		while (map_array[i][j])
		{
			if (map_array[i][j] != t_head.block)
			{
				sqr_cur = ft_sqr_test(map_array, i, j);
				if (sqr_cur > sqr_max)
				{
					sqr_max = sqr_cur;
					isqr = i;
					jsqr = j;
				}
			}
			j++;
		}
		i++;
	}
	return(ft_sqr_paint(map_array, isqr, jsqr, sqr_max));
}

int ft_core(char *map)
{
	int file;
	int data;
	char buff[BUFF_SIZE + 1];

	ft_putchar('1');
	file = open(map, O_RDONLY);
	data = read(file, buff, BUFF_SIZE);
	buff[data] = '\0';
	ft_head_check(buff);
	ft_putchar('2');
	ft_stalker(ft_map_cut(buff));
	ft_putchar('3');
	close(file);
	return (0);
}

int main(int argc, char **argv)
{
	int n;

	if (argc > 1)
	{
		ft_putchar('0');
		n = 1;
		while (n < argc)
		{
			ft_core(argv[n]);
			n++;
		}
	}
	else
	return (0);
}
