/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:22:39 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/09 23:32:28 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error, int errnum)
{
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	exit(errnum);
}

void	execute(char *argv, char **envp)
{	
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(get_path(cmd[0], envp), cmd, envp) == -1)
		error(ft_strjoin(cmd[0], " : command not found\n"), 127);
}

char	*get_path(char *cmd, char **envp)
{
	char	**path_array;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path_array = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(tmp, cmd);
		ft_free_ptr((void **)&tmp);
		if (!access(path, F_OK))
			return (path);
		i++;
	}
	return (0);
}
