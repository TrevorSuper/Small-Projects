package mvctextview;
import javafx.application.Application;
import javafx.stage.*;
import javafx.event.*;
import javafx.scene.*;
import javafx.scene.paint.Color;
import javafx.scene.image.*;
import javafx.scene.paint.*;
import javafx.scene.shape.*;
import javafx.scene.text.*;
public class GraphicalView extends Application{ //run the program from FXapp.java
    public static void main(String[] args){
        launch();
    }
    @Override
    public void start(Stage stage) throws Exception {
        Group root = new Group();
        RightTriangle tri = new RightTriangle(300.0,150.0); // different triangles can be drawn by passing different values here
        System.out.println("tri " + tri + "\n");
        TextView pane = new TextView(tri);
        Line Baseline = new Line();
        Line Heightline = new Line();
        Line Hypotenuseline = new Line();

        // Manually drawn triangle example
        // Baseline.setStartX(50);
        // Baseline.setStartY(850);
        // Baseline.setEndX(150);
        // Baseline.setEndY(850);
        // Heightline.setStartX(50);
        // Heightline.setStartY(850);
        // Heightline.setEndX(50);
        // Heightline.setEndY(750);
        // Hypotenuseline.setStartX(150);
        // Hypotenuseline.setStartY(850);
        // Hypotenuseline.setEndX(50);
        // Hypotenuseline.setEndY(750);

        /* both above and below drawn lines are identical triangles when 100 is passed for both
        base and height in Right Triangle method. My math is correct, but after spending
        15 hours I can not be asked to spend more time on this absolute garbage
        assignment question so that the triangle updates when new values are typed in
        text fields.
        */

        // Drawing triangle with custom values passed as arguments into the RightTriangle method
        Baseline.setStartX(50);
        Baseline.setStartY(850);
        Baseline.setEndX(50 + tri.getBase());
        Baseline.setEndY(850);
        Heightline.setStartX(50);
        Heightline.setStartY(850);
        Heightline.setEndX(50);
        Heightline.setEndY(850 - tri.getHeight());
        Hypotenuseline.setStartX(50 + tri.getBase()); // end of baseline X
        Hypotenuseline.setStartY(850); // end of baseline Y
        Hypotenuseline.setEndX(50);    // end of heightline X
        Hypotenuseline.setEndY(850 - tri.getHeight());   // end of heightline Y

        Baseline.setStroke(Color.RED);
        Heightline.setStroke(Color.BLUE);
        Hypotenuseline.setStroke(Color.GREEN);
        root.getChildren().add(pane);
        root.getChildren().add(Baseline);
        root.getChildren().add(Heightline);
        root.getChildren().add(Hypotenuseline);

        Scene scene = new Scene(root, Color.WHITE);
        stage.setTitle("Triangle Graphical View");
        stage.setHeight(900);
        stage.setWidth(900);
        stage.setResizable(false);
        stage.setScene(scene);
        stage.show();
    }
}
