#include "utils.h"

vector<int> splitLine(char * line) {
    char * valueAsStr = strtok(line, " \n");
    vector<int> values; 

    while (valueAsStr != NULL) {
        int integerValue = atoi(valueAsStr);
        values.push_back(integerValue);
        valueAsStr = strtok(NULL, " \n");
    }

    return values; 
}

vector<int> parseClustering(char * filePath) {
    FILE * INPUT = fopen(filePath, "r");

    char line[50000];
    fscanf(INPUT, "%[^\n]\n", line);

    vector<int> labels = splitLine(line);

    return labels; 
}

vector<vector<float>> parseDataSet(char *fileName) {
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

// Distance between two objects.
float euclidianDistance(vector<float> elemA, vector<float> elemB) {
    float sum = 0.0;

    for (int i = 0; i < elemA.size() && i < elemB.size(); i++) {
        sum += pow(elemA[i] - elemB[i], 2);
    }

    return sqrt(sum);
}