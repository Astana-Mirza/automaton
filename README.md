# Automaton
A sandbox for experiments with finite automatons and cryptoautomatons.

Qt and Python 3 are required to build the program.

### Build
Make sure that submodules are cloned with the main code, then run
```
qmake automaton.pro
make
```
This will compile the project to `build/automaton`

# Description
## Brief information
Finite automatons are widely used in cryptography. Stream ciphers use
keystream generators to encrypt data. Keystream generators can use
combiners to make a keystream from separate streams of data.

Cryptosystems can also use linear feedback shift registers (LFSR) and
non-linear ones.

All these concepts can be implemented with finite automatons and/or their
compositions.

Automaton has initial state and uses transition and output functions to
get next states and generate output. Both functions use current state and
input data. In case of cryptoautomaton, they also use key as a third parameter.

## Using the sandbox
User can make own finite automatons with writing Python functions. To create
an automaton, the user should specify transition and output functions by
setting their files and names. To make it simple, all functions must take
and return strings (use libkam for more flexibility).

It is possible to execute automatons step-by-step or process a bunch of data.

Some examples are available: MUGI keystream generator, combiners of Bluetooth and VEST
systems and LFSR. They can be found in `examples` directory.
