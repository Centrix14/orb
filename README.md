# Brief
orb (operate with readable binaries) is the language and the tool for binary files manipulation through plain text.

# Grammar

``` ebnf
expr ::= comment | definition
comment ::= # <some text> <new line>
definition ::= manual_def | auto_def
manual_def ::= value : type ;
auto_def ::= value ;
value ::= dec_val | hex_val | bin_val
dec_val ::= <digits>
hex_val ::= 0x<digits>
bin_val ::= 0b<bits>
type ::= length measure
length ::= value
measure ::= b | B
```

# Roadmap
- [x] vreader - value reader
  - [x] base interface
  - [x] decimal reading
  - [x] hexidecimal reading
  - [x] binary reading
  - [x] stopping
- [x] mreader - measure reader
- [x] refactor - unify vreader and mreader implementation
- [x] treader - type reader
- [ ] dreader - definition reader
