from sklearn import metrics
from sklearn.cluster import KMeans
from numpy import array
from utils import getMatrixFromFile

def parseClustering(path):
    with open(path, 'r') as file:
        charList = file.read().split(' ')
        integerList = [int(elem) for elem in charList]
    return array(integerList)

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
        except Exception as e:
            print(e)
            print("Oops. It seems like the file you're trying to read doesn't exist. Please try again.")

def bench_k_means(estimator, name, data, expectedClustering):
    print(' > Clustering... ', end='')
    estimator.fit(data)
    print('done.')
    print(f' > Benchmarking {name}:')
    print(f'    SILHUETA:  {metrics.silhouette_score(data, expectedClustering, metric="euclidean"):.4f}')
    print(f'    ARI:       {metrics.adjusted_rand_score(expectedClustering, estimator.labels_):.4f}')
    print(f'    F-MEASURE: {metrics.f1_score(expectedClustering, estimator.labels_, average="macro"):.4f}')
    print('\n\n')

dataset = readInputFile('dataset', 'dataset')
obtainedClustering = readInputFile('obtained output', 'clustering')
expectedNumOfClusters = int(input('What is the expected number of clusters? '))

# The datasets are organized in a way such that an object's cluster in the 
# reference clustering can be calculated by i / k, where i is it's index 
# and k is the number of clusters.
numOfObjects = len(dataset)
objectsPerCluster = numOfObjects // expectedNumOfClusters
expectedClusteringAsList = [ i // objectsPerCluster for i in range(numOfObjects)]
expectedClustering = array(expectedClusteringAsList)

optimizedKMeans = KMeans(init='k-means++', n_clusters=expectedNumOfClusters)
randomKMeans = KMeans(init='random', n_clusters=expectedNumOfClusters)

# Uncomment this to bench Scikit-learn's K-Means.
#bench_k_means(optimizedKMeans, 'OPTIMIZED', dataset, expectedClustering)
#bench_k_means(randomKMeans, 'RANDOM', dataset, expectedClustering)

print(' > Calculating metrics... ', end='')
ari = metrics.adjusted_rand_score(expectedClustering, obtainedClustering)
sillhouete = metrics.silhouette_score(dataset, expectedClustering, metric='euclidean')
fMeasureMicro = metrics.f1_score(expectedClustering, obtainedClustering, average='micro')
fMeasureMacro = metrics.f1_score(expectedClustering, obtainedClustering, average='macro')
fMeasureWeighted = metrics.f1_score(expectedClustering, obtainedClustering, average='weighted')
fMeasureSamples = metrics.f1_score(expectedClustering, obtainedClustering, average='samples')

print('done.')

print(f'ARI: {ari:.4f}')
print(f'SILLHOUETE: {sillhouete:.4f}')
print(f'Micro: {fMeasureMicro:.4f}')
print(f'Macro: {fMeasureMacro:.4f}')
print(f'Weighted: {fMeasureWeighted:.4f}')
print(f'Samples: {fMeasureSamples:.4f}')
