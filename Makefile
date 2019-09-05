run: bakaray testeentrada
	./bakaray h < testeentrada
bakaray: 
	g++ -O3 *.cpp -lglut -lGLU -lGL -o bakaray -fpermissive
analyzer:
	flex "analisador malha js"/bakaray-malhajs.l
	gcc lex.yy.c -o "analisador malha js"/analisadorsemiautomatico
	rm lex.yy.c
