foom will be a lightweight, general purpose scripting language that is similar enough to C and Java that it should be fairly easy to learn.

foom may end up having the following features:
  * dynamic language
  * C-like syntax
  * optional typing
  * first-class functions
  * everything is an object
  * closures
  * continuations
  * mixins
  * currying
  * list comprehensions
  * data types
    * [object](objectType.md) obj
      * [integer](integerType.md) int
      * [decimal](decimalType.md) dec
      * [string](stringType.md) str (multibyte?)
      * [binary](binaryType.md) bin (like a c-string, but safer)
        * [struct](structType.md)
        * [union](unionType.md)
      * [func](functionType.md) {}
      * [list](listType.md) [.md](.md)
      * [map](mapType.md) [:]
      * [tup](tupleType.md) <>  # mebbe... thinking about it

## Variables and DataTypes ##

```
  obj o
  assert o.class == obj  #
  assert o is obj
  assert o.class.name == 'obj'

  int a = 12
  assert a is int
  assert a was obj

  dec b = 12.0
  assert b is dec

  str c = "12"
  assert c is str

  assert a as str == "12"
  
  str d = '12'
  assert d is str
  
  list e = [12, 12]
  assert e is list
  assert e[0] == 12
  assert e.count == 2
  assert e.keys == [0,1]
  assert ![]
  assert 1,2,4 is list

  map f = [o: 12]
  assert f is map
  assert f.keys == [o]

  assert func {} is func
  func g = { 12 }
  assert g is func
  assert g() == 12
  assert g.call() == 12

  func h(){ 12 }
  assert h is func
  assert h() == 12

  func i(j){ j as str }
  assert i(12) == "12"
  assert i 12 == "12"

  assert int k == new Int()
  
```

## Statements ##
Statements

## Expressions ##

## Functions ##
Defining a function is done in two different ways:  traditional C like
fashion, assigning a lambda/closure to a function object. A C-like function
definition may be prefaced with `func` denoting the function type.  A function
variariable must be declared as a `func` type. Arguments may be defined
explicitly or access through the local special variable `args`.  Explicit
arguments must be typed, but may use the `obj` base object for duck typing.
The last expression evaluated in a function will be the return value. A value
may explicitily returned using the the `return` keyword followed by an
expression. The return type in in C-like function declarations is optional.
Arguments to a lambda may be declared as a list, following a colon.
```
  int f(int a){
    return a + 2
  }
  func f(a){
    return a + 2
  }
  func f = {
    return args[0] + 2
  }
  func f = { a:
    return a+2
  }
```