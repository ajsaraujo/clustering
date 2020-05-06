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

    return 0;
}