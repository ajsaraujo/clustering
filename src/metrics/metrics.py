from sklearn import metrics 
from utils import getMatrixFromFile

def parseClustering(path):
    with open(path, 'r') as file:
        charList = file.read().split(' ')
        integerList = [int(elem) for elem in charList]
    return integerList

def tryToReadFile(path, fileType):
    if fileType == 'clustering':
        data = parseClustering(path)
    else:
        data = getMatrixFromFile(path)
    return data

def readInputFile(title, fileType):
    while True:
        path = input(f'Insert {title} file path: ')
        print('Reading file... ', end='')
        
        try:
            data = tryToReadFile(path, fileType)
            print('done.')
            return data 
        except:
            print('''Oops. It seems like the file you're trying to read 
                     doesn't exist. Please try again.''')

dataset = readInputFile('dataset', 'dataset')
expectedClustering = readInputFile('expected output', 'clustering')
obtainedClustering = readInputFile('obtained output', 'clustering')

print('Calculating metrics... ', end='')
ari = metrics.adjusted_rand_score(expectedClustering, obtainedClustering)
sillhouete = metrics.silhouette_score(dataset, expectedClustering, metric='euclidean')
fMeasure = metrics.f1_score(expectedClustering, obtainedClustering, average='micro')
print('done.')

print(f'ARI: {ari:.4f}')
print(f'SILLHOUETE: {sillhouete:.4f}')
print(f'F-MEASURE: {fMeasure:.4f}')