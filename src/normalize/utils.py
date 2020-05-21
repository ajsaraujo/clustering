def getMatrixFromFile(fileName):
    with open(fileName, 'r') as file:
        rawData = file.read().split('\n')
        
        # Remove whitespaces
        stringMatrix = [ elem.split(' ') for elem in rawData if elem != '']
        
        # Cast to float        
        floatMatrix = [[float(elem) for elem in line if elem != ''] for line in stringMatrix]

    return floatMatrix

def getSmallestEntryFromMatrix(matrix): 
    listOfMins = [ min(row) for row in matrix ]
    absoluteMin = min(listOfMins)
    return absoluteMin

def matrixToString(matrix):
    for i, line in enumerate(matrix):
        for j, elem in enumerate(line):
            matrix[i][j] = "%.4f" % elem

        matrix[i] = ' '.join(line)

    matrixString = '\n'.join(matrix)

    return matrixString