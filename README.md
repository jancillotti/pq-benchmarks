*These instructions are valid for Ubuntu 22.04 and the most recent versions of Botan and liboqs as of September 29, 2023*

Create a virtual machine with Ubuntu 22.04. After installation, be sure to update all packages to their latest versions:

    sudo apt update
    sudo apt upgrade -y

Next, install dependencies required to build the various cryptographic packages and cross-compile test programs for ARM architecture:

    sudo apt install -y g++-aarch64-linux-gnu

Once this is done, proceed with installing the Botan library:


Installing Botan:
    
    
    cd ~
    git clone https://github.com/randombit/botan.git
    mv botan botan-arm
    mkdir botan-aarch64
    cd botan-arm
    ./configure.py --os=linux --cpu=armv8 --ar-command=aarch64-linux-gnu-ar --cc-bin=$(which aarch64-linux-gnu-g++) --cc=gcc --prefix=~/botan-aarch64/
    make

Installing OQS:

    cd ~
    git clone https://github.com/open-quantum-safe/liboqs.git
    cd liboqs
    mkdir build && cd build
    cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/local/ ..
    make
    sudo make install
    sudo ldconfig

...
