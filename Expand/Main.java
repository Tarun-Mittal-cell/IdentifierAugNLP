import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    private static final List<String> GRAMMAR_PATTERNS = new ArrayList<>(Arrays.asList(
            "NM* N",
            "V NM NM NM N",
            "NM* NPL",
            "V NM* (N|NPL)",
            "P NM* (N|NPL)",
            "NM* N P NM* (N|NPL)",
            "V P NM* (N|NPL)",
            "V* DT NM* (N|NPL)",
            "V+"
    ));


    public static String getBestMatch(String input) {
        int minDistance = Integer.MAX_VALUE;
        String bestMatch = null;

        for (String pattern : GRAMMAR_PATTERNS) {
            int distance = getLevenshteinDistance(input, pattern);
            if (distance < minDistance) {
                minDistance = distance;
                bestMatch = pattern;
            }
        }

        return bestMatch;
    }



    public static int getLevenshteinDistance(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(dp[i - 1][j], Math.min(dp[i][j - 1], dp[i - 1][j - 1]));
                }
            }
        }

        return dp[m][n];
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an input string");
            return;
        }

        String input = args[0];

        String bestMatch = getBestMatch(input);
        int distance = getLevenshteinDistance(input, bestMatch);
        System.out.println("Best match for input string '" + input + "' is: " + bestMatch + ", Levenshtein distance: " + distance);
    }
}


