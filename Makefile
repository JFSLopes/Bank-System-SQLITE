program:
	mkdir build 
	g++ -std=c++11 -Wall -o build/program source/*.cpp -lsqlite3

clean:
	@rm -rf build/