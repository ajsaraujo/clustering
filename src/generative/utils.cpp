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

DatasetAndFileName welcomeUserAndLoadData() {
    char inputFileName[100], outputFileName[100];

    printf("Hello!\n\n"); 

    printf("What is the input file path? ");
    scanf("%s", inputFileName);

    // elems[i][j] is the j-th feature of the i-th object.
    printf("Reading input file...\n");
    vector<vector<float>> dataset = parseDataSet(inputFileName);
    printf("done!\n\n");

    // Pass file name with no extension. 
    // Ex: segmentation.txt WRONG!! >:(
    // Ex: segmentation_data NICE :D
    printf("What should be the output file path? ");
    scanf("%s", outputFileName);

    DatasetAndFileName output; 
    output.dataset = dataset;
    strcpy(output.fileName, outputFileName);
    
    return output;
}

// Distance between two objects.
float euclidianDistance(vector<float> elemA, vector<float> elemB) {
    float sum = 0.0;

    for (int i = 0; i < elemA.size() && i < elemB.size(); i++) {
        sum += pow(elemA[i] - elemB[i], 2);
    }

    return sqrt(sum);
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