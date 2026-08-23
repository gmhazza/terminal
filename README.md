# terminal Clone in C++

A lightweight terminal clone inspired by Windows and Linux shell behaviors, built entirely in C++.

### Supported Commands
* `clear` - Clears the terminal screen
* `exit` - Quits the shell
* `echo <text>` - Prints text back to stdout
* `type <command>` - Checks if a command is a shell builtin

---

### How to Test

1. **first clone the project**
```bash
git clone https://github.com/gmhazza/terminal.git
cd ./terminal
```

2. **Build the project**
* on windows (mingw)
```bash
mingw32-make
```
* on linux
```sh
make
```

3. **execute the project**
```bash
./bin/main
```