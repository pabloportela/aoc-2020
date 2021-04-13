import java.io.IOException;


public class day3 {

    public static void main(String[] args) throws IOException {
        assert args.length == 1;
        Field field = new Field(args[0]);

        // part 1
        System.out.println("There are " + field.countTrees(1, 3) + " trees on the way one down, three right.");

        // part 2
        long solution = 1;
        System.out.println(solution);
        solution *= field.countTrees(1, 1);
        System.out.println(solution);
        solution *= field.countTrees(1, 3);
        System.out.println(solution);
        solution *= field.countTrees(1, 5);
        System.out.println(solution);
        solution *= field.countTrees(1, 7);
        System.out.println(solution);
        solution *= field.countTrees(2, 1);
        System.out.println("For part two, the solution is " + solution);
    }
}
