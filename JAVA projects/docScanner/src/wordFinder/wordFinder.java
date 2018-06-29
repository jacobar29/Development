/*
Javafx app to search a given block of text and return the frequency of each of a given list of keywords

*/

package wordFinder;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class wordFinder extends Application {
    //Setup view
    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("wordFinder.fxml"));
        primaryStage.setTitle("Word Frequency Finder");
        primaryStage.setScene(new Scene(root, 500, 600));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
