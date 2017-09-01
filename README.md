## Edge Machine Learning

This repository provides code for machine learning algorithms for edge devices developed at [Microsoft Research India](https://www.microsoft.com/en-us/research/project/resource-efficient-ml-for-the-edge-and-endpoint-iot-devices/). 

Machine learning models need to have a small footprint in terms of battery, storage and latency to  be deployed on edge devices. One example of a ubiquitous real-world application where such models are desirable is resource-scarce devices and sensors in the Internet of Things (IoT) setting. To make real-time predictions locally on IoT devices without connecting to the cloud, we need models that fit in a few kilobytes.

This repository contains two such algorithms **Bonsai** and **ProtoNN** that shine in this setting. These algorithms can train models for classical supervised learning problems with memory requirements that are orders of magnitude lower than other modern ML algorithms. The trained models can be loaded onto on edge and IoT devices/sensors, and used to make fast, precise, and accurate predictions completely offline.

For details, please see the ICML'17 publications on [Bonsai](publications/Bonsai.pdf) and [ProtoNN](publications/ProtoNN.pdf) algorithms.

Initial Contributors: Chirag Gupta, [Aditya Kusupati](https://adityakusupati.github.io/), [Ashish Kumar](https://ashishkumar1993.github.io/), and [Harsha Vardhan Simhadri](http://harsha-simhadri.org).

We welcome contributions, comments and criticism. For questions, please [email Harsha](mailto:harshasi@microsoft.com).

### Requirements
- Linux. We developed the code on Ubuntu 16.04LTS.
  For Windows 10 Anniversary Update or later, one can also use the Windows Subsystem for Linux. 
  The code can also be compiled in Windows with Visual Studio,
  but this release does not include necessary makefiles yet. 
- gcc version 5.4. Other gcc versions above 5.0 could also work.
- An implementation of BLAS, sparseBLAS and vector math calls.
  We link with the implementation provided by the [Intel(R) Math Kernel Library](https://software.intel.com/en-us/mkl).
  Please download later versions (2017v3+) of MKL as far as possible.
  The code can be made to work with other math libraries with a few modifications.

### Building
After cloning this reposirory, set compiler and flags appropriately in `config.mk` and do:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<MKL_PATH>:<EDGEML_ROOT>
make -j
```
Typically, MKL_PATH = /opt/intel/mkl/lib/intel64_lin/, and EDGEML_ROOT is '.'.

This will build two executables _Bonsai_ and _ProtoNN_.
Sample data to try these executables is not included in this repository. 

### Download a sample dataset

```bash
mkdir usps10
cd usps10
wget http://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/multiclass/usps.bz2
wget http://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/multiclass/usps.t.bz2
bzip2 -d usps.bz2
bzip2 -d usps.t.bz2
mv usps train.txt
mv usps.t test.txt
cd <EDGEML_ROOT>
```
This will create a sample train and test dataset, on which
you can  train and test Bonsai and ProtoNN algorithms.
For detailed instructions, see [Bonsai Readme](README_BONSAI_OSS.md) and [ProtoNN Readme](README_PROTONN_OSS.md).

### Makefile flags
You could change the behavior of the code by setting these flags in `config.mk` and rebuilding with `make -Bj`. All these flags can be set for both ProtoNN and Bonsai.
The following are supported currently by both ProtoNN and Bonsai. 

    SINGLE/DOUBLE:  Single/double floating-point precision.
    ZERO_BASED_IO:  Enable to perform I/O with labels and indices being 0-based instead of 1-based. 
    TIMER:          Timer logs. Print running time of various calls.
    CONCISE:        To be used with TIMER to print limited time information.

The following are supported only by ProtoNN, but one can write corresponding code for Bonsai. 
 
    LOGGER:         Debugging logs. Currently prints min, max and norm of matrices.
    LIGHT_LOGGER:   Less verbose version of LOGGER. Can be used to track call flow. 
    XML:            Enable to train with extreme multilabel learning datasets. This is in beta.
    VERBOSE:        Print additional informative output to stdout.
    
Additionally, there is one of two flags that has to be set in the Makefile: 
    
    MKL_PAR_LDFLAGS: Linking with parallel version of MKL
    MKL_SEQ_LDFLAGS: Linking with sequential version of MKL


### Microsoft Open Source Code of Conduct
This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
