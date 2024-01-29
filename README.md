
# INFIX CALCULATOR 

![C][c-md-badge]

A simple **_terminal-based calculator_** that uses **_doubly linked lists_**. It receives input from a file of infix expressions, input is assumed to be written in the correct format. The output prints a step-by-step computation of each valid expression before the result.
- Does not handle parentheses.
- Prioritizes multiplication, division, and modulo over addition and subtraction.
- Follows a left to right precedence rule.
- Negative values are allowed.
<br />

## Table of Contents
1. [Requirements](#requirements)
2. [How to Run](#instructions)
3. [Other Notes](#note)
<br />

## Requirements <a name="requirements"></a>
1. Ensure that your system has C installed. Linux-based operating systems usually have it installed.
    - To check if you have C and its necessary compilers, type in:
      - `gcc --vesion`
      - If it does not return a version number, proceed to installation of compilers.
    - For installation, refer to online references for installation guides.
      - Windows: https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/

2. When downloading the files, make sure that this directory tree is followed:

   ```
    infix-calcu
    ├── expressions.in.txt
    ├── src
    │   ├── infix.c
    │   └── initializers.h
    └── README.md
   ```
<br />

## Running Project <a name="instructions"></a>
1. Before compiling and running the program, check the `expressions.in.txt` file first:
    - The first line should be the **_number of expressions_** to be evaluated.
    - Each expression is separated by a _new line_.
    - Follow this format for the expressions:

      ```
      (num) (op) ... (num N) (op N) (num N+1)
      
      Where each expression has N operators and N+1 numbers / operands.
      ```

2. To run the program, make sure to compile the C files first.
    - If you are in a Linux / Ubuntu environment:
      - Open the terminal and proceed to the `src` folder. Compile by typing `gcc infix.c -o infix`.
      - After successful compiling, run the program by using the command `./infix`.
    - If you are using VSCode (Windows), open the `infix.c` file and perform _Run Code_.
    
3. The terminal will return the results. It also states whether an expression is valid or not.
<br />

##
### Author
- Ralph Kenneth Rea

##
### Note <a name="note"></a>
- This project is in fulfillment of the requirements in CMSC 21: Fundamentals of Programming. UPLB.

[c-md-badge]: https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white
