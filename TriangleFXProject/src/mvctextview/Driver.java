package mvctextview;

import javafx.application.Application; //run the program from FXapp.java
import javafx.stage.Stage;

import static javafx.application.Application.launch;
import javafx.scene.Scene;

public class Driver extends Application{
    //Create an observer of RightTriangle rt.

    @Override
    public void start(Stage primaryStage) {
        RightTriangle tri = new RightTriangle(0.0,0.0);
        TextView pane = new TextView(tri);
        Scene scene = new Scene(pane);
        primaryStage.setTitle("Triangle View1");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
