#include "utils.h"

int main() {
    DatasetAndFileName input = welcomeUserAndLoadData();

    vector<vector<float>> elems = input.dataset;
    int numOfObjects = elems.size();

    char outputFileName[100];
    strcpy(outputFileName, input.fileName);
        
    // Number of clusters that we are going to pass as an argument to K-means.
    int numOfClusters[] = { 5, 10, 15, 20, 30 }; 
}