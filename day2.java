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
        part1(args[0]);
    }

    private static boolean isLineValid(String line) throws NumberFormatException{
            String[] parts = line.split(" ");
            assert parts.length == 3;
            String[] bounds = parts[0].split("-");
            return isPasswordValid(
                Integer.parseInt(bounds[0]),
                Integer.parseInt(bounds[1]),
                parts[1].charAt(0),
                parts[2]
            );
    }

    private static boolean isPasswordValid(int min_tokens, int max_tokens, char token, String password) {
        int q_tokens = 0;
        for (int i=0; i<password.length(); i++) {
            if (password.charAt(i) == token) {
                q_tokens++;
            }
        }

        return (q_tokens >= min_tokens && q_tokens <= max_tokens);
    }

    private static void part1(String filename) throws NumberFormatException, IOException {
        // read lines
        ArrayList<String> lines = readLines(filename);

        // parse and count valid ones
        int q_valid = 0;
        for (String line: lines) {
            if (isLineValid(line)) {
                q_valid++;
            }
        }

        System.out.println("Number of valid passwords: " + q_valid);
    }
}
