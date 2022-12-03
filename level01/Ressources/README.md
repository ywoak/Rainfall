https://stackoverflow.com/questions/30972544/gdb-exiting-instead-of-spawning-a-shell

FROM gets() man
```
Bugs
Never use gets(). Because it is impossible to tell without knowing the data in advance how many characters gets() will read, and because gets() will continue to store characters past the end of the buffer, it is extremely dangerous to use. It has been used to break computer security. Use fgets() instead.
It is not advisable to mix calls to input functions from the stdio library with low-level calls to read(2) for the file descriptor associated with the input stream; the results will be undefined and very probably not what you want.
```