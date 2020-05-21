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

suffixes = ['fac', 'fou', 'kar', 'mor', 'pix', 'zer']

for suffix in suffixes:
    inputFileName = 'mfeat-' + suffix 
    print(f'file: {inputFileName}')
    
    parsedFile = parseFile(inputFileName)
    print(' > Writing output... ', end = '')
    
    outputFileName = inputFileName + '-parsed'
    with open(outputFileName, 'w') as outputFile:
        outputFile.writelines(parsedFile)
    print('done!')