# clustering

Clustering is the problem of partitioning a dataset in several clusters, in a way that objects in the same cluster are similar, while objects in different clusters aren't. Clustering algorithms are widely used to classify data and are extremely
relevant  problem in several applications, such as marketing segmentation, image recognition and data compression.  

## Installation and usage 

To compile the project, you'll need G++.

1. At `generative/`, run `make kmeans_out` to build `kmeans.cpp` and it's dependencies.
2. Execute the program with `./kmeans.out` if you're on Linux. 
3. You will be prompted for input and output file paths. The input file should contain a matrix representing the dataset, with columns being separated by whitespaces and lines being separated by linefeeds. The output path can be whatever you want, it will just be the prefix for the output files. 
4. The program will produce files containing clusterings with 5, 10, 15, 20 and 30 clusters each. If you want to modify the number of clusters in each run you just have to update the `numOfClusters[]` array in `kmeans.cpp`. 

## Algorithm descriptions 

### K-Means algorithm 

K-Means is one of the most popular clustering algorithms, much probably for being one of the first algorithms proposed in the literature and also for it's simplicity. Besides the dataset, the desired number of clusters (k) shall be provided. 

1. Choose k random objects as centroids for each cluster. 
2. Repeat:
     1. Assign each object to the cluster of it's closest centroid.
     2. Recalculate the centroid for each cluster. (The centroid is the mean of all objects in a cluster). 
     3. If no objects were reassigned, stop. 
    
One curiosity about K-Means is that since it uses the Euclidian Distance to calculate similarity between objects, it tends to
create "circular" clusters. This can be easily noted when you visualize data in a 2D plan. 
