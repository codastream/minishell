## syntax

| Test | Code | Output | Fichiers | Notes |
| ---- | ---- | -------| -------- | ----- |
| `<<<<<<<<<<<<<<<<` | 2 | `syntax error near unexpected token ``<<<'`|-|shows `<<`|
|`$USER`|127| `user: command not found`|-|139 with GA but 127 otherwise|
|`<< EOF cat`|?|``|-|-|
|`cat << EOF`|?|``|-|-|
|`echo -n a`|0|``|-|tester removes `\n`|
|`export MAVAR="hello"` puis `echo $MAVAR`|0|``|-|-|
|`echo tata''toto titi`|0|`tatatoto titi`|-|-|
|`env a`|2|``|-|subject differs from bash|
|``|0|``|-|-|
|``|0|``|-|-|
|``|0|``|-|-|


