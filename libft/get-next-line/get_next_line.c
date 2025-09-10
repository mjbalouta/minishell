/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/28 16:59:25 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fill_line(int bytes_read, char *buffer, char **remain, int *found)
{
	char	*line;
	int		i;
	int		z;

	i = -1;
	z = 0;
	line = ft_ncalloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (++i < bytes_read && buffer[i] != '\n' && buffer[i] != '\0')
		line[i] = buffer[i];
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		ft_clean_array(*remain);
		while (++i < bytes_read)
			(*remain)[z++] = buffer[i];
		*found = 1;
	}
	return (line);
}

char	*ft_read_and_fill(int fd, char *result, char **remain, int *found)
{
	int		bytes_read;
	char	*buffer;
	char	*line;

	buffer = ft_ncalloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (ft_free_arrays(buffer, NULL), NULL);
	if (bytes_read == 0)
	{
		free(*remain);
		*remain = NULL;
		*found = 0;
		if (!result)
		{
			free(result);
			result = NULL;
		}
		return (ft_free_arrays(buffer, NULL), result);
	}
	line = ft_fill_line(bytes_read, buffer, remain, found);
	result = ft_nstrjoin(result, line);
	return (ft_free_arrays(buffer, line), result);
}

char	*ft_fill_w_remain(char *result, char **remain, int *found)
{
	int		i;
	int		z;

	i = 0;
	z = 0;
	result = ft_ncalloc(BUFFER_SIZE + 1, sizeof(char));
	if (!result)
		return (NULL);
	while ((*remain)[i] && (*remain)[i] != '\n' && i < BUFFER_SIZE)
	{
		result[i] = (*remain)[i];
		i++;
	}
	if ((*remain)[i] == '\n')
	{
		result[i] = '\n';
		*found = 1;
		i++;
		while ((*remain)[i])
			(*remain)[z++] = (*remain)[i++];
		while (z < BUFFER_SIZE + 1)
			(*remain)[z++] = 0;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*result;
	int			found;

	if (fd == -1)
		return (free_remain(&remain));
	if (BUFFER_SIZE < 0)
		return (NULL);
	initialize_memo(&found, &result);
	if (!init_remain(&remain))
		return (NULL);
	if (remain[0])
		result = ft_fill_w_remain(result, &remain, &found);
	while (found == 2)
	{
		result = ft_read_and_fill(fd, result, &remain, &found);
		if (result == NULL)
			return (ft_free_arrays(result, NULL), free_remain(&remain));
	}
	return (result);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {	
// 	char *line;
// 	if (argc < 2)
// 		return (write(2, "Error. Missing file or input.", 29));
// 	(void)argv;
// 	// int fd = open("/dev/stdin", O_RDONLY);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	int fd = open(argv[1], O_RDONLY);
// 	while((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	if(fd >= 0)
// 		close(fd);
// 	return (0);
// }