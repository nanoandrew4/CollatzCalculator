# CollatzCalculator

I was watching a Numberphile video and thought I could implement a fast way to determine the number of steps any number must take to reach 1, by halving when the number is divisible by two, and multiplying by three and adding one
otherwise.

All attempts at using data structures to help speed up the program failed, which was quite baffling, since I thought using a map might reduce the workload significantly, among other ideas. That may have been true had no compiler 
optimizations been used, but the current program takes advantage of them, and brute force is oddly enough the fastest method, by far. This program can calulate the maximum number of steps taken for a sequence of numbers 
(you must indicate the start and end points of the sequence), or the number of steps taken for a single number (which thanks to the GMP library, can be veeeery large).
