package mvctextview;

import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;

import java.util.Observable;
import java.util.Observer;

public class TextView extends GridPane implements Observer{ //run the program from FXapp.java
    private RightTriangle target;
    private TVController controller;

    //solution here
    private TextField base;
    private TextField height;
    private TextField hypotenuse;
    private Text txtBase;
    private Text txtHeight;
    private Text txtHypotenuse;
    //solution end

    //Create an observer of RightTriangle rt.
    public TextView(RightTriangle realTri){
        //solution from here
        base = new TextField("0");
        base.setId("Base");
        height = new TextField("0");
        height.setId("Height");
        hypotenuse = new TextField("0");
        hypotenuse.setEditable(false);
        txtBase = new Text("Base");
        txtHeight = new Text("Height");
        txtHypotenuse = new Text("Hypotenuse");

        this.add(txtBase,0,0);
        this.add(base,1,0);
        this.add(txtHeight,0,1);
        this.add(height,1,1);
        this.add(txtHypotenuse,0,2);
        this.add(hypotenuse,1,2);
        //solution end

        this.target = realTri;
        this.target.addObserver(this);
        controller = new TVController(this.target);


    }

    @Override
    public void update(Observable model, Object arg) {
        RightTriangle rt = (RightTriangle)model;
        base.setText(String.valueOf(rt.getBase()));
        height.setText(String.valueOf(rt.getHeight()));
        hypotenuse.setText(String.valueOf(rt.getHypotenuse()));
    }

    public class TVController implements EventHandler {
        private RightTriangle model;

        /**
         * Create a new Controller for this TextView of the
         * specified RightTriangle.
         * @param model is RightTriangle type class
         */
        public TVController (RightTriangle model) {
            this.model = model;
            TextView.this.base.setOnAction(this);
            TextView.this.height.setOnAction(this);
        }

        @Override
        public void handle(Event event) {
            TextField tf = (TextField)event.getSource();
            try {
                double number = Double.parseDouble(tf.getText());

                if (number < 0) throw new NumberFormatException();
                String which = tf.getId();
                if (which.equals("Base")){
                    model.setBase(number);
                }else {
                    model.setHeight(number);
                }
            } catch (NumberFormatException e) {
                TextView.this.update(model, null);
            }
        }
    }
}
