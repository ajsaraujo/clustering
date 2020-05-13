def getMatrixFromFile(fileName):
    with open(fileName, 'r') as file:
        rawData = file.read().split('\n')
        
        # Remove whitespaces
        stringMatrix = [ elem.split(' ') for elem in rawData if elem != '']
        
        # Cast to float        
        floatMatrix = [[float(elem) for elem in line if elem != ''] for line in stringMatrix]

    return floatMatrix