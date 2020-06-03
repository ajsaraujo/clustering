from numpy import array

def matrixToNumpyMatrix(matrix):
    listOfArrays = [array(row) for row in matrix]
    numpy2DArray = array(listOfArrays)
    print(f' > dtype = {numpy2DArray.dtype}')
    return numpy2DArray

def getMatrixFromFile(fileName, transformToNumpy = True):
    with open(fileName, 'r') as file:
        rawData = file.read().split('\n')
        
        # Remove whitespaces
        stringMatrix = [ elem.split(' ') for elem in rawData if elem != '']
        
        # Cast to float        
        floatMatrix = [[float(elem) for elem in line if elem != ''] for line in stringMatrix]

    if transformToNumpy:
        numpyMatrix = matrixToNumpyMatrix(floatMatrix)
        return numpyMatrix
    else:
        return floatMatrix