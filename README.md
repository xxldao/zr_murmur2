#Murmur2
This is Murmur2 hash wrapper for Python.

##How to install

### Prerequisites

For now, you must install `numpy` prior to installing this package by running:
```bash
pip install numpy
```

### PIP install

You can install from pip:
```bash
pip install git+git://github.com/gsmcwhirter/murmur2.git
```

### Manual Install

If you want to install Murmur2 from a local download, execute the following script.
```bash
python setup.py install
```

##How to use
There are two functions implemented:
- murmur64a
- murmur32n

Example:
```
import murmur2

print murmur2.murmur64a("test",4,100)
```

First argument, "test", is input.
Second argument, 4, is the length of first argument.
Third argument is a seed. If you set a different seed, murmur64a returns different hash value.

