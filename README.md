# Brief
orb (operate with readable binaries) is the language and the tool for binary files manipulation through plain text.

# Grammar

``` ebnf
expr ::= comment | definition
comment ::= # <some text> <new line>
definition ::= manual_def | auto_def
manual_def ::= value : type [;]
auto_def ::= value;
value ::= decimal_val | hex_val | bin_val
decimal_val ::= 0d<digits> | <digits>
hex_val ::= 0x<digits>
bin_val ::= 0b<bits>
type ::= sign length
sigh ::= u | s
length ::= value
```
