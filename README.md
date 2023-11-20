# PQ-Benchmarking
*These instructions are valid for Ubuntu 22.04 and the most recent versions of Botan and liboqs as of September 29, 2023*

This repository is made available as part of an artifact submission to the 2024 Network and Distributed 
System Security Symposium (NDSS), associated with the following paper:

Geoff Twardokus, Nina Bindel, Hanif Rahbari, and Sarah McCarthy, "When Cryptography Needs a Hand: Practical Post-Quantum Authentication for V2V Communications," _Network and Distributed System Security Symposium (NDSS 2024)_, San Diego, CA, Feb. 2024.

Bibtex:

    @inproceedings{twardokus2024when,
        author = "Geoff Twardokus and Nina Bindel and Hanif Rahbari and Sarah McCarthy",
        title = "When Cryptography Needs a Hand: Practical Post-Quantum Authentication for {V2V} Communications",
        booktitle = "Proc. Network and Distributed System Security Symposium (NDSS)",
        month = feb,
        year = "2024",
        address = "San Diego, CA",
        pages = ""
    }

## Repository Structure
This repository consists of multiple source code (C++) files, a Makefile to be used for building the project from those
source files, and a test script (`functional_test.bash`) that builds the project binaries for the x86 architecture and 
executes them for evaluation purposes on a typical x86-based PC.

## Evaluation Requirements and Supported Environments

### Hardware
No hardware is required beyond a "commodity PC." As defined by the
[NDSS 2024 Call for Artifacts](https://web.archive.org/web/20230930035437/https://secartifacts.github.io/ndss2024/call),
"[a] commodity desktop machine is defined as one with an x86-64 CPU with 8 cores and 16 GB of RAM running a recent Linux
or Windows operating system."

### Software
An Ubuntu 22.04 virtual machine containing the pre-configured artifact is available from [](). This virtual machine was
created and evaluated using Virtualbox version 7.0.8 r156879 (Qt5.15.2), which is freely available from Oracle at
https://www.virtualbox.org. We recommend users and evaluators use the same version to ensure consistency.
## Setup
Create a fresh virtual machine with Ubuntu 22.04 (VirtualBox is recommended for a free hypervisor). After installation, be sure to update all packages to their latest versions:

    sudo apt update
    sudo apt upgrade -y

Next, install several dependencies:

    sudo apt install -y g++-aarch64-linux-gnu astyle cmake gcc ninja-build libssl-dev python3-pytest python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind

Clone the `pq-benchmarks` repository.

    cd $HOME
    git clone https://github.com/twardokus/pq-benchmarks.git

## Installing Botan
First, obtain the Botan source code from GitHub:
    
    cd $HOME
    git clone https://github.com/randombit/botan.git

Next, cross-compile Botan for ARM:
    
    mv botan botan-arm
    mkdir botan-aarch64
    cd botan-arm
    ./configure.py --os=linux --cpu=armv8 --ar-command=aarch64-linux-gnu-ar --cc-bin=$(which aarch64-linux-gnu-g++) --cc=gcc --prefix=$HOME/botan-aarch64/
    make
    make install

Now, compile Botan for x86_64 (you will need to clone the Botan source repository again, as included in the command sequence below):

    cd $HOME
    git clone https://github.com/randombit/botan.git
    mv botan botan-x86
    mkdir botan-intel
    cd botan-x86
    ./configure.py --os=linux --cpu=x86_64 --cc-bin=$(which g++) --cc=gcc --prefix=$HOME/botan-intel/
    make
    make install

## Installing liboqs

Start by creating placeholder directories for the ARM and x86 installations of liboqs:

    mkdir liboqs-aarch64 liboqs-x86

Now, obtain the liboqs source code from GitHub:

    cd $HOME
    git clone -b main https://github.com/open-quantum-safe/liboqs.git

Next, build liboqs for ARM:

    cd $HOME
    mv liboqs liboqs-arm 
    cd liboqs-arm
    mkdir build && cd build
    cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=$HOME/pq-benchmarks/arm-toolchain.cmake -DOQS_USE_OPENSSL=OFF -DCMAKE_INSTALL_PREFIX=$HOME/liboqs-aarch64 ..
    ninja
    ninja install

Now, build liboqs for x86_64:

    cd $HOME
    git clone -b main https://github.com/open-quantum-safe/liboqs.git
    mv liboqs liboqs-intel
    cd liboqs-intel
    mkdir build && cd build
    cmake -GNinja -DOQS_USE_OPENSSL=OFF -DCMAKE_INSTALL_PREFIX=$HOME/liboqs-x86 ..
    ninja
    ninja install


## Building and running benchmarking code


Finally, move to the cloned `pq-benchmarking` repository and build the test binaries for both x86 and ARM (note that either architecture can be build alone with individual make rules. Check the included Makefile for details):

    cd $HOME/pq-benchmarks
    make all

Run the binaries:

    ./functional_test.bash

Results will be displayed in the terminal and written to per-algorithm results files (e.g., "ecdsa_results.txt").
