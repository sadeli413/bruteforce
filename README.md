# bruteforce

A brute force algorithm that uses crypt.h and loops through every possible string.
For example:
```
aaa
aab
aac
```
etc...

Since there are 94 ascii characters\
```!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~```
You can treat a brute force algorithm like a base 94 counting system, where ```! == 0``` and ```~ == 93``` and so forth.\
To do this base 94 system, loop through each digit in you number, and keep track of your places. In base ten, that is ones place, tens place, hundreds place, etc. In base 94 that is ones place, 94 place, 94^2 place, 95^3 place, etc. So as you loop, keep track of total count. For example, every 94^4 time, the fourth digit to the right increments by one. Every 94^1 time, the first digit to the right increments by one every 94^0 time, the rightmost digit increments by one (that's every time)\
Besides keeping track of total count and places, you need to keep track of the size, where the size is the number of digits. Every 94^size time, add another ! digit to the left.\
In **words.c** this is represented with the leftmost column is the total count, the middle column is the base 10 representation, and the rightmost column is the base 94 representation.\
In **encrypt.c**, an input hash is encrypted with an input salt using crypt.h\
In **brute.c** each ascii string produced by the base 94 is encrypted with the input salt with crypt.h and is compared with an input hash. When a match is found, the program stops.
