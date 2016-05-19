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

Phase 1:Lexical Analysis
---------------------------
- **Tokens:**
  - Arithmetic Operators
    - `+`
    - `-`
    - `*`
    - `/`
    - `%`
  - Relation Oerators
    - `==`
    - `!=`
    - `<`
    - `<=`
    - `>`
    - `>=`
  - Assignment Operators
    - `=`
  - Pointer Operators
    - `->`
    - `.`
    - `&`
  - Others
    - `(` and `)`
    - `[` and `]`
    - `{` and `}`
    - `;`
    - `,`
    - `...`
- **Keywords:**
  - Constants
    - `tk_cINT` (number,  ex:999)
    - `tk_cCHAR`(single character,  ex:'X')
    - `tk_cSTR` (characters,  ex:`This is JCC\n`)
  - keywords
    - `int`
    - `char`
    - `void`
    - `struct`
    - `if`
    - `else`
    - `for`
    - `continue`
    - `break`
    - `sizeof`
  - user defined
    - Ex:`int user_ident;` (`user_ident` will be added.)

Phase 2:Syntax Analysis
---------------------------

**Declaration**
```
 * <translation_unit>::={<external_declaration>}<tk_EOF>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <external_declaration>::=<function_definition> | <declarator>
 * <function_definition>::=<type_specifier><declarator><funcbody>
 * <declarator>::=<type_specifier><tk_SEMICOLON> | <type_specifier><init_declarator_list><tk_SEMICOLON>
 * <init_declarator_list>::=<init_declarator>{<tk_COMMA><init_declarator>}
 * <init_declarator>::=<declarator>{<tk_ASSIGN><initializer>}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <type_specifier>::=<kw_INT>   |
 *                    <kw_CHAR>  |
 *                    <kw_VOID>  |
 *                    <struct_specifier>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <struct_specifier>::=<kw_STRUCT><IDENTIFIER><tk_BEGIN><struct_declaration_list><tk_END>
 *                    | <kw_STRUCT><IDENTIFIER>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <struct_declaration_list>::=<struct_declaration>{<struct_declaration>}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <struct_declaration>::=<type_specifier><struct_declaration_list><tk_SEMICOLON>
 * <struct_declaration_list>::=<declarator>{<tk_COMMA><declarator>}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <declarator>::={<pointer>}<direct_declarator>
 * <pointer>::=<tk_STAR>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <direct_declarator>::=<IDENTIFIER><direct_declarator_postfix>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <direct_declarator_postfix>::={<tk_openBR><tk_cINT><tk_closeBR>
 *                                | <tk_openBR><tk_closeBR>
 *                                | <tk_openPA><parameter_type_list><tk_closePA>
 *                                | <tk_openPA><tk_closePA>
 * } 
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <parameter_type_list>::=<parameter_list> | <parameter_list><tk_COMMA><tk_ELLIPSIS>
 * <parameter_list>::<parameter_declaration>{<tk_COMMA><parameter_declaration>}
 * <parameter_declaration>::=<type_specifier>{<declarator>} 
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <funcbody>::=<compound_statement>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <initializer>::=<assignment_expression>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
```

**Expression**
```
 * <expression>::=<assignment_expression>{<tk_COMMA><assignment_expression>}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <assignment_expression>::=<equality_expression>
 *                         | <unary_expression><tk_ASSIGN><assignment_expression>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <equality_expression>::=<relational_expression>
 *                       { <tk_EQ><relational_expression>
 *                       | <tk_NEQ><relational_expression>
 *                       } 
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <relational_expression>::=<additive_expression>
 *                        {
 *                           <tk_LT><additive_expression>
 *                         | <tk_GT><additive_expression>
 *                         | <tk_LEQ><additive_expression>
 *                         | <tk_GEQ><additive_expression>
 *                        } 
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <additive_expression>::=<multiplicative_expression>
 *                      {
 *                        <tk_PLUS><multiplicative_expression>
 *                      | <tk_MINUS><multiplicative_expression>
 *                      }
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <multiplicative_expression>::=<unary_expression>
 *                             {
 *                               <tk_STAR><unary_expression>
 *                             | <tk_DIVIDE><unary_expression>
 *                             | <tk_MOD><unary_expression>
 *                             }
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <unary_expression>::=<postfix_expression>
 *                    | <tk_AND><unary_expression>
 *                    | <tk_STAR><unary_expression>
 *                    | <tk_PLUS><unary_expression>
 *                    | <tk_MINUS><unary_expression>
 *                    | <sizeof_expression>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <sizeof_expression>::=<kw_SIZEOF><tk_openPA><type_specifier><tk_closePA>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <postfix_expression>::=<primary_expression>
 *                     {
 *                        <tk_openBR><expression><tk_closeBR>
 *                      | <tk_openPA><tk_closePA>
 *                      | <tk_openPA><argument_expression_list><tk_closePA>
 *                      | <tk_DOT><IDENTIFIER>
 *                      | <tk_POINTTO><IDENTIFIER>
 *                     }
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <primary_expression>::=<IDENTIFIER>
 *                      | <tk_cINT>
 *                      | <tk_cSTR>
 *                      | <tk_cCHAR>
 *                      | <tk_openPA><expression><tk_closePA>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <argument_expression_list>::=<assignment_expression>{<tk_COMMA><assignment_expression>}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
```


**Statement**
``` 
 * <statement>::=<compound_statement>
 *             | <if_statement>
 *             | <return_statement>
 *             | <break_statement>
 *             | <continue_statement>
 *             | <for_statement>
 *             | <expression_statement>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * <compound_statement>::=<tk_BEGIN>{<declaration>}{<statement>}<tk_END> 
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <expression_statement>::=<tk_SEMICOLON>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <if_statement>::=<kw_IF><tk_openPA><expression><tk_closePA><statement>[<kw_ELSE><statement>]
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <for_statement>::=
 *               <kw_FOR><tk_openPA><expression_statement><expression_statement><expression><tk_closePA><statement>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <continue_statement>::=<kw_CONTINUE><tk_SEMICOLON>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <break_statement>::=<kw_BREAK><tk_SEMICOLON>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * <return_statement>::=<kw_RETURN><tk_SEMICOLON>
 *                    | <kw_RETURN><expression><tk_SEMICOLON>
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
```


AUTHOR:
====================================
- Jia-Rung Chang(張家榮)(or Jared)
    - National Cheng Kung University,Taiwan
    - Major in Engineering Science(Computer Science)

