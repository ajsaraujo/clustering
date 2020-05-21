import utils 

print(' > Before we begin, please answer the following questions:')
inputFileName = input('What is the input file name? ')

print(' > Nice! Reading input file... ', end = '')
matrix = utils.getMatrixFromFile(inputFileName)
print('done!')

print(' > Searching smallest value... ', end = '')
smallestValue = abs(utils.getSmallestEntryFromMatrix(matrix))
print('found!')

matrix = [ [ elem + smallestValue for elem in row] for row in matrix ]

outputFileName = inputFileName + '-positive'
with open(outputFileName, 'w') as file:
    output = utils.matrixToString(matrix)
    print(' > Writing output... ', end = '')
    file.write(output)
    print('done!')