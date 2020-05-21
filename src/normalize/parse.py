def removeExtraWhiteSpaces(line):
    lineWithoutSpaces = ''

    for i in range(len(line) - 1):
        if line[i] == ' ' and line[i + 1] == ' ':
            continue 
        lineWithoutSpaces += line[i]
    
    lineWithoutSpaces += line[len(line) - 1]
    return lineWithoutSpaces.strip() + '\n'

def parseFile(fileName):
    print(' > Parsing input file... ', end = '')

    with open(fileName, 'r') as inputFile:
        parsedFile = [ removeExtraWhiteSpaces(line) for line in inputFile ]
        print('done!')
        return parsedFile

inputFileName = input('What is the input file name? ')
parsedFile = parseFile(inputFileName)

print(' > Writing output... ', end = '')
outputFileName = inputFileName + '-parsed'
with open(outputFileName, 'w') as outputFile:
    outputFile.writelines(parsedFile)
print('done!')