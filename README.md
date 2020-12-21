# Scheduling Algorithms

Rate Monotonic, Deadline Monotonic and Early Deadline Frist implemented in C++ to the Real Time Systems discipline in Federal University of Ceará. 

To build, simply:

    make

To run:

    ./bin/app <taskset> <method>

where taskset is any file in format:

    P   C   D
    #   #   #
    .   .   . 

P = period, C = computatinal time and D = Deadline

method is either: `rm`, `dm` or `edf` (case unsensitive)