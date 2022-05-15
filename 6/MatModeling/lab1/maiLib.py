import numpy as np;
from statistics import geometric_mean

# ---- getAnyBS
def getAnyBS(CWn):
    dim = len(CWn);
    BSMat = np.matrix(np.arange(dim * dim * 2).reshape((dim, dim * 2)), dtype = 'float');
    BSArr = BSMat.getA();
    for i in range(0, dim):
        for j in range(0, dim * 2):
            leftIns = CWn[int(j / 2)];
            rightIns = CWn[i];
            if (j % 2):
                inserted = leftIns / (leftIns + rightIns);
            else: 
                inserted = rightIns / (leftIns + rightIns);

            
            BSArr[i][j] = inserted;
    return BSMat;            
# ----

# ---- getB
def getB(AllBArr, CWn):
    BCount = len(AllBArr);
    rowCount = len(AllBArr[0].getA());
    colCount = len(AllBArr[0].getA()[0]);
    ret = np.matrix(np.arange(rowCount * colCount).reshape(rowCount, colCount), dtype = 'float');
    retArr = ret.getA();
    CWnMat = np.matrix(CWn);
    for i in range(rowCount):
        for j in range(colCount):
            BSMat = np.matrix(np.arange(BCount).reshape(BCount, 1), dtype = 'float');
            BSArr = BSMat.getA();
            for bi in range(BCount):
                BSArr[bi][0] = AllBArr[bi].getA()[i][j];
            retArr[i][j] = np.matmul(CWnMat, BSMat);
    return (ret);
# ----

# ----
def getL(C, Wn):
    CArr = C.getA();
    CSums = np.matrix(np.arange(len(CArr[0])).reshape(len(CArr[0]), 1), dtype = 'float');
    CSums.fill(0);
    CSumsArr = CSums.getA();

    for i in range(len(CArr)):
        for j in range(len(CArr[0])):
            CSumsArr[j] += CArr[i][j];
    return np.matmul(Wn, CSums);
# ----

# ---- getBWn
def getBWn(B):
    BArr = B.getA();
    W = [];
    for i in range(len(BArr)):
        W.append(0);

    for i in range(len(BArr)):
        for j in range(len(BArr[0])):
            if j % 2:
                continue;
            W[i] += BArr[i][j];
    WSum = np.sum(W);
    Wn = [];
    for i in range(len(W)):
        Wn.append(W[i] / WSum);

    return Wn;                    
# ----

# ---- getCMat
def getCMat(CArray):
    size = len(CArray);
    CMat = np.matrix(np.arange(size * size).reshape((size, size)), dtype = 'float');
    CMatArrays = CMat.getA();
    for i in range(0, size):
        for j in range(0, size):
            CMatArrays[i][j] = CArray[i] / CArray[j];
    return CMat;
# ----

# ---- getACMainMat
def getACMainMat(CArray, ALevels):
    ACols = len(ALevels[0]);
    CSize = len(CArray);
    CAMainMat = np.matrix(np.arange(CSize * ACols).reshape(CSize, ACols), dtype = 'float');
    CAMainArrays = CAMainMat.getA();
    for i in range(0, CSize):
        for j in range(0, ACols):
            CAMainArrays[i][j] = ALevels[i][j] * CArray[i];
    return CAMainMat;
# ----

# ---- getW
def getW(Mat):
    Arrays = Mat.getA();
    ret = []
    for i in range(0, len(Arrays)):
        ret.append(geometric_mean(Arrays[i]))

    return ret;
# ----

# ---- getWn
def getWn(W):
    ret = [];
    sum = np.sum(W);
    for i in range(0, len(W)):
        ret.append(W[i] / sum);
    return ret;
# ----

# ---- getAnyCAMat
def getAnyCAMat(CAMainMat, CIndex):
    CAMainMatArr = CAMainMat.getA();
    CACount = len(CAMainMatArr[0]);
    CARows = len(CAMainMatArr);
    CAAnyMat = np.matrix(np.arange(CACount * CACount).reshape(CACount, CACount), dtype = 'float');
    CAAnyMat.fill(0);
    CAAnyMatArr = CAAnyMat.getA();
    for i in range(0, CACount):
        for j in range(0, CACount):
            CAAnyMatArr[i][j] = CAMainMatArr[CIndex][i] / CAMainMatArr[CIndex][j];
    return CAAnyMat;
# ----

# ---- getFullW
def getFullW(CWn, CWArrays):
    dim = len(CWn);
    CWnMat = np.matrix(CWn);
    CAWnMat = np.matrix(CWArrays);
    return np.matmul(CWnMat, CAWnMat).getA()[0];
# ----