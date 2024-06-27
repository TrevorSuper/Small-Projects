package mvctextview;

import java.util.Observable;

public class RightTriangle extends Observable { //run the program from FXapp.java
    private double base;
    private double height;
    private double hypotenuse;

    public RightTriangle(double base, double height) {
        this.base = base;
        this.height = height;
        setHypotenuse();
        // System.out.println("RightTriangle() base and height " + base + " " + height + "\n");
    }

    public void setBase(double newBase){
        this.base = newBase;
        setHypotenuse();
        // System.out.println("SetBase() " + base + "\n");
    }

    public double getBase (){
        System.out.println("getBase() " + this.base + "\n");
        return this.base;
    }

    public double getHeight() {
        System.out.println("getHeight() " + height + "\n");
        return height;
    }

    public void setHeight(double newHeight) {
        this.height = newHeight;
        // System.out.println("setHeight() " + height + "\n");
        setHypotenuse();
    }

    public double getHypotenuse() {
        System.out.println("getHypotenuse() " + hypotenuse + "\n");
        return hypotenuse;
    }

    public void setHypotenuse() {
        this.hypotenuse = Math.sqrt(
                (base*base) + (height*height));
        // System.out.println("setHypotenuse() " + this.hypotenuse + "\n");
        setChanged();
        notifyObservers();
    }
} // end RightTriangle
