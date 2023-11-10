/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jariza-o <jariza-o@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:05:11 by jariza-o          #+#    #+#             */
/*   Updated: 2023/11/10 13:04:12 by jariza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	ft_leaks(void)
// {
// 	system("leaks -q a.out");
// }

int	ft_strcmp(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		c1;
	int		c2;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	c1 = 0;
	while (s1 && s1[c1])
	{
		str[c1] = s1[c1];
		c1++;
	}
	free(s1);
	c2 = 0;
	while (s2 && s2[c2])
	{
		str[c1] = s2[c2];
		c1++;
		c2++;
	}
	str[c1] = '\0';
	return (str);
}

char	*ft_read(int fd, char *buffer)
{
	char	*temp;
	int		i;

	i = 1;
	while (i > 0 && ft_strcmp(buffer, '\n'))
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (NULL);
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1)
			return (free(buffer), free(temp), NULL);
		if (i == 0)
			return (free(temp), buffer);
		temp[i] = '\0';
		buffer = ft_strjoin(buffer, temp);
		free(temp);
	}
	return (buffer);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	if (!str || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str && str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str && str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_remove_line(char *buffer, char *line)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	while (buffer && buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	i++;
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	n = 0;
	while (buffer && buffer[i] != '\0')
	{
		str[n] = buffer[i];
		n++;
		i++;
	}
	str[n] = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (!fd)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_remove_line(buffer, line);
	return (line);
}

// int main(void)
// {
// 	atexit(ft_leaks);
// 	int fd = open("test.txt", O_RDONLY);
// 	char *str = get_next_line(fd);
// 	printf("%s", str);
// 	free (str);
// 	str = get_next_line(fd);
// 	printf("%s", str);
// 	free (str);
// 	str = get_next_line(fd);
// 	printf("%s", str);
// 	// free (str);
// 	return (0);
// }
