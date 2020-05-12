import os

def getMinAndMax(matrix):
    allMins = [min(line) for line in matrix]
    allMaxes = [max(line) for line in matrix]
    
    absoluteMin = min(allMins)
    absoluteMax = max(allMaxes)

    return [absoluteMin, absoluteMax]

def normalizeValue(value, min, maxMinusMin):
    return (value - min) / maxMinusMin

def normalizeMatrix(matrix):
    smallestValue, biggestValue = getMinAndMax(matrix)
    diff = biggestValue - smallestValue

    for i, line in enumerate(matrix):
        for j, value in enumerate(line):
            matrix[i][j] = normalizeValue(value, smallestValue, diff)

    return matrix

def getMatrixFromFile(fileName):
    with open(fileName, 'r') as file:
        rawData = file.read().split('\n')
        
        # Remove whitespaces
        stringMatrix = [ elem.split(' ') for elem in rawData if elem != '']
        
        # Cast to float        
        floatMatrix = [[float(elem) for elem in line if elem != ''] for line in stringMatrix]

    return floatMatrix

def matrixToString(matrix):
    for i, line in enumerate(matrix):
        for j, elem in enumerate(line):
            matrix[i][j] = "%.4f" % elem

        matrix[i] = ' '.join(line)

    matrixString = '\n'.join(matrix)

    return matrixString

def processFile(fileName):
    inputMatrix = getMatrixFromFile(fileName)
    normalizedMatrix = normalizeMatrix(inputMatrix)
    outputMatrix = matrixToString(normalizedMatrix)
    return outputMatrix

def makeOutputFileName(inputFileName):
    outputFileName = inputFileName.replace('.', '_normalized.', 1)

    if outputFileName == inputFileName:
        outputFileName = inputFileName + '_normalized.txt'
    
    return outputFileName


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
