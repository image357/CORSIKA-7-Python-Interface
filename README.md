# CORSIKA interface

CORSIKA interface using COAST to extract shower information within python.

---

This piece of code is an implementation of the
[COAST interface](https://web.ikp.kit.edu/rulrich/coast.html) in order to link
CORSIKA air-shower information handling to a python interpreter.
It will enable you to write, extract, modify, etc. air-shower data on the fly
within the scope of python scripts. It is a 1-to-1 map of the functionality of the
COAST interface mode.


# Prerequisites

* [CORSIKA](https://www.ikp.kit.edu/corsika/)
* [COAST](https://web.ikp.kit.edu/rulrich/coast.html)
* python3 development files (e.g. python3-dev or python3-devel packages for
  your distribution)
* (g)make
* gcc
* doxygen


# Installation

First clone the repository:
```bash
git clone https://github.com/image357/corsika-interface
```

Next, point your `COAST_USER_LIB` environment variable to the git repository.
For instance, add the following to your `.bashrc`:
```bash
COAST_USER_LIB="/path/to/corsika-interface"; export COAST_USER_LIB
LD_LIBRARY_PATH="${LD_LIBRARY_PATH:+${LD_LIBRARY_PATH}:}$COAST_USER_LIB"; export LD_LIBRARY_PATH
```

Make sure that you have the following environment variables:
* `CORSIKA_DIR`
* `COAST_DIR`

E.g. in your `.bashrc` file:
```bash
CORSIKA_DIR="/path/to/corsika/install/corsika-76900"; export CORSIKA_DIR
COAST_DIR="/path/to/coast/install/coast-v4r5"; export COAST_DIR
LD_LIBRARY_PATH="${LD_LIBRARY_PATH:+${LD_LIBRARY_PATH}:}$COAST_DIR/lib"; export LD_LIBRARY_PATH
```

Once your environment is ready, compile the project within your git repository:
```bash
make release docs
```

Go to your CORSIKA installation folder and run the `./coconut` script. Choose
whatever options you want but make sure that you at least select
```
d3 - Use an external COAST user library (COrsika data AccesS Tool)
```

Once the compilation of CORSIKA is done you are ready to create your python
analysis code. First, create a new folder (for instance `/path/to/python/code`).
Then copy the file named `override_example.py` from your git repository to this
new folder such that it is called `override.py`:
```bash
cp /path/to/corsika-interface/override_example.py /path/to/python/code/override.py
```
At last, you have to define another environment variable, because CORSIKA needs
to know where you have your python code. Add the following to your `.bashrc`:
```bash
CORSIKA_PYTHON_INTERFACE="/path/to/python/code"; export CORSIKA_PYTHON_INTERFACE
```

That's it! When you now run your CORSIKA binary you should see the following
two additional outputs:
```bash
patched interface
running interface tests
```


# Usage

You control the python interface with your `override.py` file. It is the main
entrance file that will be executed by the CORSIKA binary. In order to use the
link to the COAST interface you have to inherit from a specific class:
```python
interface.Override
```
This class is an abstract interface class for which you will have to implement
5 methods:
* `init`: Used to do some initialization tasks
* `close`: Used to do some some finalization tasks
* `write`: Will give you CORSIKA block-data whenever it is ready to be written
  to disk.
* `interaction`: Will be called when there is interaction information available.
* `track`: Will give you information about particle tracks.

Once you have implemented your personal interface class, you have to call
```python
interface.patch(MyInterfaceClass)
```
in order to override the default interface behavior.

Every user-accessible method is documented and you should be able to
explore the functionality via autocompletion features of your editor or you can
have a look at the official documentation in the `html` folder in your git
repository.


# Contributing

Feel free to fork the project, create pull requests and open issues if you encouter problems or if you have questions.


# Disclaimer

The source code can be found here: https://github.com/image357/CORSIKA-7-Python-Interface
