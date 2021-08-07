all: learn_map.out learn_unordered_map.out learn_observer.out

learn_map.out: src/learn_map.cpp
	g++ -std=c++11 src/learn_map.cpp -o learn_map.out

learn_unordered_map.out: src/learn_unordered_map.cpp
	g++ -std=c++11 src/learn_unordered_map.cpp -o learn_unordered_map.out

learn_observer.out: src/learn_observer.cpp
	g++ -std=c++11 src/learn_observer.cpp -o learn_observer.out

clean:
	rm -f *.out *.o