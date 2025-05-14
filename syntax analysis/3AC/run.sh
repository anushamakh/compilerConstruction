flex file.l 
bison -d file.y
gcc file.tab.c lex.yy.c -o file -I/opt/homebrew/opt/flex/include -L/opt/homebrew/opt/flex/lib -lfl -lm
./file input.txt