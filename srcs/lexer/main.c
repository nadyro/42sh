#include "lexer.h"
#include <stdio.h>

int				main(int argc, char **argv)
{
	int *tab;
	int i = 0;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		tab = get_tokens(argv[1]);
		while (tab[i] != -1)
		{
			switch(tab[i])
			{
				case TK_WORD:
					printf("WORD ");
					break;
				case TK_NEWLINE:
					printf("NEWLINE ");
					break;
				case TK_IO_NUMBER:
					printf("IO_NUMBER ");
					break;
				case TK_GREAT:
					printf("GREAT ");
					break;
				case TK_DGREAT:
					printf("DGREAT ");
					break;
				case TK_GREATAND:
					printf("GREATAND ");
					break;
				case TK_LESS:
					printf("LESS ");
					break;
				case TK_DLESS:
					printf("DLESS ");
					break;
				case TK_LESSAND:
					printf("LESSAND ");
					break;
				case TK_PIPE:
					printf("PIPE ");
					break;
				case TK_SEMI:
					printf("SEMI ");
					break;
				case TK_COMMENT:
					printf("COMMENT ");
					break;
				//case TK_SPACE:
				//	printf("SPACE ");
				//	break;
				case TK_AND:
					printf("AND ");
					break;
				case TK_AND_IF:
					printf("AND_IF ");
					break;
				case TK_OR_IF:
					printf("OR_IF ");
					break;
				case TK_END:
					printf("END ");
					break;
			}
			i += 3;
		}
		printf("\n");
	}
	return (0);
}
