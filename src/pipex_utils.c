/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:42:50 by armitite          #+#    #+#             */
/*   Updated: 2024/09/15 19:54:02 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	files_error(char **av, int c)
{
	if (c == 0)
	{
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(1);
	}
}

int	files_function(char **av, int c)
{
	int		outfile;
	int		infile;

	if (c == 1)
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			return (files_error(av, 0), 0);
		return (infile);
	}
	if (c == 2)
	{
		outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (outfile == -1)
			return (0);
		return (outfile);
	}
	return (0);
}

void	pid_exec1(int infile, int fd[2], char **av, char **envp)
{
	char	*filename1;
	char	**av1;

	av1 = ft_split(av[2], ' ');
	filename1 = get_paths(av1[0], envp, av, 1);
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	close(infile);
	if (execve(filename1, av1, envp) == -1)
	{
		free(filename1);
		ft_free(av1);
	}
}

void	pid_exec2(int outfile, int fd[2], char **envp, char **av)
{
	char	*filename2;
	char	**av2;

	av2 = ft_split(av[3], ' ');
	filename2 = get_paths(av2[0], envp, av, 2);
	dup2(fd[0], 0);
	dup2(outfile, 1);
	close(fd[1]);
	close(fd[0]);
	close(outfile);
	if (execve(filename2, av2, envp) == -1)
	{
		free(filename2);
		ft_free(av2);
	}
}

int	exec_commands(char **envp, char **av)
{
	int		fd[2];
	int		pid;
	int		pid2;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (close(fd[1]), close(fd[0]), 2);
	if (pid == 0)
		pid_exec1(files_function(av, 1), fd, av, envp);
	pid2 = fork();
	if (pid2 < 0)
		return (close(fd[1]), close(fd[0]), 2);
	if (pid2 == 0)
		pid_exec2(files_function(av, 2), fd, envp, av);
	close(fd[0]);
	close(fd[1]);
	while (!waitpid(pid, NULL, 0) || !waitpid(pid2, NULL, 0))
		;
	return (0);
}
