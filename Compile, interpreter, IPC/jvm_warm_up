import java.security.MessageDigest;
import java.nio.charset.StandardCharsets;

public class SHA256Warmup {

    private static final String MESSAGE = "";

    public static void main(String[] args) {
        SHA256Warmup warmup = new SHA256Warmup();

        System.out.println("--- 웜업 전 실행 ---");
        printResult(warmup);

        // 웜업 횟수를 인자로 전달
        System.out.println("\n--- 웜업 중 (50000회 반복) ---");
        warmup.runWarmup(50000);

        System.out.println("\n--- 웜업 후 실행 ---");
        printResult(warmup);

        System.out.println("\n--- 추가 웜업 중 (1000000회 반복) ---");
        warmup.runWarmup(1000000);

        System.out.println("\n--- 최종 실행 ---");
        printResult(warmup);
    }

    private static void printResult(SHA256Warmup warmup) {
        long startTime = System.nanoTime();
        warmup.method();
        long endTime = System.nanoTime();
        System.out.println("time: " + (endTime - startTime));
    }

    /**
     * JVM 웜업을 위해 반복적으로 호출될 메서드
     * @param count 웜업 반복 횟수
     */
    public void runWarmup(int count) {
        for (int i = 0; i < count; i++) {
            method();
        }
    }

    /**
     * JIT 컴파일러에 의해 최적화될 대상 메서드
     */
    public void method() {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] encodedhash = digest.digest(MESSAGE.getBytes(StandardCharsets.UTF_8));
            bytesToHex(encodedhash);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }
}
