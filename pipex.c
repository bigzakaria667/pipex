/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:15:48 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/20 20:26:16 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_infile(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (perror("⚠️ Open error !"), -1);
	return (fd);
}

int	write_outfile(char *s)
{
	int	fd;

	// 0644 = PERM ONLY PROPRIO
	fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("⚠️ Write error !"), -1);
	return (fd);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char **cmd, char **envp)
{
	char	*path;
	char	*slash_cmd;
	char	**dirs;
	char	*full_path;
	int	i;

	i = 0;
	path = get_path(envp);
	dprintf(2, "PATH = %s\n", path);
	dirs = ft_split(path, ':');	
	while (dirs[i])
	{
		slash_cmd = ft_strjoin("/", cmd[0]);
		full_path = ft_strjoin(dirs[i], slash_cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_infile;
	int	fd_outfile;
	int	pipefd[2];
	pid_t	pid;
	char	**cmd;
	char	*full_path;

	if (argc != 5)
		return (1);
	else
	{
		// LECTURE ET ECRITURE
		fd_infile = read_infile(argv[1]);
		fd_outfile = write_outfile(argv[4]);
		if (fd_infile == -1 || fd_outfile == -1)
			return (1);
		// VERIF DU PIPE
		if (pipe(pipefd) == -1)
			return (perror("⚠️ Pipe error !"), 1);
		// CREATION DU FORK
		pid = fork();
		if (pid == -1)
			return (perror("⚠️ Fork error !"), 1);
		// PERMET DE CONNECTER MES FICHIERS A L'ENTREE OU LA SORTIE
		if (pid == 0)
		{
			// CMD1
			dup2(fd_infile, 0);
			dup2(pipefd[1], 1);
			// FERMETURE DES FD INUTILES
			close(fd_infile);
			close(pipefd[0]);
			close(pipefd[1]);
			// PARSER CMD1
			cmd = ft_split(argv[2], ' ');
			if (!cmd)
				return (1);
			// FIND LE PATH DU CMD
			full_path = find_cmd_path(cmd, envp);
			dprintf(2, "FULL PATH = %s\n", full_path);
			if (!full_path)
				return (perror("⚠️ Path error !"), 1);
			// EXECVE
			if (execve(full_path, cmd, envp) == -1)
				return (perror("⚠️ Execve error !"), 1);
		}
	}
	return (0);
}
