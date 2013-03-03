Channel
=======

Channel is an attempt for implementing channels like golang offers. I've considered them to be useful from the first moment I've seen them, so here is an exemplary implementation for C++ :)

Once again, the given code requires a rather new compiler. I've tested it with GCC 4.7.1 on Windows, 4.6.3 on Ubuntu and with XCode 4.5.1 on OSX.
Note: Most parts can easily be implemented using Boost, since the API is quite close to what the current C++ standard offers (regarding mutex, lock_guard, thread, etc.).

Note:
====
This package is now part of https://github.com/DorianGrey/Concurrent, so it will be maintained there.
