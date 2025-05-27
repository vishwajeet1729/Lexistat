[Keyword] int
[Identifier] main
[Separator] (
[Separator] )
[Separator] {
[Keyword] int
[Identifier] x
[Operator] =
[Constant] 5
[Separator] ;
[Keyword] float
[Identifier] y
[Operator] =
[Constant] 3.14
[Separator] ;
[Identifier] x
[Operator] =
[Identifier] x
[Operator] +
[Constant] 10
[Separator] ;
...

Symbol Table
------------
Name: main, Type: int, Scope: 0, Declared: 1, Usage: declaration 
Name: x, Type: int, Scope: 1, Declared: 2, Usage: declaration usage, Referenced at: 4 
Name: y, Type: float, Scope: 1, Declared: 3, Usage: declaration 
...

No lexical errors found.
