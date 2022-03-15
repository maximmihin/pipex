#include "../includes/pipex.h"

void	error_find_cmd(t_pipex *pipex, char *err)
{
//	free(pipex->cmd_args); /// это двумерный массив
	char **tmp;
	int i;

	tmp = pipex->cmd_args;
	i = 0;

	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(pipex->cmd_args);
	close(pipex->end[1]);
	close(pipex->end[0]);
	perror(err);
	exit(1);
}

char	*find_cmd(char **cmd_paths, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = ft_strjoin("/", cmd);
	while (*cmd_paths)
	{
		command = ft_strjoin(*cmd_paths, tmp);
		if (access(command, 0) == 0)
		{
			free(tmp);
			return (command);
		}
		free(command);
		cmd_paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **env)
{
	dup2(pipex.end[1], 1);
	close(pipex.end[0]);
	dup2(pipex.fd_infile,0);

	pipex.cmd_args = ft_split(argv[2], ' ');
	if (!pipex.cmd_args)
		error2("Error : failed malloc (cmd_argc)\n");
	pipex.cmd = find_cmd(pipex.cmd_paths,pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		error_find_cmd(&pipex);

	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

void	second_child(t_pipex pipex, char *argv, char **env)
{
	close(pipex.end[1]);
	dup2(pipex.end[0],0);
	dup2(pipex.fd_outfile, 1);
	pipex.cmd_args = ft_split(argv, ' ');
	if (!pipex.cmd_args)
	{
		perror("Failed malloc 2 1");
		exit(1);
	}
	pipex.cmd = find_cmd(pipex.cmd_paths,pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		//end work;
		free(pipex.cmd_args);
		close(pipex.end[1]);
		close(pipex.end[0]);
		perror("Failed malloc 2 2");
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}
