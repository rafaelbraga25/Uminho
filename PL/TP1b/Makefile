V=parser
$V: $V.fl
	flex $V.fl
	cc -g lex.yy.c -o $V `pkg-config --cflags --libs glib-2.0`
clean:
	rm lex.yy.c $V
