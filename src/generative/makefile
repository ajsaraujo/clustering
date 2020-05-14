kmeans_out: utils.o kmeans.o
	g++ utils.o kmeans.o -o kmeans_out

tw_kmeans_out: utils.o tw_kmeans.o
	g++ utils.o tw_kmeans.o -o tw_kmeans_out 

kmeans: kmeans.cpp
	g++ -c kmeans.cpp

tw_kmeans: tw_kmeans.cpp
	g++ -c tw_kmeans.cpp

utils: utils.cpp
	g++ -c utils.cpp

clean: 
	rm *.o kmeans tw_kmeans 