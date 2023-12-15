This is a simple C++ program which will count the number of vowels in a set of files. The program assumes the user has a directory containing 20 text files. The program will prompt the user for the directory location of the files. If the files are NOT located in the same directory as the executable then the user will need to supply the full path of where the files are located.

There is one file, **vowels.cpp**. You can use your favorite C++ compiler to compile it into an executable. Note, you will need to link with the lpthread library.

Here is an example compile command.

```bash
$ g++ vowels.cpp -lpthread
```

Then to run the program.

```bash
$ ./a.out
```
