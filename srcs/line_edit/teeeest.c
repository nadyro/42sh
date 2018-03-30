#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

void    termanip(int sig)
{
	static struct termios   shell;
	static struct termios   old;

	if (sig == 0)
	{
		tcgetattr(0, &shell);
		tcgetattr(0, &old);
		shell.c_oflag &= ~(OPOST);
		shell.c_lflag &= ~(ICANON);
		shell.c_lflag &= ~(ECHO);
		shell.c_cc[VMIN] = 1;
		shell.c_cc[VTIME] = 1;
		tcsetattr(0, TCSADRAIN, &shell);
	}
	else if (sig == 2)
	{
		tcsetattr(0, TCSADRAIN, &old);
		exit(0);
	}
}

int main()
{
	char buffer[2051];
	signal(SIGINT, termanip);
	termanip(0);
	while (1)
	{
		buffer[read(1, buffer, 2050)] = '\0';
		printf("%zu\n", strlen(buffer));
		printf("%s", buffer);
		//for (int i = 0; i < 2050; i++)
		//	printf("%d=%d=%c::\n", i, (int)buffer[i], buffer[i]);
	}
}
