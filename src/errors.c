#include "../includes/pipex.h"

int		msg_error1(char *err)
{
	size_t 	len;

	len = ft_strlen(err);
	write(2, err, len);
	return (1);
}

void 	msg_error2(char *err)
{
	perror(err);
	exit(1);
}
