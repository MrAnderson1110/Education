import maiLib as ml

# ---- calcMaiPlus
def calcMaiPlus(C, ALevels):
    CAMainMat = ml.getACMainMat(C, ALevels);
    CMat = ml.getCMat(C);
    CW = ml.getW(CMat);
    CWn = ml.getWn(CW);

    BSArr = [];
    for i in range(len(C)):
        CAMat = ml.getAnyCAMat(CAMainMat, i);
        CAW = ml.getW(CAMat);
        CAWn = ml.getWn(CAW);
        BS = ml.getAnyBS(CAWn);
        BSArr.append(BS);
        
    B = ml.getB(BSArr, CWn);
    BWn = ml.getBWn(B);
    return BWn;
# ----

# ---- calcMai
def calcMai(C, ALevels):
    CAMainMat = ml.getACMainMat(C, ALevels);
    CMat = ml.getCMat(C);
    CW = ml.getW(CMat);
    CWn = ml.getWn(CW);

    CAWnArr = [];
    for i in range(len(C)):
        CAMat = ml.getAnyCAMat(CAMainMat, i);
        CAW = ml.getW(CAMat);
        CAWn = ml.getWn(CAW);
        CAWnArr.append(CAWn);

    WFull = ml.getFullW(CWn, CAWnArr)    
    print('Mai L:', ml.getL(CMat, [CWn]));
    return WFull;
# ----

# ---- getAns
def getAns(MAI):
    ans = 0;
    for i in range(0, len(MAI)):
        if MAI[i] > MAI[ans]:
            ans = i;
    return ans;
# ----

# ---- main
ALevels = [
    [0.001, 0.2,   0.8],
    [1.0,   0.001, 0.2],
    [0.2,   0.001, 0.5]
];
ALevelsPlus = [
    [0.001, 0.2,   0.8, 0.001],
    [1.0,   0.001, 0.2, 0.5  ],
    [0.2,   0.001, 0.5, 0.2  ]
];

# a)

C = [0.4, 0.2, 0.3];

MAI = calcMai(C, ALevels);
print('a) Mai Wns:', MAI);
print('a) MAI ans:', getAns(MAI) + 1);
print('----')

MAIWithAPlus = calcMai(C, ALevelsPlus);
print('a) Mai with ALevels+ Wns:', MAIWithAPlus);
print('a) Mai with ALevels+ ans:', getAns(MAIWithAPlus) + 1);
print('----')

MAIPlus = calcMaiPlus(C, ALevelsPlus);
print('a) Mai+ Wns:', MAIPlus);
print('a) Mai+ ans:', getAns(MAIPlus) + 1);
print('----')
print('\n');


# б)

C = [0.3, 0.3, 0.4];

MAI = calcMai(C, ALevels);
print('б) Mai Wns:', MAI);
print('б) MAI ans:', getAns(MAI) + 1);
print('----')

MAIWithAPlus = calcMai(C, ALevelsPlus);
print('б) Mai with ALevels+ Wns:', MAIWithAPlus);
print('б) Mai with ALevels+ ans:', getAns(MAIWithAPlus) + 1);
print('----')

MAIPlus = calcMaiPlus(C, ALevelsPlus);
print('б) Mai+ Wns:', MAIPlus);
print('б) Mai+ ans:', getAns(MAIPlus) + 1);
print('----')
print('\n');


# в)

C = [0.2, 0.5, 0.3];

MAI = calcMai(C, ALevels);
print('в) Mai Wns:', MAI);
print('в) MAI ans:', getAns(MAI) + 1);
print('----')

MAIWithAPlus = calcMai(C, ALevelsPlus);
print('в) Mai with ALevels+ Wns:', MAIWithAPlus);
print('в) Mai with ALevels+ ans:', getAns(MAIWithAPlus) + 1);
print('----')

MAIPlus = calcMaiPlus(C, ALevelsPlus);
print('в) Mai+ Wns:', MAIPlus);
print('в) Mai+ ans:', getAns(MAIPlus) + 1);
print('----')
# ----