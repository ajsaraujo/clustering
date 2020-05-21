import os
from utils import getMatrixFromFile, matrixToString

def getMinAndMax(matrix):
    allMins = [min(line) for line in matrix]
    allMaxes = [max(line) for line in matrix]
    
    absoluteMin = min(allMins)
    absoluteMax = max(allMaxes)

    return [absoluteMin, absoluteMax]

def normalizeValue(value, min, maxMinusMin):
    return (value - min) / maxMinusMin

def getMinsAndMaxes(matrix):
    minsAndMaxes = [ [value, value] for value in matrix[0] ]

    for line in matrix:
        for j, value in enumerate(line):
            minsAndMaxes[j][0] = min(minsAndMaxes[j][0], value)
            minsAndMaxes[j][1] = max(minsAndMaxes[j][1], value)
    
    return minsAndMaxes

def normalizeMatrix(matrix):
    minsAndMaxes = getMinsAndMaxes(matrix)

    for i, line in enumerate(matrix):
        for j, value in enumerate(line):
            minValue, maxValue = minsAndMaxes[j]
            matrix[i][j] = normalizeValue(value, minValue, maxValue)
    
    return matrix

def makeOutputFileName(inputFileName):
    outputFileName = inputFileName.replace('.', '_normalized.', 1)

    if outputFileName == inputFileName:
        outputFileName = inputFileName + '_normalized.txt'
    
    return outputFileName

def processFile(fileName):
    inputMatrix = getMatrixFromFile(fileName)
    normalizedMatrix = normalizeMatrix(inputMatrix)
    outputMatrix = matrixToString(normalizedMatrix)
    return outputMatrix

directoryPath = input("What is the directorie's path?")

for fileName in os.listdir(directoryPath):
    if 'normalized' in fileName:
        continue

    fileName = directoryPath + '/' + fileName
    output = processFile(fileName)

    outputFileName = makeOutputFileName(fileName)

    with open(outputFileName, 'w') as file:
        file.write(output)
        file.write('\n')
