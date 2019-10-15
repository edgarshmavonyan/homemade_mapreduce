### My homemade MapReduce.

Supported operations are
1. Map, having key-value output.
2. MapReduce, taking 1st operation and Reducing to key-value.

There is not much work to implement standalone reduce, or some other types of operations in MR paradigm, as I tried to implement it scalable and having a nice friendly interface.

Now only MR can be run from command line, and both Map and MR can be run by user with needed arguments, but that can be easily implemented.

P.S. This is heavily inspired by MR interfaces in production, that I've met.
