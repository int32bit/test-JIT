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
