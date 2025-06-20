/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:32:00 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/20 20:53:05 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (!slash_cmd)
			return (NULL);
		full_path = ft_strjoin(dirs[i], slash_cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	cmd1(int fd_infile, int fd_outfile, int *pipefd)
{
	// PERMET DE CONNECTER MES FICHIERS A L'ENTREE OU A LA SORTIE
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
