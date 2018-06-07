all:
	gcc -g -fsanitize=address -fno-omit-frame-pointer main.c lexer.c ../../libft/ft_strlen.c ../../libft/ft_strndup.c ../../libft/ft_strchr.c ../../libft/ft_strdup.c ../../libft/ft_strjoin.c ../../libft/ft_strstr.c ../../libft/ft_putstr_fd.c ../../libft/ft_strcat.c ../../libft/ft_strcpy.c ../../libft/ft_putstr.c ../../libft/ft_memset.c ../parser/parser.c ../parser/ast.c -I../../include

clean:
	rm a.out
	rm -rf a.out.dSYM
	
re: clean all
