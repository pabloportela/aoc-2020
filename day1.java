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


        // read the file numbers into a set
        Set<Integer> numbers = new HashSet<Integer>();
        for (String line: readLines(args[0])) {
            numbers.add(Integer.parseInt(line));
        }

        // iterate and find first pair satisfying the equation "a + b = 2020"
        int target_sum = 2020;
        for (Integer n: numbers) {
            if (numbers.contains(target_sum - n)) {
                int solution = n * (target_sum - n);
                System.out.println(solution);
                break;
            }
        }
    }
}
