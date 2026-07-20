# C++ Competitive Programming Setup

**Short description:** A lightweight C++23 competitive-programming setup for Sublime Text, with a starter template and STL debug utilities.

This repository contains the personal C++ tools used to write, compile, and debug competitive-programming solutions quickly.

## Contents

- `debug.h` — a local debugging header that prints numbers, strings, pairs, tuples, STL containers, adapters, optionals, bitsets, and C-style arrays.
- `Sublime-Setup/C++23.sublime-build` — a Sublime Text build system using `g++`, C++23, warnings, optimisation, and AddressSanitizer/UBSan.
- `Sublime-Setup/insert_cppmain.py` — a Sublime Text command that inserts a C++ solution template with common aliases, PBDS, fast I/O, and a timestamp.
- `Sublime-Setup/Default (Linux).sublime-keymap` — binds <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>M</kbd> to insert the template in C++ files.

## Requirements

- Linux
- Sublime Text
- `g++` with C++23 support

## Setup

1. Copy `debug.h` to a directory searched by your compiler, such as `/usr/local/include`, or add this repository to your compiler include paths.
2. Copy the files in `Sublime-Setup/` to the appropriate Sublime Text `Packages/User` directory.
3. Select **Tools → Build System → C++23** in Sublime Text.
4. In a C++ source file, press <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>M</kbd> to insert the starter template.

The build profile compiles the open file and runs the produced executable for up to four seconds. It reads from `inputf.in` and writes to `outputf.in` in the source file's directory.

## Debugging

The starter template enables debug output when compiled with `-DLOCAL`:

```cpp
#ifdef LOCAL
#include <debug.h>
#else
#define dbg(x...)
#endif

// Example
vector<int> values = {1, 2, 3};
dbg(values); // values:- [1 2 3]
```

Debug output is written to `stderr`, keeping normal program output clean.
