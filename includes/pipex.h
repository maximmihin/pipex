#ifndef PIPEX_PIPEX_H
# define PIPEX_PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	char	**cmd_paths;
	char	*cmd;
	char 	**cmd_args;
	int		end[2];
	int		pid_id_first;
	int 	pid_id_second;

} t_pipex;

size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);


void	first_child(t_pipex pipex, char **argv, char **env);
void	second_child(t_pipex pipex, char *argv, char **env);


#endif //PIPEX_PIPEX_H