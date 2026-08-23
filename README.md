# terminal Clone in C++

A lightweight terminal clone inspired by Windows and Linux shell behaviors, built entirely in C++.

### Supported Commands
* `clear` - Clears the terminal screen
* `exit` - Quits the shell
* `echo <text>` - Prints text back to stdout
* `type <command>` - Checks if a command is a shell builtin

---

### How to Test

* first clone the project
```bash
git clone https://github.com/gmhazza/terminal.git
cd ./terminal
```

* Build the project
1. on windows (install mingw32)
```bash
mingw32-make
```
2. on linux
```sh
make
```

* execute the project
```bash
./bin/main
```