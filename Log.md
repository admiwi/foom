As for IO, I'm hoping to abstract everything thing as much as possible
such that something like this will be possible:

```
File.new("c:/test.txt").each { line :  println line }
```
-or-
```
stdin.each { l : println l }
```

IO will be OS aware -- rather it will know DOS has `\` for directory
separators, `\r\n` for newline and that sort of thing.

The `assert` idea comes directly from Groovy.  They really focused on
testing driven design.

I have thought about scope a bit and I'm getting into trouble with the
idea of everything being a closure. Ideally, I would like every `{}` to
be a function.  So a `for-loop` would become `for(init;condi;seq) func` --
but that's tough.

Let suppose we have a `loop` operator.  `loop` takes three closures: block
before the predicate, the predicate, and block after the predicate.
The predicate will be executed each time and is expected to return a boolean.
loop will be declared as such:
```
void loop(func pre, func pred, func post)
```
and used like:
while...
```
loop {}{i<10} { print "Hi"}
```
do..while...
```
loop { prinln "Hi" } { if i<10; return false; else i++; return true;} {}
```

The for-loop
```
for(int i = 0; i<10; ++i) {  println i }
```
would be syntactic sugar for
```
{ int i = 0;
loop {} { if i<10; return false; else ++i; return true;} { println i }
}
```

loop doesn't actually have to exist, it just demonstrates the scoping issues.

`{}` bound scope -- essentially, functions bound scope.  Variables
defined in the same, or higher, scopes as a function can be seen
within the function.  Objects in the inner scope with the same name
override the outer scope without destruction, however, if one does
this, they lose the ability to access the object of that name within
the scope. args will always be local.  I think packages and imports
would be necessary to keep the scope uncluttered.  I'll probably adopt
Pythons idea behind modules/packages being based on a directory
structure and special initialization file.  It seems like a fairly
reasonable way of keeping things straight.

The functions are very similar with the exception the type binding,
incoming and outgoing.
`func f = { 10 }`  isn't explicitly bound to return an `int`.


Beginning to think I should keep all classes upper case -- even the base classes.  Lowercase like in C gives the impression that they are above being a normal class -- which is true to some extent, I guess.  They are the foundation.

Another idea, I want everything to be extensible.
```
  Decimal.toDollars = { "$%{self:.2f}" }
  assert 10.5.toDollars() == "$10.50"
```
This also introduces string interpolation/formating.  Sorta like sprintf style except the variable is in `{}`, followed by a `:` with the sprintf formating characters following.

Along with the extensibility comes the possibility of overloading.
```
  assert "a":"b" == "ab"
  String.`:` = { args[1].concat(args[0]) }
  assert "a":"b" == "ba"
```
Which brings me to the `.base` member of classes -- and everything else...
The above could be rewritten as...
```
  String.`:` = { String.base.`:`(args[1],args[0]) }
  assert "a":"b" == "ba"
```
As you can see, you can access operators functions by using the backticks.  All operators can be overloaded except dot(.), quotes(") and backticks(`).

I had expressed the desire for maps and lists be the same thing, just a little more information attached to a map.  With the current syntax, a map would look like this:
```
  map m = ["foo":"bar"]
  assert m["foo"] == "bar"
  assert m[0] == "bar"
```
The trouble starts when you use integers as the key...
```
  map m = [1:"foo",0:"bar"]
  assert m[0] == ???  
```
One way around this would be to use a different syntax for accessing list/maps via keyword.
```
  map m = [1:"foo",0:"bar"]
  assert m[0] == "foo"
  assert m<0> == "bar"
```
However, iteration becomes less intuitive.  Still need to think about this.
```
  for k, v in ["1":"foo",0:"bar"] {
    assert k is int  // would this fail?
  }
//(hmm which construct....
  for ["1":"foo",0:"bar"] { k,v:
    assert k is int  // would this fail?
  }
```

I still think I may need tuples....
```
assert <1> is tuple
int a = 1, b = 2, c = 3
<a,b,c> = <c,b,a>
assert a == 3
<a,b,c> = 1,2,3,4
assert c == [3,4]
```
A bare list on the left would be treated as a tuple -- on the right, a list.
```
  int a = 1, b = 2, c = 3
  a,b,c = c,a,b

```

# Update #

First update of this document in a long time -- a tremendous amount of work done.  Most of the above is depreciated.

Grammar changed a bit.  I am now requiring a semicolon at the end of a statement.
See [Documentation](Documentation.md).

Some interesting points about foom so far:

Foom performs lazy execution.  Functions are defined as variables of `func` type and are assigned a block.  But due to the lazy execution, you can refer to the variable name within the block, thus making the function recursive.  Check out `tests\qsort.fm`.  The `sort` function calls itself.  Oddly enough, this wasn't explicitly by design -- more of "it just worked" when I tried it.  I hope to expand this idea to list comprehensions such that they may refer to themselves and do functional style Fibonacci series.

Call-back, or closures, as seen in `tests\functions.fm`, took complete refactoring of the scope system.  Originally, most AST nodes had an attached scope.  That appeared to work, however, functions retained their scope through multiple calls -- as if, let's say in C, everything was declared `static`.  This isn't what I wanted.  So I tried to attach a new scope to each function and changed the context when the function was called.  This approach failed miserably due to a scope pointer was attached to **each** AST node.  I would have had to descend the AST and replace the pointer on each node prior every function call.  It was obvious that I had to move the scope to the the functions that actually performed the evaluation.  Now every `*feval*` function takes a scope pointer as an argument.  The function call function creates a new scope tree for each call.  Probably not very space efficient, but it allows functions to return functions is a sane way.