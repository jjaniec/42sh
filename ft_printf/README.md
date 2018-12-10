# ft_printf [![Build Status](https://travis-ci.org/jjaniec/ft_printf.svg?branch=master)](https://travis-ci.org/jjaniec/ft_printf)

## What's ft_printf ?

The goal of this project was to recode the famous printf C function to learn variadic functions and to improve my algorithmic methodology
```c
int printf(const char * (restrict) format, ...);
```

You can print content of a passed parameter by using the following syntax:
```c
%[flag][min width].[precision][length modifier][conversion specifier]
```

## Features

The following conversions are supported:
```c
s: char *
S: wchar_t *
p: void * (to print address of a pointer)
d / i: int
D: intmax_t
o/O: unsigned int/long int to octal output
u/U: unsigned int/unsigned long int
x/X: unsigned int/long int to hexadecimal output
c: char
C: wchar_t
```

You can also change input types with the following length modifiers:
```c
h/hh/l/ll/j/z
```

Use the usual flags:
```text
-       Left justify.
0       Field is padded with 0's instead of blanks.
+       Sign of number always O/P.
blank   Positive values begin with a blank.
#       Various uses:
  %#o        0 prefix inserted.
  %#x        0x prefix added to non-zero values.
  %#X        0X prefix added to non-zero values.
```

And specify width and precision to adapt your output

### Bonus

#### Colors

Output can be colored with the following tags:
```text
{FG_COLOR}: to specify a foreground color
{BG_COLOR}: for a background color
```
and replace COLOR by one of the following:
```python
DEFAULT
BLACK
WHITE
LIGHT_GREY
DARK_GREY
(LIGHT_)RED
(LIGHT_)GREEN
(LIGHT_)YELLOW
(LIGHT_)BLUE
(LIGHT_)MAGENTA
(LIGHT_)CYAN
```

An invalid color specifier will cause it to be skipped

#### Added conversions

```c
b: int to binary output
```

## Trying it

First, clone the project,
```sh
git clone https://github.com/jjaniec/ft_printf
cd ft_printf
```

then `make` the project and compile your files with the generated ```libftprintf.a``` and by adding
```c
#include "ft_printf.h"
```
and use it like the real printf function
