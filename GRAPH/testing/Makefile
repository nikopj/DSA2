useGraph.out: useGraph.o
	g++ -o useGraph.out useGraph.o graph.o heap.o hash.o

useGraph.o: useGraph.cpp graph.o
	g++ -c useGraph.cpp

graph.o: graph.cpp graph.h heap.o
	g++ -c graph.cpp

heap.o: heap.cpp heap.h hash.o
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

test: useGraph.out
	rm -f test*
	echo -e "graph.txt\nv1\ntestv1.txt" | ./useGraph.out
	diff testv1.txt outv1.txt
	echo -e "graph.txt\nv5\ntestv5.txt" | ./useGraph.out
	diff testv5.txt outv5.txt

bigtest: useGraph.out
	rm -f big_graph
	python makegraph.py
	echo -e "big_graph\nv888\ntestbig.txt" | ./useGraph.out

debug:
	g++ -g -o useGraphDebug.out useGraph.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.out *.o *.stackdump *~ test*
