build:
	g++ -Wall ./src/*.cpp -o compiler
run:
	./compiler
clean:
	rm compiler