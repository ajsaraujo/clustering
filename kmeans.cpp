#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

vector<vector<float>> readInput(char *fileName) {
    FILE *INPUT = fopen(fileName, "r");

    vector<vector<float>> allElems;
    vector<float> newElem;
    char line[2000];

    while (fscanf(INPUT, "%[^\n]\n", line) != EOF) {
        char * floatNumberAsString = strtok(line, " \n");
        newElem.clear();

        while (floatNumberAsString != NULL) {
            float floatValue = atof(floatNumberAsString);
            floatNumberAsString = strtok(NULL, " \n");
            newElem.push_back(floatValue);
        }

        allElems.push_back(newElem);
    }

    return allElems;
};

int * makeRandomClustering(int numOfObjects, int numOfClusters) {
    int * labels = (int*) malloc(numOfObjects * sizeof(int));

    for (int i = 0; i < numOfObjects; i++) {
        // Assign the i-th object to a random cluster.
        labels[i] = rand() % numOfClusters;
    }

    return labels;
}

// Distance between two objects.
float euclidianDistance(vector<float> elemA, vector<float> elemB) {
    float sum = 0.0;

    for (int i = 0; i < elemA.size() && i < elemB.size(); i++) {
        sum += pow(elemA[i] - elemB[i], 2);
    }

    return sqrt(sum);
}

// Calculate distance between all pairs of objects.
float ** makeDistanceMatrix(vector<vector<float>> allElems) {
    int numOfElems = allElems.size(); 
    float ** matrix = (float**) malloc(numOfElems * sizeof(float*));

    for (int i = 0; i < numOfElems; i++) {
        matrix[i] = (float*) malloc(numOfElems * sizeof(float));
    }

    for (int i = 0; i < numOfElems; i++) {
        for (int j = i + 1; j < numOfElems; j++) {
            float dist = euclidianDistance(allElems[i], allElems[j]);
            matrix[i][j] = dist;
            matrix[j][i] = dist;
        }
    }

    return matrix;
};

// Sum of distances from centroidCandidate to all elements in cluster.
float distanceToClusterElems(int centroidCandidate, vector<int> cluster, float ** distanceMatrix) {
    float distance = 0;

    for (int u : cluster) {
        if (u == centroidCandidate) continue;
        distance += distanceMatrix[centroidCandidate][u];
    }

    return distance;
}

int calculateCenter(vector<int> cluster, float ** distanceMatrix) {
    float minimalDistance = distanceToClusterElems(cluster[0], cluster, distanceMatrix);
    int centroidCandidate = cluster[0];

    for (int i = 1; i < cluster.size(); i++) {
        float distance = distanceToClusterElems(i, cluster, distanceMatrix);

        if (distance < minimalDistance) {
            minimalDistance = distance;
            centroidCandidate = i;
        }
    }

    return centroidCandidate;
}

int * calculateAllCenters(int numOfClusters, int * labels, int numOfElems, float ** distanceMatrix) {

    // clusterElements[i] is the list of elements that belong to the i-th cluster.
    vector<vector<int>> clusterElements(numOfClusters);

    for (int i = 0; i < numOfElems; i++) {
        int clusterLabel = labels[i];
        clusterElements[clusterLabel].push_back(i);
    }

    // centers[i] is the cluster center of the i-th cluster.
    int * centers = (int*) malloc(numOfClusters * sizeof(int));
    
    for (int i = 0; i < numOfClusters; i++) {
        centers[i] = calculateCenter(clusterElements[i], distanceMatrix);
    }

    return centers;
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

vector<vector<float>> pickRandomCentroids(vector<vector<float>> objects, int numOfClusters) {
    vector<vector<float>> centroids;

    int numOfObjects = objects.size();

    // wasPicked[i] is true if the i-th object was picked as a centroid.
    bool * wasPicked = (bool*) calloc(numOfObjects, sizeof(bool));

    while (centroids.size() < numOfClusters) {
        int i = rand() % numOfObjects;

        if (wasPicked[i]) continue; 

        wasPicked[i] = true;
        centroids.push_back(objects[i]);
    }

    return centroids;
}

vector<vector<float>> computeCentroids(int * labels, vector<vector<float>> objects, int numOfClusters) {
    // This assumes every object has the same number of features.
    int numOfFeatures = objects[0].size();
    
    // A vector filled with 0s. 
    vector<float> emptyCentroid(numOfFeatures, 0.0);
    
    // centroids[i] will be the centroid for the i-th cluster.
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

FILE * openOutputFile(int numOfClusters, char * fileNamePrefix) {
    char outputFileName[100];

    sprintf(outputFileName, "%s_%d.txt", fileNamePrefix, numOfClusters);
    
    FILE * OUTPUT = fopen(outputFileName, "w");
    
    return OUTPUT;
}

void writeOutput(int * clustering, int numOfObjects, char * outputFileName, int numOfClusters) {
    FILE * OUTPUT = openOutputFile(numOfClusters, outputFileName);

    for (int i = 0; i < numOfObjects - 1; i++) {
        fprintf(OUTPUT, "%d ", clustering[i]);
    }

    fprintf(OUTPUT, "%d\n", clustering[numOfObjects - 1]);
}

int main() {
    char inputFileName[100];
    printf("What is the input file path? ");
    scanf("%s", inputFileName);

    // Pass file name with no extension. 
    // Ex: segmentation.txt WRONG!! >:(
    // Ex: segmentation_data NICE :D
    char outputFileName[100]; 
    printf("What should be the output file path? ");
    scanf("%s", outputFileName);

    // elems[i][j] is the j-th feature of the i-th object.
    printf("Reading input file...\n");
    vector<vector<float>> elems = readInput(inputFileName);
    int numOfObjects = elems.size();

    // Number of clusters that we are going to pass as an argument to K-means.
    int numOfClusters[] = { 5, 10, 15, 20, 30 }; 

    kmeans(5, elems);
    /*for (int i = 0; i < 5; i++) {
        printf("Running K-Means with k = %d...\n", numOfClusters[i]);
        int * clustering = kmeans(numOfObjects, numOfClusters[i], distances);
        writeOutput(clustering, numOfObjects, outputFileName, numOfClusters[i]);
        printf("Done!\n\n");
    }*/

    printf("Done all tasks.\n");
    return 0;
}