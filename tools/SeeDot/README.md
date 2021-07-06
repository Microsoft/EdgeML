# SeeDot

SeeDot is an automatic quantization tool that generates efficient machine learning (ML) inference code for IoT devices.

### **Overview**

ML models are usually expressed in floating-point, and IoT devices typically lack hardware support for floating-point arithmetic. Hence, running such ML models on IoT devices involves simulating floating-point arithmetic in software, which is very inefficient. SeeDot addresses this issue by generating fixed-point code with only integer operations. To enable this, SeeDot takes as input trained floating-point models (like [Bonsai](https://github.com/microsoft/EdgeML/blob/master/docs/publications/Bonsai.pdf) or [ProtoNN](https://github.com/microsoft/EdgeML/blob/master/docs/publications/ProtoNN.pdf) or [FastGRNN](https://github.com/microsoft/EdgeML/blob/master/docs/publications/FastGRNN.pdf)) and generates efficient fixed-point code that can run on microcontrollers. The SeeDot compiler uses novel compilation techniques to automatically infer certain parameters used in the fixed-point code, optimized exponentiation computation, etc. With these techniques, the generated fixed-point code has comparable classification accuracy and performs significantly faster than the floating-point code.

To know more about SeeDot, please refer to our publications [here](https://www.microsoft.com/en-us/research/publication/compiling-kb-sized-machine-learning-models-to-constrained-hardware/) and [here](https://www.microsoft.com/en-us/research/publication/shiftry-rnn-inference-in-2kb-of-ram/).

This document describes the tool usage with an example.

### **Software requirements**

1. [**Python 3**](https://www.python.org/) with following packages:
   - **[Antrl4](http://www.antlr.org/)** (antlr4-python3-runtime; tested with version 4.7.2)
   - **[Numpy](http://www.numpy.org/)** (tested with version 1.16.4)
   - **[Scikit-learn](https://scikit-learn.org/)** (tested with version 0.21.2)
   - **[Bokeh](https://bokeh.org/)** (tested with version 2.1.1)
2. Linux packages:
   - **[gcc](https://www.gnu.org/software/gcc/)** (tested with version 9.3.0)
   - **[make](https://www.gnu.org/software/make/)** (tested with version 4.2.1)

### **Usage**

SeeDot can be invoked using **`SeeDot-dev.py`** file. The arguments for the script are supplied as follows:

```
usage: SeeDot-dev.py [-h] [-a] [-v] [-d] [-m] [-n] [-dt] [-t] [-s] [-sf]
                     [--load-sf] [--convert] [--tempdir] [-o] [--driver]

optional arguments:
  -h, --help            Show this help message and exit
  -a , --algo           Algorithm to run ['bonsai' or 'protonn' or 'fastgrnn']
  -v , --version        Floating-point ['float'] or fixed-point ['fixed']
  -d , --dataset        Dataset to use
  -m , --maximisingMetric ['acc', 'disagree', 'red_disagree']
                        What metric to maximise during exploration
  -n , --numOutputs     Number of simultaneous outputs of the inference
                        procedure (1 for a single-class classification problem)
  -t , --target         Target device ['x86', 'arduino', 'm3']
  -s , --source         model source type ['seedot', 'onnx', 'tf']
```

An example invocation is as follows:
```
python SeeDot-dev.py -a rnn -v fixed -d usps10 -n 1 -t arduino -m red_disagree
```

SeeDot expects the `train` and the `test` data files in a specific format. Each data file should be of the shape `[numberOfDataPoints, numberOfFeatures + n]`, where the ground truth/output is in the first `n` columns. The tool currently supports numpy arrays (.npy) for inputting model parameters.
The data files must be present in the directory `datasets/<algo>/<dataset>`. 

After training, the learned parameters are stored in this directory in a specific format. For FastGRNN, the learned parameters are `W`, `U`, `Bg`, `Bh`, `FC`, `FCBias`, `zeta` and `nu`. These parameters are numpy arrays (.npy). The model files must be present in the directory `model/<algo>/<dataset>`.

The compiler output is present in `temp` directory for x86, `arduinodump` directory for arduino, and `m3` directory for m3.

## Getting started: Quantizing FastGRNN on usps10

To help get started with SeeDot, we provide 1) a pre-loaded fixed-point model, and 2) instructions to generate fixed-point code for the FastGRNN predictor on the **[usps10](https://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/multiclass/)** dataset. The process for generating fixed-point code for the Bonsai or ProtoNN predictor is similar.

### Generating fixed-point code

This process consists of four steps: 1) installing EdgeML TensorFlow library, 2) training ProtoNN on usps10, 3) quantizing the trained model with SeeDot, and 4) performing prediction on the device.

#### **Step 1: Installing EdgeML TensorFlow library**

1. Clone the EdgeML repository and navigate to the right directory.
     ```
     git clone https://github.com/Microsoft/EdgeML
     cd EdgeML/tf/
     ```

2. Install the EdgeML library.
     ```
     pip install -r requirements-cpu.txt
     pip install -e .
     ```

#### **Step 2: Training FastGRNN on usps10** 

1. Navigate to the FastGRNN examples directory.
     ```
     cd ../examples/tf/FastCells
     ```
     
2. Fetch and process usps10 data and create output directory.
     ```
     python fetch_usps.py
     python process_usps.py
     ```

3. Invoke ProtoNN trainer using the following command.
      ```
      python fastcell_example.py --data-dir ./usps10 --input-dim 16 --hidden-dim 32
      ```
  This would give around 93-95% classification accuracy. The trained model is stored in the `usps10/FastGRNNResults/<timestamp>` directory.

More information on using the FastGRNN trainer can be found [here](https://github.com/microsoft/EdgeML/tree/master/examples/tf/FastCells).

#### **Step 3: Quantizing with SeeDot**

1. Copy the dataset and model files into the correct directory.
     ```
     cd ../../../tools/SeeDot/
     mkdir datasets/rnn/usps10
     mkdir model/rnn/usps10
     cp ../../examples/tf/FastCells/usps10/*.npy ./datasets/rnn/usps10/
     cp ../../examples/tf/FastCells/usps10/FastGRNNResults/<timestamp>/* ./model/rnn/usps10/
     ```
2. Copy the example code for FastGRNN in the SeeDot language:
     ```
     cp seedot/compiler/input/fastgrnn.sd model/rnn/usps10/input.sd
     ```

3. Invoke SeeDot compiler using the following command.
      ```
      python SeeDot-dev.py -a rnn -v fixed -t arduino -m red_disagree -n 1 -d usps10
      ```

   The SeeDot-generated code would give around 92-95% classification accuracy. The difference in classification accuracy is 0-3% compared to the floating-point code. The generated code is stored in the `arduinodump` folder which contains the sketch along with two files: model.h and predict.cpp. `model.h` contains the quantized model and `predict.cpp` contains the inference code.

#### **Step 4: Prediction on the device**

Follow the below steps to perform prediction on the device, where the SeeDot-generated code is run on a single data-point stored on the device's flash memory.

1. The model files are generated within `arduinodump/arduino/16/rnn/usps10`. Copy all the files to `arduinodump/arduino`.
2. Open the Arduino sketch file located at `arduinodump/arduino/arduino.ino` in the [Arduino IDE](https://www.arduino.cc/en/main/software).
3. Connect the Arduino microcontroller to the computer and choose the correct board configuration.
4. Upload the sketch to the device.
5. Open the Serial Monitor and select baud rate specified in the sketch (default is 115200) to monitor the output.
6. The average prediction time is computed for every iteration. On an Arduino Uno, the average prediction time is around 280000 micro seconds.

More device-specific details on extending the Arduino sketch for other use cases can be found in [`arduino/README.md`](https://github.com/microsoft/EdgeML/blob/Feature/SeeDot/Tools/SeeDot/seedot/arduino/README.md).


The above workflow has been tested on Arduino Uno. It is expected to work on other Arduino devices as well.


Copyright (c) Microsoft Corporation. All rights reserved. Licensed under the MIT license.
