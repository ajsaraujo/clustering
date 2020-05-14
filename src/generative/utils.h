#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <cmath>
using namespace std; 

typedef struct DatasetAndFileName {
    vector<vector<float>> dataset; 
    char fileName[100];
} DatasetAndFileName; 

vector<int> splitLine(char * line);
vector<int> parseClustering(char * filePath);
vector<vector<float>> parseDataSet(char * fileName);
float euclidianDistance(vector<float> elemA, vector<float> elemB);
DatasetAndFileName welcomeUserAndLoadData();
FILE * openOutputFile(int numOfClusters, char * fileNamePrefix);
void writeOutput(int * clustering, int numOfObjects, char * outputFileName, int numOfClusters);

#endif 