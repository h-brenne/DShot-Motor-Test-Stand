import numpy as np

def timestampData(time, data):
        index = np.searchsorted(data, time, side="left")
        return index

def meanInterval(data, iStart, iEnd):
        intervalData= []
        for i in range(len(data)):
                if(i>iStart and i<iEnd):
                        intervalData.append(data[i])

        return np.mean(intervalData)
