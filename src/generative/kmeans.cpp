#include <cstdlib>
#include "utils.h"

using namespace std;

int * makeRandomClustering(int numOfObjects, int numOfClusters) {
    int * labels = (int*) malloc(numOfObjects * sizeof(int));

    for (int i = 0; i < numOfObjects; i++) {
        // Assign the i-th object to a random cluster.
        labels[i] = rand() % numOfClusters;
    }

    return labels;
}

int findClosestCluster(vector<float> object, vector<vector<float>> centroids) {
    int closestCluster = 0;
    float smallestDistance = euclidianDistance(object, centroids[0]);

    int numOfClusters = centroids.size();
    for (int i = 0; i < numOfClusters; i++) {
        float distance = euclidianDistance(object, centroids[i]);

        if (distance < smallestDistance) {
            closestCluster = i;
            smallestDistance = distance; 
        }
    }

    return closestCluster; 
}

vector<pair<int, int>> objectsInTheWrongCluster(int * labels, vector<vector<float>> centroids, vector<vector<float>> objects) {
    // elems[i].first is the elem to be reassigned.
    // elems[i].second is the element's new cluster.
    vector<pair<int, int>> toReassign; 

    int numOfObjects = objects.size();

    for (int i = 0; i < numOfObjects; i++) {
        int closestCluster = findClosestCluster(objects[i], centroids);

        if (closestCluster != labels[i]) {
            toReassign.push_back({i, closestCluster});
        }
    }

    return toReassign;
}

int * reassignElements(int * labels, vector<pair<int, int>> elems) {
    for (auto p : elems) {
        int index = p.first;
        int newCluster = p.second;
        labels[index] = newCluster;
    }

    return labels;
}

vector<vector<float>> computeCentroids(int * labels, vector<vector<float>> objects, int numOfClusters) {
    int numOfFeatures = objects[0].size();

    for (int i = 1; i < objects.size(); i++) {
        if (objects[i].size() > numOfFeatures) {
            numOfFeatures = objects[i].size();
        }
    }    

    vector<float> emptyCentroid(numOfFeatures, 0.0);    
    vector<vector<float>> centroids(numOfClusters, emptyCentroid);

    // objectsInCluster[i] is the number of objects in the i-th cluster.
    int * objectsInCluster = (int*) calloc(numOfClusters, sizeof(int));

    int numOfObjects = objects.size();

    // Sum all values.
    for (int i = 0; i < numOfObjects; i++) {
        int cluster = labels[i];
        objectsInCluster[cluster]++;

        for (int j = 0; j < objects[i].size(); j++) {
            centroids[cluster][j] += objects[i][j];
        }
    }

    // Divide them to obtain the mean.
    for (int i = 0; i < numOfClusters; i++) {
        for (int j = 0; j < centroids[i].size(); j++) {
            centroids[i][j] /= objectsInCluster[i];
        }
    }

    return centroids;
}

int * kmeans(int numOfClusters, vector<vector<float>> objects) {
    int numOfObjects = objects.size();
    
    // elemLabel[i] is the cluster where the i-th element belongs.
    int * labels = makeRandomClustering(numOfObjects, numOfClusters);

    vector<vector<float>> centroids = pickRandomCentroids(objects, numOfClusters);

    while (true) {
        vector<pair<int, int>> objectsToReassign = objectsInTheWrongCluster(labels, centroids, objects);
        
        // No element must be reassigned => our job is done. 
        if (objectsToReassign.size() == 0) break;

        labels = reassignElements(labels, objectsToReassign);

        centroids = computeCentroids(labels, objects, numOfClusters);
    }

    return labels; 
}

int main() {
    DatasetAndFileName input = welcomeUserAndLoadData();

    vector<vector<float>> elems = input.dataset;
    int numOfObjects = elems.size();

    char outputFileName[100];
    strcpy(outputFileName, input.fileName);
        
    // runs[i] is the number of clusters for the i-th run of k-means.
    vector<int> runs = { 7, 10 };
    
    for (int numOfClusters : runs) {
        printf("Running K-Means with k = %d...\n", numOfClusters);
        int * clustering = kmeans(numOfClusters, elems);
        writeOutput(clustering, numOfObjects, outputFileName, numOfClusters);
        printf("Done!\n\n");
    }

    printf("All tasks done.\n");
    return 0;
}