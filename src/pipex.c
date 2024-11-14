/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:57:57 by armitite          #+#    #+#             */
/*   Updated: 2024/09/11 16:01:15 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*ft_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*access_check(char *av, char **allpaths)
{
	int		i;
	char	*joinpaths;
	char	*tmp;

	i = 0;
	if (!av)
		return (NULL);
	if (access(av, X_OK) == 0)
		return (av);
	while (allpaths[i])
	{
		joinpaths = ft_strjoin(allpaths[i], "/");
		tmp = joinpaths;
		joinpaths = ft_strjoin(joinpaths, av);
		free(tmp);
		if (access(joinpaths, X_OK) == 0)
			return (joinpaths);
		i++;
		free(joinpaths);
	}
	ft_free(allpaths);
	return (NULL);
}

char	*get_paths(char *avh, char **envp, char **av, int i)
{
	char	*path1;
	char	*path;
	char	**allpaths;

	path = ft_path(envp);
	path = ft_strchr(path, '/');
	allpaths = ft_split(path, ':');
	path1 = access_check(avh, allpaths);
	if (path1 == NULL)
	{
		if (i == 1)
			allpaths = ft_split(av[2], ' ');
		if (i == 2)
			allpaths = ft_split(av[3], ' ');
		return (ft_putstr_fd(allpaths[0], 2),
			ft_putendl_fd(": command not found", 2), ft_free(allpaths), NULL);
	}
	ft_free(allpaths);
	return (path1);
}

int	main(int ac, char **av, char **envp)
{
	if (ac == 5)
		exec_commands(envp, av);
	else
		return (write(1, "Error\n", 6), 1);
}
