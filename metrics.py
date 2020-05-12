from sklearn import metrics 

def parseClustering(path):
    with open(path, 'r') as file:
        charList = file.read().split(' ')
        integerList = [int(elem) for elem in charList]
    return integerList

expectedOutputFilePath = input('Insert expected output file path: ')
expectedClustering = parseClustering(expectedOutputFilePath)
print('File readed.')

obtainedOutputFilePath = input('Insert obtained output file path: ')
obtainedClustering = parseClustering(obtainedOutputFilePath)
print('File readed.')

ari = metrics.adjusted_rand_score(expectedClustering, obtainedClustering)
