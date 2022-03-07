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

static void ft_free(char **str)
{
    while (*str)
    {
        free(*str);
        *str = NULL;
    }
}

static char all_return(int fd, char **buf, char **backup, int bytes)
{

}

char	get_next_line(int fd)
{
    static char	*backup[OPEN_MAX + 1];
    char		*buf;
    char		*res;
    int         bytes;
    
    if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
        return (NULL);
    buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    if (!backup[fd])
        *backup = ft_strdup("");
}