/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:37:07 by rsticks           #+#    #+#             */
/*   Updated: 2019/03/20 22:27:24 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int check_head(char *buff)
{
	int j;
	int i;

	i = 0;
	while (buff[i] != '\n')
		i++;
	t_head.only = i;
	if ((i < 4) && (i > 7))
		return(1);
	i = i - 4;
	j = i;
	while (i >= 0)
	{
		if (!(buff[i] >= '0') && (buff[i] <= '9'))
			return(1);
		i--;
	}
	return (0);
}

int check_length(char *buff)
{
	int i;
	int c;

	i = t_head.only + 1;
	while (buff[i] != '\0')
	{
		c++;
		if (buff[i] == '\n')
		{
			if (c != t_head.length)
				return (0);
			c = 0;
		}
		i++;
	}

}

int check_nb_of_lines(char *buff)
{
	int nb;
	int j;
	int i;
	
	nb = 0;
	i = t_head.only - 3;
	j = i;
	i = 0;
	while (i != j)
	{
		nb = nb * 10 + (buff[i] -'0');
		i++;
	}
	i = 0;
	j = t_head.only + 1;
	while (buf[j] =! '\n')
		j++;
	t_head.length = j - t_head.only + 1;
	while (*buff)
	{
		if (*buff == '\n')
			i++;
		buff++;
	}
	if (nb != i)
		return(1);
	return(0);
}

int check_lines(char *buff)
{
	int i;

	i = 0;
	while (buff[i] != '\n')
		i++;
	i++;
	while (buff[i] != '\0')
	{
		if ((buff[i] != t_head.empty) && (buff[i] != t_head.block))
			return (1);
		i++;
	}
	return (0);
}

int check_head_character(void)
{
	if ((t_head.square == t_head.block) || (t_head.square == t_head.empty) || (t_head.empty == t_head.block))
		return (1);
	return (0);
}
