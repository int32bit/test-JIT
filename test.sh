#!/bin/sh

run_test()
{
    if [ $# -lt 1 ]; then
        echo "Usage: $0 <times>"
        exit 1
    fi

    echo "C++"
    g++ TestJIT.cpp -o TestJIT
    time ./TestJIT $1
    echo

    echo "Java with JIT"
    time java -ea TestJIT $1
    echo

    echo "Java without JIT"
    javac TestJIT.java
    time java -ea -Djava.compiler=NONE TestJIT $1
    echo

    echo "Python"
    time python TestJIT.py $1
    echo

    echo "Pypy"
    time pypy TestJIT.py $1
    echo
}

run_test $@ 2>&1 | tee result.txt
