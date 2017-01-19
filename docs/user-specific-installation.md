# User-Specific Installation Setup and Requirements

This section assumes the user's home directory is the default directory and that the system-wide installation has been completed by an admin. 

## Setup

1. Create a local bin directory: ``mkdir bin``

2. Create a local etc for alternatives: ``mkdir -p etc/alternatives``
		
3. Create a local var for alternatives: ``mkdir -p var/lib/dpkg/alternatives``
		
4. Create a directory for protocol buffer files: ``mkdir protobuf``

5. Create a prediction services directory: ``mkdir prediction_services``

6. Update ``path`` to include the new local bin directories.

		vi .profile
		export PATH=''$HOME/bin:$HOME/ .local/bin:$PATH''
		source .profile
		
## Alternatives

Alternatives writes files to /etc and /var. This requires administration privileges, but we provide user-accessible alternatives.

1. gcc C compiler

		$ update-alternatives --altdir ~/etc/alternatives --admindir ~/var/lib/dpkg/alternatives --install ~/bin/gcc gcc /usr/bin/gcc-5 100
		$ update-alternatives --altdir ~/etc/alternatives --admindir ~/var/lib/dpkg/alternatives --install ~/bin/gcc gcc /usr/bin/gcc-4.8 50
		$ update-alternatives --altdir ~/etc/alternatives --admindir ~/var/lib/dpkg/alternatives --config gcc

2. g++ C++ compiler

		$ update-alternatives --altdir ~/etc/alternatives --admindir ~/var/lib/dpkg/alternatives --install ~/bin/g++ g++ /usr/bin/g++-5 100
		$ update-alternatives --altdir ~/etc/alternatives --admindir ~/var/lib/dpkg/alternatives --install ~/bin/g++ g++ /usr/bin/g++-4.8 50
		$ update-alternatives --altdir ~/etc/alternatives --admindir ~/var/lib/dpkg/alternatives --config g++

## CUDA Environment Variables

1. Set CUDA environment variables in ``.profile``:

		export CUDA PATH=/usr/local/cuda

2. Run .profile: ``$ source .profile``

## Python Virtual Environments

1. Create environment: ``$ virtualenv <ENV>``
	
	Example: ``$ virtualenv ~/dw``
	Example: ``$ source ~/dw/bin/activate``
	
## Python Modules

These are the Python packages required for the H2O Python client. If using virtual environments, please be sure to activate and install packages in environments. 

1. Install required H2O Python modules:


## R Packages

All commands that are to be executed from R will be pre-fixed with a greater than sign (i.e. >).


		$ R		

		48: USA (CA 1) [https]
		
## Jupyter Notebooks

If using virtual environments, please be sure to activate  and install packages in environments. 

	$ pip install jupyter

## Jupyter Notebook R Kernel

**For Virtual Environment**

1. Install required packages:

		> system.file(package="IRkernel")

		> R.home("bin")

		> exit
	

		$ cd /home/wen/R/x86 64-pc-linux-gnu-library/3.2/IRkernel/kernelspec

		$ cp kernel.json kernel.json.orig

 - kernel.json Before

		

		
**For Global environment**

		$ R