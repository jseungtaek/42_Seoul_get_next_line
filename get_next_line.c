/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejeon <sejeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:14:53 by sejeon            #+#    #+#             */
/*   Updated: 2022/03/07 19:45:33 by sejeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

static char	*return_next_line(char **backup)
{
	char	*line;
	char	*pre_backup;
	int		index;

	index = 0;
	line = NULL;
	while ((*backup)[index] != '\n' && (*backup)[index])
		index++;
	if ((*backup)[index] == '\n')
	{
		pre_backup = *backup;
		line = ft_substr(pre_backup, 0, index + 1);
		*backup = ft_strdup(&(*backup)[index + 1]);
		return (line);
	}
	line = ft_strdup(*backup);
	ft_free(backup);
	return (line);
}

static char	*return_all(int fd, char **buf, char **backup)
{
	int		bytes;
	char	*pre_backup;

	if (!**backup)
	{
		ft_free(backup);
		return (NULL);
	}
	bytes = 1;
	while (!ft_strchr(*backup, '\n') && bytes)
	{
		bytes = read(fd, *buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			ft_free(backup);
			return (NULL);
		}
		(*buf)[bytes] = '\0';
		pre_backup = *backup;
		*backup = ft_strjoin(pre_backup, *buf);
		free(pre_backup);
	}
	return (return_next_line(backup));
}

char	*get_next_line(int fd)
{
	static char	*backup[256 + 1];
	char		*buf;
	char		*res;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (!backup[fd])
		backup[fd] = ft_strdup("");
	res = return_all(fd, &buf, &backup[fd]);
	free(buf);
	return (res);
}
