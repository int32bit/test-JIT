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
