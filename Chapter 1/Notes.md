# Preprocessor Directives
1. Preprocessing can be defined as something that allows one to engineer and modify their src code before submitting it to the compiler.

2. The purpose of preprocessing is to remove the preprocessing directives and substitute them with equivalent generated C code and prepare a final source that is ready to be submitted to the compiler.

3. The behavior of the C/C++ Preprocessor can be controlled and influenced using a set of _directives_. C directives  are lines of code starting with a `#` character in both header and source files. These lines are only meaningful to the C Preprocessor and never to the C compiler. There are various such directives but some are important such as the ones used macro definition and conditional compilation.

Macros have a number of applications and you can see some of them as follows:
- Definiing a constant
- Using as a function instead of writing a C function
- Loop unrolling
- Header guards
- Code generation
- Conditional compilation

## 1.1 Defining a Macro
Macros are defined using the `#define` directive. Each macro has a name and a possible list of parameters. It also has a value that gets substituted by its name in the Preprocessing phase through a step called _macro expansion_. A macro can also be undefined with the `#undef` directive.

**basic use of #define to substitute a variable**
```c
#include <stdio.h>
#define ABC 4
int main(int argc, char** argv){
    int x = 5;
    int y = ABC;
    int z = x+y;
    printf("result: %d\n",z);
}
```
In the preceding example, `ABC` is not a variable that holds an integer value nor an integer constant. In fact, it's a macro called `ABC` and its corresponding value is `4`. After the macro expansion phase, the resulting code can be submitted to the C compiler and if we use `clang -E filename.c` it looks like this:

```shell
# 2 "macros.c" 2

int main(int argc, char** argv){
    int x = 5;
    int y = 4;
    int z = x+y;
    printf("result: %d\n",z);
}
```
In the preceding example, the preprocessor did the macro expansion, and as part of it, the preprocessor simply replaced the macro's name with its value. The preprocessor also removes the comments from the code.

**Function like macro**
```c
#include <stdio.h>
#define ABC 4
#define ADD(a,b)a+b
int main(int argc, char** argv){
    int x = 5;
    int y = ABC;
    int z = x+y;
    printf("result-1: %d\n",z);
    int a = ADD(x,z);
    printf("result-2: %d\n",a);
}
```
In the preceding code, `ADD` is not a function. It is just a function-like macro that accepts arguments. After preprocessing, the result code will be like this:
```c
int main(int argc, char** argv){
    int x = 5;
    int y = 4;
    int z = x+y;
    printf("result-1: %d\n",z);
    int a = x+z;
    printf("result-2: %d\n",a);
}
```
As you can see, the argument `x` used as parameter `a` is replaced with all instances of `a` in the macro's value. This is the same for the parameter `b`, and its corresponding argument `y`. Then the final substitution occurs, and we get `x+y` instead of `ADD(a+b)` in the preprocessed code. This is how function like macros can mimic functions, and one can put frequently used logic into a function-like-macro instead of a C function.

Macros only exist before the compilation phase. This means that the compiler, theoretically, doesn't know anything about the macros. The compiler knows everything about a function because it is part of the C grammar and it is parsed and being kept in the _parse tree_. But the macro is just a C preprocessor directive only known to the preprocessor itself.

Macros allow you to generate code before the compilation. Modern C compilers are aware of the C preprocessor directives. The modern C compilers know about the source before entering the preprocessing phase.
```c
#include <stdio.h>
#define ABC 4
#define ADD(a,b)a+b
#define CODE \
printf("%d\n",i)

int main(int argc, char** argv){
    int x = 5;
    int y = ABC;
    int z = x+y;
    printf("result-1: %d\n",z);
    int a = ADD(x,z);
    printf("result-2: %d\n",a);
    CODE;
}
```
If we compile the following code using `clang`, we get the following output
```shell
anmolkhanna@Anmols-MacBook-Air Chapter 1 % clang macros.c                                              ~/Users/anmolkhanna/Desktop/Projects/C-Programming/Extreme-C/Chapter 1
macros.c:14:5: error: use of undeclared identifier 'i'
   14 |     CODE;
      |     ^
macros.c:5:15: note: expanded from macro 'CODE'
    5 | printf("%d\n",i)
      |               ^
1 error generated.
```
As we can see in the error message, the compiler points exactly to the line in which the macro is defined.

We can view the proceprocessing result just before compilation in most compilers. With `gcc` or `clang`, you can use the `-E` option to dump code after preprocessing.

**dumping the preprocessed code from the previous code snippet**
```shell
int main(int argc, char** argv){
    int x = 5;
    int y = 4;
    int z = x+y;
    printf("result-1: %d\n",z);
    int a = x+z;
    printf("result-2: %d\n",a);
    printf("%d\n",i);
}
```
Thus, a **_traslation unit_** (or a compilation unit) is the preprocessed C code that is ready to be passed to the compiler.

In a translation unit, all directives are substituted with inclusions or macro expansions and a flat long piece of C code is produced.

Next, let's use macros to generate a Loop

**Using Macros to generate loop**
```c
#include <stdio.h>
#define printVar(a) printf("%d\n",a);
#define startLoop(v,s,e) for(int v=s;v<=e;v++){
#define endLoop }

int main(int argc, char** argv){
    startLoop(counter, 1, 10)
        printVar(counter)
    endLoop
    return 0;
}
```
As you can in the precedign code box, the code inside the `main` function is not a valid C code in any way! But after preprocessing, we get a correct C source code that compiles without any problem. Following is the preprocessed result:
```shell
int main(int argc, char** argv){
    for(int counter=1;counter<=10;counter++){
        printf("%d\n",counter);
    }
    return 0;
}
```
In the code above, we just used a different and not C-looking set of instructions to write our algorithm. Then after preprocessing, we got a fully functional and correct C program. This is an important application of macros; to define a new _Domain Specific Language (DSL)_ and write code using it.

DSLs are very useful in different parts of a project; for example, they are used heavily in testing frameworks such as Google Test Framework (gtest) where a DSL is used to write assertions, expectations, and test scenarios.

We should note that we don't have any C directives in the final preprocessed code. This means that the `#include` directive has been replaced by the contents of the file it was referring to. That is why you see the content of the `stdio.h` header file before the `main` function when you use `clang -E macros.c` to compile the source code.

Let's now look at the next example, which introduces two new operators regarding macro parameters; the `#` and `##` operators:

**using # and ##**
```c
#include <stdio.h>
#include <string.h>
#define cmd(Name) \
    char Name ## _cmd[256] = ""; \
    strcpy(Name ## _cmd,#Name);

int main(int argc, char** argv){
    cmd(copy);
    cmd(paste);
    cmd(cut);
    char uIn[256];
    scanf("%s",uIn);
    if(strcmp(uIn,copy_cmd)==0){
        printf("We copy\n");
    }else if(strcmp(uIn,cut_cmd)==0){
        printf("We cut\n");
    }else if(strcmp(uIn,paste_cmd)==0){
        printf("We paste\n");
    }else{
        printf("Don't know!\n");
    }
    return 0;
}
```
While expanding the macro, the `#` operator turns the paraeter into its string form surrounded by a pair of quotation marks. For example, in the preceding code, the `#` operator used before the `Name` parameter turns it into `"copy"` in the preprocessed code.

The `##` operator has a different meaning. It just concatenates that paramaeter to other elements in the macro definition and usually forms variable names. Following is the preprocessed source for the above code.
```shell
int main(int argc, char** argv){
    char copy_cmd[256] = ""; __builtin___strcpy_chk (copy_cmd, "copy", __builtin_object_size (copy_cmd, 2 > 1 ? 1 : 0));;

    char paste_cmd[256] = ""; __builtin___strcpy_chk (paste_cmd, "paste", __builtin_object_size (paste_cmd, 2 > 1 ? 1 : 0));;

    char cut_cmd[256] = ""; __builtin___strcpy_chk (cut_cmd, "cut", __builtin_object_size (cut_cmd, 2 > 1 ? 1 : 0));;

    char uIn[256];
    scanf("%s",uIn);

    if(strcmp(uIn,copy_cmd)==0){
        printf("We copy");
    }else if(strcmp(uIn,cut_cmd)==0){
        printf("We cut");
    }else if(strcmp(uIn,paste_cmd)==0){
        printf("We paste");
    }else{
        printf("Don't know!");
    }

    return 0;
}
```
