import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


public class day2 {

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
        countValidPasswords(args[0]);
    }

    private static boolean isValidPasswordPart1(int min_tokens, int max_tokens, char token, String password) {
        int q_tokens = 0;
        for (int i=0; i<password.length(); i++) {
            if (password.charAt(i) == token) {
                q_tokens++;
            }
        }

        return (q_tokens >= min_tokens && q_tokens <= max_tokens);
    }

    private static boolean isValidPasswordPart2(int first_pos, int second_pos, char token, String password) {
        return
            password.length() >= first_pos &&
            password.length() >= second_pos &&
            (password.charAt(first_pos-1) == token ^ password.charAt(second_pos-1) == token)
        ;
    }

    private static void countValidPasswords(String filename) throws NumberFormatException, IOException {
        // read lines
        ArrayList<String> lines = readLines(filename);

        // parse and count valid ones
        int q_valid_part_1 = 0;
        int q_valid_part_2 = 0;

        for (String line: lines) {
            // parse line
            String[] parts = line.split(" ");
            String[] bounds = parts[0].split("-");
            int first = Integer.parseInt(bounds[0]);
            int second = Integer.parseInt(bounds[1]);
            char token = parts[1].charAt(0);

            // count valid passwords for both parts
            if (isValidPasswordPart1(first, second, token, parts[2])) {
                q_valid_part_1++;
            }
            if (isValidPasswordPart2(first, second, token, parts[2])) {
                q_valid_part_2++;
            }
        }

        System.out.println("Number of valid passwords for parts 1 and 2 respectively: " + q_valid_part_1 + " and " + q_valid_part_2);
    }
}
