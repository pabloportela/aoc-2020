import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


public class Field {

    private ArrayList<ArrayList<Boolean>> field;

    private ArrayList<String> readLines(String filename) throws IOException {
        FileReader fileReader = new FileReader(filename);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        ArrayList<String> lines = new ArrayList<String>();
        while ((line = bufferedReader.readLine()) != null) {
            lines.add(line);
        }

        return lines;
    }

    Field(String filename) throws IOException {
        this.field = new ArrayList<ArrayList<Boolean>>();

        // pase file, create field
        for (String line: readLines(filename)) {
            ArrayList<Boolean> row = new ArrayList<Boolean>();
            for (int i=0; i<line.length(); i++) {
                row.add(line.charAt(i) == '#');
            }
            this.field.add(row);
        }
    }

    private int get(int row, int col) {
        assert row >= 0 && col >= 0;

        if (row >= this.field.size()) {
            return -1;
        }
        if (this.field.get(row).get(col % this.field.get(row).size())) {
            return 1;
        }
        else {
            return 0;
        }
    }

    public long countTrees(int row_offset, int col_offset) {
        int col = 0, row = 0;
        long q_trees = 0;

        while (true) {
            int has_tree = this.get(row, col);
            if (has_tree == 1) {
                q_trees++;
            }
            else if (has_tree == -1) {
                break;
            }

            row += row_offset;
            col += col_offset;
        }

        return q_trees;
    }
}
