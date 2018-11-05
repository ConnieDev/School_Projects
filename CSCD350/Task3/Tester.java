import f18cs350task3.*;
import javafx.geometry.Dimension2D;
import javafx.geometry.Point2D;

public class Tester {
    public static void main(String[] args) throws java.lang.CloneNotSupportedException{
        Box box1 = new Box("box1", new Dimension2D(3,5), true);
        Box box2 = new Box("box2", new Dimension2D(4,6));
        Box box3 = new Box("box3", new Dimension2D(8,7));
        Box box4 = new Box("box4", new Dimension2D(2,5));
        box1.connectChild​(new Connector(box2, new Point2D(10,12)));
        box2.connectChild​(new Connector(box3, new Point2D(-2,-15)));
        box2.connectChild​(new Connector(box4, new Point2D(7,-8)));
        System.out.println("<------------------------------------>Original Boxes<------------------------------------>");
        System.out.print(box1.toString());
        for (Box b : box1.getDescendantBoxes()) {
            System.out.print(b.toString());
        }
        System.out.println("<------------------------------------>Clone of box 1 Structure<------------------------------------>");
        Box box5 = box1.clone();
        System.out.print(box5.toString());
        for (Box b : box5.getDescendantBoxes()) {
            System.out.print(b.toString());
        }
        System.out.println("<------------------------------------>Clone of box 2 Structure<------------------------------------>");
        Box box6 = box2.clone();
        System.out.print(box6.toString());
        for (Box b : box6.getDescendantBoxes()) {
            System.out.print(b.toString());
        }
        System.out.println("<------------------------------------>Clone of box 3 Structure<------------------------------------>");
        Box box7 = box3.clone();
        System.out.print(box7.toString());
        for (Box b : box7.getDescendantBoxes()) {
            System.out.print(b.toString());
        }
        System.out.println("<------------------------------------>Clone of box 4 Structure<------------------------------------>");
        Box box8 = box4.clone();
        System.out.print(box8.toString());
        for (Box b : box8.getDescendantBoxes()) {
            System.out.print(b.toString());
        }
    }
}