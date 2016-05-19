# JCC
Jared's C Compiler : Build a mini C compiler(x86-64) from scratch.

This is an unfinished C compiler.
====================================
This is a final project for NCKU compiler system course.


Quick Start:
====================================
All the toolchain you need is GCC on Linux based system.
Tested Platform: Ubuntu 16.04(x64)

```
git clone https://github.com/JaredCJR/JCC
cd JCC
```

Phase 1:Lexical Analysis
---------------------------
- This is a Token Colorer,it will color the target file tokens,and print in the terminal colorfully.
- Using the lexical analysis to identify tokens for coloring.

```
git checkout DEMO_LEX
make clean
make demo
```
![alt tag](https://raw.githubusercontent.com/JaredCJR/JCC/master/demo/pictures/phase_lexical.jpg)


Phase 2:Syntax Analysis
---------------------------
- This is a Syntax Indenter,it will indent the codes with basic functionalities and Token Colorer.
- Using syntax analysis to check basic grammars , based on Token Colorer.
```
git checkout master  (FIXME:Need to create a branch later)
make clean
make demo
```
![alt tag](https://raw.githubusercontent.com/JaredCJR/JCC/master/demo/pictures/phase_syntax.jpg)


Phase 3:Semantic Analysis
---------------------------
NOT DONE!


Supported Functionality
==============================
- **Tokens:**
  - Arithmetic Operators
    - "+"
    - "-"
    - "*"
    - "/"
    - "%"
  - Relation Oerators
    - "=="
    - "!="
    - "<"
    - "<="
    - ">"
    - ">="
  - Assignment Operators
    - "="
  - Pointer Operators
    - "->"
    - "."
    - "&"
  - Others
    - "(" and ")"
    - "[" and "]"
    - "{" and "}"
    - ";"
    - ","
    - "..."
- **Keywords:**
  - Constants
    - "tk_cINT" (number,  ex:999)
    - "tk_cCHAR"(single character,  ex:'X')
    - "tk_cSTR" (characters,  ex:"This is JCC\n")
  - keywords
    - "int"
    - "char"
    - "void"
    - "struct"
    - "if"
    - "else"
    - "for"
    - "continue"
    - "break"
    - "sizeof"
  - user defined
    - Ex: int user_ident; ("user_ident" will be added.)





AUTHOR:
====================================
- Jia-Rung Chang(張家榮)(or Jared)
    - National Cheng Kung University,Taiwan
    - Major in Engineering Science(Computer Science)

