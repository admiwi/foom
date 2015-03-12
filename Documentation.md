# Foom #

Foom is a dynamically typed, lazily interpreted language.  Most statement are terminated with a `;` with the exception of `for` and `if`/`else`.
For examples, please take a look at the [tests](http://code.google.com/p/foom/source/browse/#svn/trunk/tests) directory in the source.

## Datatypes ##

There are five basic types in Foom:
  * `int` -- integer, internally a long
    * `to_string` method returns string representation of number
  * `str` -- strings
    * two types:
      * interpolated strings surrounded by double quotes (`"`) interpolate standard C-sytle slash codes
      * raw strings surrounded by single quotes (`'`) only interpret the slash code `\'`
    * `length` member that returns the strings length
    * `to_string` method that returns itself
  * `list` -- an array list --  a bare list is contained in `[]`
    * `subscript` method allows indexing of lists using brackets and starting with 0
      * `l[2]` retrieves the 3rd element
      * a series of numbers separated by commas in brackets returns a subset of the list, e.g. `l[1,2,4]` returns a list containing the 2nd, 3rd, and 5th elements. (Currently, the series of numbers must be in ascending order).
    * `length` member retrieves the number of elements in the list
  * `func` -- function type
    * raw function is contained in a `{}` block
    * functions must have an argument regardless if it's used
  * `obj` -- base object
    * primarily used internally at this point


## Variables ##
Variables are declared with a primary data type as such:
```
str s;
int i = 10;
list l = [2, i, 39];
func f;
f = { args[1]; };
```
Currently, one declaration per statement.

## Comments ##
Currently nonexistent.  Planning on # to ignore rest of line. Maybe ## for blocks.

## Functions ##
Functions are declared using the `func` keyword, setting the variable to a block.  The block is only evaluated when the function is called so using the function variable name in the block, thus a recursive function, will behave as expected.  Arguments to the function are passed in as list called `args`.  All variables are currently passed by reference.  The last statement in a function is the function's return value.  Functions are assignment statements thus must end with a `;`.
(Per [Bug 1](http://code.google.com/p/foom/issues/detail?id=1), all functions require arguments.)

The following function takes three arguments: a list L, integer A, and integer B.  It swaps position A in list L with position B and returns L at the end.
```
func swap = {
  list l = args[0];
  int t = l[args[1]];
  l[args[1]] = l[args[2]];
  l[args[2]] = t;
  l;
};
```

## Libraries ##
### foom ###
foom is imported automatically:
  * `foom.import("lib")` -- imports library dlls/foom\_lib.dll to name lib
  * `foom.import("lib","alias")` -- imports library dlls/foom\_lib.dll to name alias

### sys ###
sys contains various systems functions:
  * `sys.print()` -- prints argument
  * `sys.println()` -- prints argument followed by a newline
  * `sys.rand()` -- returns a random positive integer or zero
  * `sys.rand(k)` -- returns a random integer from 0 to k