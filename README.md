# clustering

Clustering is the problem of partitioning a dataset in several clusters, in a way that objects in the same cluster are similar,
while objects in different clusters aren't. (this can be defined more formally with objective functions). Clustering is a 
relevant problem in several applications, such as marketing segmentation, image recognition and data compression. 

Several clustering algorithms can be found in the literature, each with it's own traits. They may have different objective functions, 
produce different clusterings, take different parameters or perform differently when facing noise or outliers. In general, no 
algorithm suits all cases, but each has it's own strengths and weaknessess, being up to the user to choose the most suitable for
his application. 

## K-Means algorithm 

K-Means is one of the most popular clustering algorithms, much probably for being one of the first algorithms proposed in the
literature and also for it's simplicity. Besides the dataset, the desired num of clusters K shall be provided. 

1. Choose k random objects as centroids for each cluster. 
2. Repeat:
    2.1 Assign each object to it's closest cluster (use centroid for comparison). 
    2.2 Recalculate the centroid for each cluster.
    2.2 If no objects were reassigned, stop. 
    
One curiosity about K-Means is that since it uses the Euclidian Distance to calculate similarity between objects, it tends to
create "circular" clusters. This can be easily noted when you visualize data in a 2D plan. 