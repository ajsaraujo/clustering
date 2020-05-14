#include "utils.h"

int * twKmeans(int numOfClusters, vector<vector<float>> objects) {
    
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