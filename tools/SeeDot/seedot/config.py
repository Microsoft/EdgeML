# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

# Target word length. Currently set to match the word length of Arduino (2 bytes)
wordLength = 16
availableBitwidths = [8, 16, 32]

# Range of max scale factor used for exploration
maxScaleRange = 0, -wordLength

# tanh approximation limit
tanhLimit = 1.0

# MSBuild location
# Edit the path if not present at the following location
msbuildPathOptions = [r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe",
                      r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe",
                      r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe"
                      ]

# Not supported (ddsEnabled = False and vbwEnabled = True) 

# Enable Data driven scale computation. Turning this to False reverts the compiler to old verion (PLDI'19)
ddsEnabled = True

# Enable Variable BitWidth code generation. Setting this to false results in a code which uses mostly 16 bits
vbwEnabled = True

# For exponential activation functions, turning this on restricts the range of the values taken by tanH, sigmoid
# which results in a better scale assignment (OOPSLA'20 Section 5.4)
functionReducedProfiling = True

# Turning this to True restricts function profiling to those datapoints whose extrema are not in highest 10%, which
# can make scales more precise but risk running into overflows for some cases.
trimHighestDecile = False

# If true, then during exploration, a higher scale would be preferred if two or more codes have similar accuracy results
higherOffsetBias = True

# If true, the exploration iterates between Stage III and IV of the exploration to attempt to reach a global optimum
fixedPointVbwIteration = False

# Number of offsets tried out for each variable (except X, for which 9 are tried) when they are demoted to 8 bits one at a time.
offsetsPerDemotedVariable = 3

# Following classes are used sanity checks for arguments passed to the compiler, to prevent unexpected arguments being passed. 
# These lists should be updated as the compiler is expanded to multiple algorithms and datasets 

class MaximisingMetric:
    accuracy = "acc"
    disagreements = "disagree"
    reducedDisagreements = "red_disagree"
    default = [accuracy]
    all = [accuracy, disagreements, reducedDisagreements]

class Algo:
    bonsai = "bonsai"
    lenet = "lenet"
    protonn = "protonn"
    rnn = "rnn"
    rnnpool = "rnnpool"
    mbconv = "mbconv"
    test = "test"
    default = [bonsai, protonn]
    all = [bonsai, lenet, protonn, rnn, rnnpool, mbconv, test]


class Version:
    fixed = "fixed"
    floatt = "float"
    default = [fixed, floatt]
    all = default


class DatasetType:
    training = "training"
    testing = "testing"
    default = testing
    all = [training, testing]

class ProblemType:
    classification = "classification"
    regression = "regression"
    default = classification
    all = [classification, regression]

class Target:
    arduino = "arduino"
    x86 = "x86"
    m3 = "m3"
    default = x86
    all = [arduino, x86, m3]

class Source:
    seedot = "seedot"
    tf = "tf"
    onnx = "onnx"
    default = seedot
    all = [seedot, tf, onnx]