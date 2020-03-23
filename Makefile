run: ./build/result
	./build/result

./build/result:
	g++ -o ./build/result ./src/*.cpp -lncurses -lpthread