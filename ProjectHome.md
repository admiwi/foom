Foom was designed with a few core ideas.

·       It must have C-style syntax.  For better or worse, many of today’s programming languages have derived or borrowed aspects of their syntax from C. Doing so decreases the learning curve allowing broader adoption of the language.

·       Everything is an object. Most programming languages have a set of primitive data types such as strings, integers, floating point numbers, and Boolean values.  In Foom, all of these, with the addition of functions and types, are classes. They all have properties that can be accessed and manipulated.

·       All curly brackets ({ }) are anonymous functions. This is a departure from C-style syntax to some extent.  C uses curly brackets to limit scope and define blocks of code. Foom follows this convention; however, code within bare curly brackets is not executed until it is called, as it is a function.

·       Variables are lexically-scoped.  The context of a variable can be found by reading the text of the program and noting the location of the declaration.

·       Functions are first-class objects.  As mentioned above, functions are objects, which can be passed to other functions and stored in data structures.  They can also be created by other functions encapsulating their scope producing what is called a closure.



See more in Foom [Documentation](Documentation.md).

Quicksort (`tests\qsort.fm`):
```
foom.import("sys");
list data = [3,1,20,4,7,2];

func printlist = {
  list l = args[0];
  sys.print("[");
  for(int i = 0; i < l.length; i = i + 1) {
    sys.print(l[i]);
    if(i < l.length - 1)
      sys.print(", ");
  }
  sys.println("]\n");
};
func swap = {
  list l = args[0];
  int t = l[args[1]];
  l[args[1]] = l[args[2]];
  l[args[2]] = t;
  l;
};

func sort = {
  list d = args[0];
  int b = args[1];
  int e = args[2];
  if(e > b + 1) {
    int piv = d[b];
    int l = b + 1;
    int r = e;
    for(0;l < r;0) {
      if(d[l] <= piv) {
        l = l + 1;
      } else {
        r = r - 1;
        swap(d, l, r);
      }
    }
    l = l - 1;
    swap(d, l, b);
    sort(d, b, l);
    sort(d, r, e);
  }
};

printlist(data);
sort(data, 0, data.length);
printlist(data);
```
Produces:
```
foom tests/qsort.fm 
[3, 1, 20, 4, 7, 2]

[1, 2, 3, 4, 7, 20]
```