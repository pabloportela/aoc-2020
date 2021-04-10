import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;


public class day1 {

    public static void main(String []args) throws IOException, NumberFormatException {
        FileReader fileReader = new FileReader(args[0]);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        Set<Integer> numbers = new HashSet<Integer>();
        int target_sum = 2020;

        // read the file numbers into a set
        while ((line = bufferedReader.readLine()) != null) {
            numbers.add(Integer.parseInt(line));
        }

        for (Integer n: numbers) {
            if (numbers.contains(target_sum - n)) {
                int solution = n * (target_sum - n);
                System.out.println(solution);
                break;
            }
        }
    }
}
