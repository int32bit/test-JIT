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
