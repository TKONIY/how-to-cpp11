all: learn_map.out learn_unordered_map.out

learn_map.out: learn_map.cpp
	g++ -std=c++11 learn_map.cpp -o learn_map.out

learn_unordered_map.out: learn_unordered_map.cpp
	g++ -std=c++11 learn_unordered_map.cpp -o learn_unordered_map.out

clean:
	rm -f *.out *.o