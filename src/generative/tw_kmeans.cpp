#include "utils.h"

float * initializeWeightArray(int arraySize, float weight) {
    float * arr = (float*) calloc(arraySize, sizeof(float));

    for (int i = 0; i < arraySize; i++) {
        arr[i] = weight;
    }

    return arr;
}

int * twKmeans(int numOfClusters, int numOfViews, vector<vector<float>> objects) {
    float initialViewWeight = 1.0 / numOfViews;
    float * viewWeight = initializeWeightArray(numOfViews, initialViewWeight);

    // This assumes every object has the exact same number of features.
    int numOfVariables = objects[0].size();
    float initialVariableWeight = 1.0 / numOfVariables;
    float * variableWeight = initializeWeightArray(numOfVariables, initialVariableWeight);

    
}

int main() {
    DatasetAndFileName input = welcomeUserAndLoadData();

    vector<vector<float>> elems = input.dataset;
    int numOfObjects = elems.size();

    char outputFileName[100];
    strcpy(outputFileName, input.fileName);
        
    // Number of clusters that we are going to pass as an argument to K-means.
    vector<int> numOfClusters = { 5, 10, 15, 20, 30 };
    int numOfRuns = numOfClusters.size(); 

    for (int i = 0; i < numOfRuns; i++) {
        printf("Running TW-k-means with k = %d... ", numOfClusters[i]);
        int * clustering = twKmeans(numOfClusters[i], elems);
        printf("done!\n");
        printf("Writing output to file... ");
        writeOutput(clustering, numOfObjects, outputFileName, numOfClusters[i]);
        printf("done!\n\n");
    }
}