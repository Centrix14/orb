# Brief
orb (operate with readable binaries) is the language and the tool for binary files manipulation through plain text.

# Grammar

``` ebnf
expr ::= comment | definition
comment ::= # <some text> <new line>
definition ::= manual_def | auto_def
manual_def ::= value : type [;]
auto_def ::= value;
value ::= dec_val | hex_val | bin_val
dec_val ::= <digits>
hex_val ::= 0x<digits>
bin_val ::= 0b<bits>
type ::= sign length
sigh ::= u | s
length ::= value
```

# Roadmap
- [ ] vreader - value reader
  - [ ] base interface
    - [ ] token write bounds check
  - [ ] decimal reading
  - [ ] hexidecimal reading
  - [ ] binary reading
  - [ ] stopping
- [ ] treader - type reader
