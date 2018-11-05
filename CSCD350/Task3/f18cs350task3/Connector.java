//Conrad Provan
package f18cs350task3;

import javafx.geometry.Point2D;

public class Connector implements Cloneable {
    private Box childBox;
    private Box parentBox;
    private Point2D offsetFromParentBox;

    public Connector(Box childBox, Point2D offsetFromParentBox){
        if(offsetFromParentBox == null){
            throw new NullPointerException();
        }
        if(childBox == null){
            throw new IllegalArgumentException();
        }
        this.childBox = childBox;
        this.offsetFromParentBox = offsetFromParentBox;
        this.childBox.setConnectorToParent​(this);
    }

    public Connector clone()throws java.lang.CloneNotSupportedException{
        Connector connectorClone = (Connector)super.clone();
        connectorClone.parentBox = null;
        connectorClone.offsetFromParentBox = new Point2D(this.getOffsetFromParentBox().getX(),this.getOffsetFromParentBox().getY());
        connectorClone.childBox = this.getChildBox().clone();
        connectorClone.getChildBox().setConnectorToParent​(connectorClone);
        return connectorClone;
    }

    public Box getChildBox() {
        return childBox;
    }

    public Point2D getOffsetFromParentBox() {
        if(offsetFromParentBox == null) {
            throw new NullPointerException();
        }else{
            return offsetFromParentBox;
        }
    }

    public Box getParentBox() {
        if(hasParentBox()) {
            return parentBox;
        }
        throw new NullPointerException();
    }

    public boolean hasParentBox(){
        return (parentBox != null);
    }

    void setParentBox(Box parentBox) {
        if(parentBox == null){
            throw new NullPointerException();
        }
        if(this.parentBox != null){
            throw new IllegalArgumentException("Already connected to parent box'" + this.parentBox.getID() + "'");
        }
        this.parentBox = parentBox;
    }

    public String toString() {
        return "(Parent: " + getParentBox().getID() + ", Child: " + getChildBox().getID() + ")";
    }
}
