/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jariza-o <jariza-o@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:12:05 by jariza-o          #+#    #+#             */
/*   Updated: 2023/11/09 19:44:36 by jariza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int		len_s1;
	int		len_s2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	len_s1 = 0;
	while (s1 && s1[len_s1])
	{
		str[len_s1] = s1[len_s1];
		len_s1++;
	}
	len_s2 = 0;
	while (s2 && s2[len_s2])
	{
		str[len_s1] = s2[len_s2];
		len_s1++;
		len_s2++;
	}
	str[len_s1] = '\0';
	free (s1);
	return (str);
}

char	*ft_read(int fd, char	*buf)
{
	char		*temp;
	int			c;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	c = 1;
	while (c > 0 && ft_strcmp(buf, '\n'))
	{
		c = read(fd, temp, BUFFER_SIZE);
		if (c == -1)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		if (c == 0)
			break ;
		temp[c] = '\0';
		buf = ft_strjoin(buf, temp);
	}
	free(temp);
	return (buf);
}

// char	*ft_read(int fd, char *buffer)
// {
// 	char	*leido;
// 	char	*temp;
// 	int		a;

// 	a = 1;
// 	while (a > 0 && ft_strcmp(temp, '\n'))
// 	{
// 		leido = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 		if (!leido)
// 			return (NULL);
// 		a = read(fd, leido, BUFFER_SIZE);
// 		if (a == -1)
// 		{
// 			free (leido);
// 			free (buffer);
// 			// nose si si linerar buffer
// 			return (NULL);
// 		}
// 		if (a == 0)
// 		{
// 			free (leido);
// 			break ;
// 		}
// 		temp = ft_strjoin(buffer, leido);
// 		free (leido);
// 	}
// 	return (temp);
// }

char	*ft_line(char *buffer)
{
	int		len_line;
	char	*line;

	len_line = 0;
	while (buffer && buffer[len_line] != '\n' && buffer[len_line] != '\0')
		len_line++;
	if (buffer[len_line] == '\n')
		len_line++;
	line = (char *)malloc(sizeof(char) * (len_line + 1));
	if (!line)
		return (NULL);
	len_line = 0;
	while (buffer && buffer[len_line] != '\n' && buffer[len_line] != '\0')
	{
		line[len_line] = buffer[len_line];
		len_line++;
	}
	if (buffer[len_line] == '\n')
	{
		line[len_line] = '\n';
		len_line++;
	}
	line[len_line] = '\0';
	return (line);
}

char	*ft_remove_line(char *buffer, char *line)
{
	char	*temp;
	int		i;
	int		n;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer && buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	// printf("RM: %s\n", buffer);
	if (buffer[i] == '\0')
		return (free (buffer), NULL);
	else
		i++;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - ft_strlen(line) + 1));
	if (!temp)
		return (NULL);
	n = 0;
	while (buffer && buffer[i])
	{
		temp[n] = buffer[i];
		n++;
		i++;
	}
	temp[n] = '\0';
	free (buffer);
	// printf("TEMP: %s\n", temp);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_remove_line(buffer, line);
	return (line);
}

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *str = get_next_line(fd);
	
// 	while (str != NULL)
// 	{
// 		printf("%s\n", str);
// 		free (str);
// 		str = get_next_line(fd);
// 	}
// 	return (0);
// }