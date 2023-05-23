# Atomic Reference Counted Smart Pointers in C

Included a basic implementation of persistent lists as an example of how to use them.

The convention here is that `Arc`s are considered an "owner" of their internal data,
taking on the convention that a pointer to an `Arc` is a borrow of their internal data.
If your function receives an `Arc*`, you know you aren't responsible for dropping it,
but if it receives an `Arc` then you are responsible for dropping it. If you clone it,
then you also are responsible for dropping the cloned copy.
