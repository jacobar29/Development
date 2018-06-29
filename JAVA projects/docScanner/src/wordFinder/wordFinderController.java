package wordFinder;

import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class wordFinderController {

    @FXML
    private TextArea textToSearch; // Text to be searched through
    @FXML
    private TextArea keyWordArea; //  Words to be searched for
    @FXML
    private TextArea results; // Results of search


    // handler for search button
    public void handleButton() {
        results.setVisible(true);
        StringBuilder outputString = new StringBuilder("Words found: \n"); // build text string for results output
        String searchtext = (textToSearch.getText().toLowerCase() + " buffer"); // buffer ensures last word is not excluded from count
        String keyWords = ((keyWordArea.getText().toLowerCase()) + ", "); // comma added to ensure last word is not excluded from keywords array
        String[] keyWordArray = keyWords.split(", ");

        for (String KeyWord : keyWordArray) {
            int counter = 0;
            //splits text at keyword, creates temp array of portions, length of temp functions as a counter
            if (isContain(searchtext, KeyWord)) {

                // Set String pattern, ensures only entire word is matched
                String pattern = "\\b" + KeyWord + "\\b";
                Pattern p = Pattern.compile(pattern);

                String[] temp = searchtext.split(p.toString());

                // if keyword is found temp.length > 1, else temp.length = 1
                if (temp.length > 1) {
                    counter = temp.length - 1;
                    outputString.append(KeyWord);
                }
                // only appends counter if count is more than one
                if (counter > 1) outputString.append(" x ").append(counter).append('\n');
            }
        }
        results.setText(outputString.toString());

    }

    // pattern matcher, causes only whole words to match, return true if found
    private static boolean isContain(String source, String subItem) {
        String pattern = "\\b" + subItem + "\\b";
        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(source);
        return m.find();
    }

}


