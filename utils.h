#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <cmath>
using namespace std; 

vector<int> splitLine(char * line);
vector<int> parseClustering(char * filePath);
vector<vector<float>> parseDataSet(char * fileName);
float euclidianDistance(vector<float> elemA, vector<float> elemB);

#endif 