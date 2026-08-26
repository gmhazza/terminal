# terminal Clone in C++

A lightweight terminal clone inspired by Windows and Linux shell behaviors, built entirely in C++.

### Supported Commands
* `clear` - Clears the terminal screen
* `exit` - Quits the shell
* `echo <text>` - Prints text back to stdout
* `type <command>` - Checks if a command is a shell builtin
* `cwd` - Print the current working directory
* `cd <path>` - Change the path of current working directory
* `ls <path>` - Show the files and folders of the path or current working directory if no path specified
* `mkdir <name>` - Create a new directory with a specific name
* `mkfile <name>` - Create a new file with a specific name

### Supported Cross Platform ENV PATH

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