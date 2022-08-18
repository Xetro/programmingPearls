## Problem
**Input:** File containing at most *n* unique positive integers, each less then *n*, where *n*=10<sup>7</sup>

**Output:** Sorted list in increasing order of input integers

**Constraints:** At most (roughly) 1MB of storage in main memory; Ample disk storage available; Time effecient

## Solutions
+ Disk based Merge Sort. Using work files to store data instead of memory.
+ Multipass Sort. Read input file multiple times and sort the amount we can fit in memory each time (eg. 1st pass 0-249,999, 2nd 250,000-499,999...)
+ Bit Vector representation of a set. We can represent a set of nonnegative integers less then *n* by a string of *n* bits (eg. n=10, set {1, 3, 5, 9} = 0 1 0 1 0 1 0 0 0 1)

We chose Bit Vector as it's fastest and easiest to implement. A string of 10<sup>7</sup> bits translates to 1,25MB which is still inside our problem constraints and we can store everything in RAM. No work files or multiple read passes needed.

## Code

**unique.c** - Generates our input file with random numbers. Takes amount of numbers and max number of digits as input and generates a file named **randomnumsuniq** with random unique numbers in that range. To avoid duplicates we generate an array of integers, with length same as the max number possible and with values same as it's index position.
Then we iterate through it *n*-times (where *n* is the amount of numbers we want). Each iteration we pick a random number between current and last index position, we check the value on that random index position and swap it with one on our current position and print it out.

**start.c** - Implementation of our algorithm. Reads **randomnumsuniq** file and outputs sorted list to **sorted** file.
Uses bitwise logical operations to manipulate our set of bits. Hardcoded to our problem specification (*n*=10<sup>7</sup>).

**multipass.c** - More involved implementation, that will also take available memory size and max digits as input and will add multiple passes to our algorithm if neccesary.

**duplicates.c** - Evolution of multipass.c, which allows duplicates of same integer in our input (max 10).
Instead of flagging a single bit on/off, we use 4 bits to count its occurrences.
