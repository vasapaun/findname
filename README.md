# findname
Program that finds filenames matching a given regex in the current (or specified) directory and all its subdirectories.

Usage:
    
    findname <regex> <options>

Options:
    
    -i[nverse]  - Find all filenames MISmatching the given regex

    -d[elete]   - Delete(unlink) all files found (You will be prompted for confirmation regarding each file found)

    -l[ocation] - Specify the root directory for the search. Default directory is the directory from which you're running the program 
