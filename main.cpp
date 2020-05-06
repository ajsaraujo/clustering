#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <vector> 
using namespace std; 

vector<vector<float>> readInput(char * fileName) {
    FILE * INPUT = fopen(fileName, "r");

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

int main() {
    // elems[i][j] is the j-th feature of the i-th object
    vector<vector<float>> elems = readInput("input.txt");

    return 0;
}