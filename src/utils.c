/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:22:39 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/01 23:20:28 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{	
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(get_path(cmd[0], envp), cmd, envp) == -1)
		error("Error\nExecve error\n");
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
		free(tmp);
		if (!access(path, F_OK))
			return (path);
		i++;
	}
	return (0);
}
