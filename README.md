## Environment

OS:

* OS X EI Capitan 10.11.4
* MacBook Pro (Retina, 13-inch, Early 2015)
* Processor 2.7 GHz Intel Core i5
* Memory 8 GB 1867 MHz DDR3

java:

```
$ java -version
java version "1.8.0_131"
Java(TM) SE Runtime Environment (build 1.8.0_131-b11)
Java HotSpot(TM) 64-Bit Server VM (build 25.131-b11, mixed mode)
```

Python

```
$ python --version
Python 2.7.10
```

g++

```
$ test_jit g++ --version
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 7.3.0 (clang-703.0.31)
Target: x86_64-apple-darwin15.4.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

## Code

c++

```cpp
#include <string>
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

class TestJIT {
    public:
        TestJIT(int times) {
            this->times = times;
        }
        void start() {
            log("Test started");
        }
        void finish() {
            log("Test finished");
        }
        int run() {
            int result = 0;
            for (int i = 0; i < this->times; ++i) {
                for (int j = 0; j < this->times; ++j) {
                    result += i * j + i - j;
                }
            }
            return result;
        }
    private:
        int times;
        void log(string message) {
            cout << message << endl;
        }
};

void print_progress(int done, int total) {
    printf("%lf%%\n", done * 1.0 / total * 100);
}

int main(int argc, char **argv)
{
    assert(argc > 1);
    TestJIT test = TestJIT(1000);
    test.start();
    int times = atoi(argv[1]);
    for (int i = 0; i < times; ++i) {
        test.run();
        if (i % 100 == 0) {
            print_progress(i + 1, times);
        }
    }
    test.finish();
    return 0;
}
```

java

```java
import java.util.Date;

public class TestJIT {
    private int times;

    public TestJIT(int times) {
        this.times = times;
    }

    private void log(String message) {
        System.out.printf("%s %s\n", new Date(), message);
    }

    public int run() {
        int result = 0;
        for (int i = 0; i < this.times; ++i) {
            for (int j = 0; j < this.times; ++j) {
                result += i * j + i - j;
            }
        }
        return result;
    }

    public void start() {
        log("Test started");
    }

    public void finish() {
        log("Test finished");
    }

    public static void printProgress(int done, int total) {
        System.out.printf("%f%%\n", (double)done / (double)total * 100);
    }

    public static void main(String[] args) {
        assert args.length > 0;
        TestJIT test = new TestJIT(1000);
        test.start();
        int times = Integer.parseInt(args[0]);
        for (int i = 0; i < times; ++i) {
            test.run();
            if (i % 100 == 0) {
                printProgress(i + 1, times);
            }
        }
        test.finish();
    }
}
```

python

```python
from datetime import datetime
import sys


class TestJIT:

    def __init__(self, times):
        self.times = times

    def run(self):
        result = 0
        for i in range(self.times):
            for j in range(self.times):
                result += i * j + i - j
        return result

    def start(self):
        self.log("Test started")

    def finish(self):
        self.log("Test finied")

    def log(self, message):
        print("%s %s" % (datetime.now(), message))


def print_progress(done, total):
    print("%f%%" % (done * 1.0 / total * 100))


def main():
    assert len(sys.argv) > 1
    test = TestJIT(1000)
    test.start()
    times = int(sys.argv[1])
    for i in range(times):
        test.run()
        if i % 100 == 0:
            print_progress(i + 1, times)
    test.finish()


if __name__ == "__main__":
    main()
```

test startup script:

```sh
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
```

## Result

```
./run_test.sh 1234
```

Result:

```
C++
real	0m3.805s
user	0m3.779s
sys	0m0.012s

Java with JIT
real	0m0.916s
user	0m0.837s
sys	0m0.053s

Java without JIT
real	0m21.536s
user	0m20.961s
sys	0m0.197s

Python
real	1m53.462s
user	1m52.782s
sys	0m0.292s

Pypy
real	0m2.455s
user	0m2.347s
sys	0m0.058s
```

| language | has JIT | spend time |Optimized parameter|
|----------|---------|------------|-------------------|
| C++      | No      | 3.8        | -                 |
| java     | Yes     | 0.9        | -                 |
| java     | No      | 21.5       | -                 |
| python   | No      | 113        | -                 |
| pypy     | Yes     | 2.4        | -                 |
