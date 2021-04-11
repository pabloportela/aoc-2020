import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;


public class day1 {

    private static ArrayList<String> readLines(String filename) throws IOException {
        FileReader fileReader = new FileReader(filename);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        ArrayList<String> lines = new ArrayList<String>();
        while ((line = bufferedReader.readLine()) != null) {
            lines.add(line);
        }

        return lines;
    }

    public static void main(String []args) throws NumberFormatException, IOException {
        part1(args[0]);
        part2(args[0]);
    }

    private static void part1(String filename) throws NumberFormatException, IOException {
        // read the file numbers into a set
        Set<Integer> numbers = new HashSet<Integer>();
        for (String line: readLines(filename)) {
            numbers.add(Integer.parseInt(line));
        }

        // iterate and find first pair satisfying the equation "a + b = 2020"
        int target_sum = 2020;
        for (Integer a: numbers) {
            if (numbers.contains(target_sum - a)) {
                int solution = a * (target_sum - a);
                System.out.println("Part 1: " + solution);
                return;
            }
        }
    }

    private static void part2(String filename) throws NumberFormatException, IOException {
        // read the file numbers into a set
        Set<Integer> numbers = new HashSet<Integer>();
        for (String line: readLines(filename)) {
            numbers.add(Integer.parseInt(line));
        }

        // iterate and find first pair satisfying the equation "a + b + c = 2020"
        int target_sum = 2020;
        for (Integer a: numbers) {
            for (Integer b: numbers) {
                int c = target_sum - a - b;
                if (numbers.contains(c)) {
                    int solution = a * b * c;
                    System.out.println("Part 2: " + solution);
                    return;
                }
            }
        }
    }
}
