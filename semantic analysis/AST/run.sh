flex ast.l 
bison -d ast.y
gcc ast.tab.c lex.yy.c ast.c -o ast -I/opt/homebrew/opt/flex/include -L/opt/homebrew/opt/flex/lib -lfl -lm
./ast input.txt