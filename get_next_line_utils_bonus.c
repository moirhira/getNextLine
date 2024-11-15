/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:23:05 by moirhira          #+#    #+#             */
/*   Updated: 2024/11/14 14:23:22 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// calculate the len ==========done==========
int	calclen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len] != '\0')
		len++;
	return (len);
}

//get a new line  ===========done============
char	*find_newline(char *data, int ch)
{
	int	i;

	i = 0;
	if (!data)
		return (NULL);
	while (data[i] != '\0')
	{
		if (data[i] == (char)ch)
			return (&data[i]);
		i++;
	}
	return (NULL);
}

// cut line (\n) from buffer =========done====
char	*separate_line(char *data)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!data)
		return (NULL);
	while (data[i] != '\n' && data[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = data[j];
		j++;
	}
	if (data[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// copy function
void	ft_copy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

// update the bufer by separating the line ======done======
char	*update_buffer(char *data)
{
	char	*remaindata;
	char	*new_data;
	int		datalen;

	remaindata = find_newline(data, '\n');
	if (remaindata)
		remaindata++;
	datalen = calclen(remaindata);
	if (!datalen)
	{
		free(data);
		return (NULL);
	}
	new_data = malloc(datalen + 1);
	if (!new_data)
	{
		free(data);
		return (NULL);
	}
	ft_copy(new_data, remaindata);
	free(data);
	return (new_data);
}
