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
    char line[3000];

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

    // Ensures that each cluster has at least one object.
    for (int i = 0; i < numOfClusters; i++) {
        labels[i] = i;
    }

    for (int i = numOfClusters; i < numOfObjects; i++) {
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

int findClosestCluster(int elem, int * centers, int numOfClusters, int * labels, float ** distanceMatrix) {
    int closestCluster = labels[elem];
    float smallestDistance = distanceMatrix[elem][centers[closestCluster]];

    for (int i = 0; i < numOfClusters; i++) {
        int clusterCenter = centers[i];
        float distance = distanceMatrix[elem][clusterCenter];

        if (distance < smallestDistance) {
            closestCluster = i;
            smallestDistance = distance; 
        }
    }

    return closestCluster; 
}

vector<pair<int, int>> elementsThatMustBeReassigned(int numOfObjects, int * centers, int desiredNumOfClusters, int * labels, float ** distances) {
    // elems[i].first is the elem to be reassigned.
    // elems[i].second is the element's new cluster.
    vector<pair<int, int>> elems; 

    for (int i = 0; i < numOfObjects; i++) {
        int closestCluster = findClosestCluster(i, centers, desiredNumOfClusters, labels, distances);
            
        if (closestCluster != labels[i]) {
            elems.push_back({i, closestCluster});
        }
    }

    return elems;
}

int * reassignElements(int * labels, vector<pair<int, int>> elems) {
    for (auto p : elems) {
        int index = p.first;
        int newCluster = p.second;
        labels[index] = newCluster;
    }

    return labels;
}

int main() {
    int desiredNumOfClusters;
    printf("How many clusters should the final clustering have? ");
    scanf("%d", &desiredNumOfClusters);

    // elems[i][j] is the j-th feature of the i-th object.
    vector<vector<float>> elems = readInput("input.txt");
    int numOfObjects = elems.size();

    // distances[i][j] is the distance between the i-th and j-th element. 
    float ** distances = makeDistanceMatrix(elems);

    // elemLabel[i] is the cluster where the i-th element belongs.
    int * labels = makeRandomClustering(numOfObjects, desiredNumOfClusters);

    // centers[i] is the center of the i-th cluster.
    int * centers = calculateAllCenters(desiredNumOfClusters, labels, numOfObjects, distances);

    bool elementsWereReassigned = true;

    while (true) {
        vector<pair<int, int>> changingElems = elementsThatMustBeReassigned(numOfObjects, centers, desiredNumOfClusters, labels, distances);
        
        // No element must be reassigned => our job is done. 
        if (changingElems.size() == 0) break;

        labels = reassignElements(labels, changingElems);
    }

    for (int i = 0; i < numOfObjects; i++) {
        printf("%d: %d\n", i, labels[i]);
    }

    return 0;
}