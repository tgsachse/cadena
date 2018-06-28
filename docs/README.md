# cadena
This small library provides the `Cadena` class, implemented using a doubly-linked list of characters. Cadenas support many operations:
- prepend
- append
- insert
- delete†
- replace†
- search


*†coming soon!*

# usage
To download this program, clone this repository using `git` like so:
```
git clone https://www.github.com/tgsachse/cadena.git
```
To use the example program included in this repository, execute the `run.sh` script and provide two arguments. The first argument must be the text file you'd like to create a cadena from, and the second argument must be the string you'd like to find in the cadena. The program will then print out the number of occurences of that string in the cadena. This number is determined using the [Knuth-Morris-Pratt](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) string search algorithm.

Here's an example of using the `run.sh` script to find the string `Rick` in the file `examples/rick_and_morty.txt`:
```
./run.sh examples/rick_and_morty.txt Rick
```

# complexity
Below is a table of space and runtime complexities for all operations:

| Operation    | Best-Case Runtime | Average-Case Runtime | Worst-Case Runtime |
| :----------: | :---------------: | :------------------: | :----------------: |
| Construction |        O(k)       |         O(k)         |        O(k)        |
| Prepend      |        O(1)       |         O(1)         |        O(1)        |
| Append       |        O(1)       |         O(1)         |        O(1)        |
| Insert       |        O(1)       |         O(n)         |        O(n)        |
| Delete       |        O(1)       |         O(n)         |        O(n)        |
| Replace      |        O(k)       |         O(n+k)       |        O(n+k)      |
| Search       |        O(n)       |         O(n)         |        O(n)        |
| Destruction  |        O(n)       |         O(n)         |        O(n)        |

`k` is the number of characters in a string passed to the function. `n` is the number of characters in the cadena. The space complexity of the cadena is `O(n)`.
