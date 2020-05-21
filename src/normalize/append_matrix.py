import os
import utils 

def sumMatrixes(matrixA, matrixB):
    if len(matrixA) != len(matrixB):
        print(' > WARNING! Matrixes have different sizes.')
    
    numOfRows = min(len(matrixA), len(matrixB))
    for i in range(numOfRows):
        matrixA[i] += matrixB[i]
    
    return matrixA

print(' > Hello! Before we begin, let me ask you some questions: ')
directoryPath = input('   What is the directory path? ')
matrixFileName = input('   What is the first matrix file path? ')
print(' > Nice, let\'s append some matrixes!')

matrix = utils.getMatrixFromFile(matrixFileName)

for fileName in os.listdir(directoryPath):
    fileName = directoryPath + '/' + fileName
    if 'appended' in fileName or fileName == matrixFileName:
        continue
    newMatrix = utils.getMatrixFromFile(fileName)
    matrix = sumMatrixes(matrix, newMatrix)

matrixAsString = utils.matrixToString(matrix)
with open(directoryPath + '/appended', 'w') as outputFile:
    outputFile.write(matrixAsString)