all:
	gcc -g -fsanitize=address -fno-omit-frame-pointer main.c lexer.c ../../libft/ft_strlen.c ../../libft/ft_putstr_fd.c ../../libft/ft_putstr.c ../../libft/ft_memset.c ../parser/parser.c -I../../include

clean:
	rm a.out
	rm -rf a.out.dSYM
	
re: clean all
