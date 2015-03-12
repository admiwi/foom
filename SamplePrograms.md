# Hello World #
```
println "Hello World"
```

# Print Random Line from File #
```
Rand rnd = sys.Rand();
str line
File("/some/file.txt").eachIndex { str ln, int i : line = (rnd.get(i+1) < 1)? ln : line }
println line
```

# Fibonacci Sequence #
Ideally, I would like lazy evaluation.
```
list fib = [1,2,(a+b for a in fib[1..], for b in fib)]
```
This also demonstrates the difference between `[x,y,z]` and `x,y,z` as lists.  Perhaps I need an operator or something to explode the list -- I'm not sure, but nonetheless, I would like functions to be able to add raw elements to a list by putting them inline.  Mebbe a list buider operator would be better.  Something like Haskell's `:`
```
list fib = 1:2:[a + b for a in fib[1..], for b in fib]
```

# Conditionals #
```
switch(foo) {
  case str:  //match against classes
    println foo
    break;
  case 10.0:  //can be anything....
    println "Perfect 10!"
    break;
  case int:
    foo += 100  //changing the value of foo, will be considered lower in switch
    break
  case { args[0] > 100 and args[0] < 1000}: // can pass function, case is first argument
    print "Impressive "  // no break.. will get "Impressive Tan"
  case { foo was Copper }: // foo is still in scope...
    println "Tan"
    break
  default:  // if nothing else matched...
    println "moof"
}
```
```
if(foo > 10 and != 'car') { //{ are required
  println "not car or 10"
} else if(foo was int) {  // chained like C
  println "but it was a number..."
} else {
  println "but it's some class "+foo.class.name
}
```