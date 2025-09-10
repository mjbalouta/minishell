/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_net_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:56:00 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/26 11:56:00 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h> 
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_nstrjoin(char *s1, char *s2);
size_t	ft_nstrlen(const char *s);
void	*ft_ncalloc(size_t nmemb, size_t size);
void	ft_clean_array(char *ptr);
void	ft_free_arrays(char *result, char *line);
int		init_remain(char **remain);
char	*free_remain(char **remain);
void	initialize_memo(int *found, char **result);

#endif