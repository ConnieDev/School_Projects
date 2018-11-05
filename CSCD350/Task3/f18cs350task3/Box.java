//Conrad Provan
package f18cs350task3;

import javafx.geometry.Dimension2D;
import javafx.geometry.Point2D;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Box implements Cloneable{
    private String id;
    private Dimension2D size;
    private boolean isRoot;
    private Connector connectorToParent;
    private List<Connector> connectorList = new ArrayList<>();

    public class Corners{
        private final Point2D topLeft;
        private final Point2D topRight;
        private final Point2D bottomRight;
        private final Point2D bottomLeft;

        public Corners(Point2D topLeft, Point2D topRight, Point2D bottomRight, Point2D bottomLeft){
            if((topLeft == null) || (topRight == null) || (bottomRight == null) || (bottomLeft == null)) {

            }
            this.topLeft = topLeft;
            this.topRight = topRight;
            this.bottomRight = bottomRight;
            this.bottomLeft = bottomLeft;
        }

        public Point2D getTopLeft() {
            return topLeft;
        }

        public Point2D getTopRight() {
            return topRight;
        }

        public Point2D getBottomLeft() {
            return bottomLeft;
        }

        public Point2D getBottomRight() {
            return bottomRight;
        }

        public String toString() {
            return ("{["+ this.topLeft.getX() + ", " + this.topLeft.getY() + "], [" + this.topRight.getX() + ", " + this.topRight.getY() + "], [" + this.bottomRight.getX() + ", " + this.bottomRight.getY() + "], [" + this.bottomLeft.getX() + ", " + this.bottomLeft.getY() + "]}");
        }
    }

    private class ComparebyID implements Comparator<Box> {
        public int compare(Box b1, Box b2) {
            if(b1 == null || b2 == null){
                throw new NullPointerException();
            }
            return b1.getID().compareTo(b2.getID());
        }
    }

    public Box(final String id, final Dimension2D size){
        this(id,size,false);
    }

    public Box(final String id, final Dimension2D size, final boolean isRoot) {
        if(id == null){
            throw new NullPointerException();
        }
        if(id.isEmpty()){
            throw new IllegalArgumentException();
        }
        if(size == null){
            throw new NullPointerException();
        }
        if(size.getWidth() <= 0){
            throw new IllegalArgumentException();
        }
        if(size.getHeight() <= 0){
            throw new IllegalArgumentException();
        }
        this.id = id;
        this.size = size;
        this.isRoot = isRoot;
    }

    public double calculateAreaAll(){
        double areaAll = this.calculateAreaSelf();
        for (Box b: getDescendantBoxes())
            areaAll += b.calculateAreaSelf();
        return areaAll;
    }

    public double calculateAreaSelf(){
        return this.size.getHeight() * this.size.getWidth();
    }

    public Corners calculateBoundingBoxAll(){
        Corners c = this.calculateBoundingBoxSelf();
        double minX = c.getBottomLeft().getX();
        double minY = c.getBottomLeft().getY();
        double maxX = c.getTopRight().getX();
        double maxY = c.getTopRight().getY();

        for(Box b : getDescendantBoxes()){
            c = b.calculateBoundingBoxSelf();
            if(minX > c.getBottomLeft().getX())
                minX = c.getBottomLeft().getX();
            if(minY > c.getBottomLeft().getY())
                minY = c.getBottomLeft().getY();
            if(maxX < c.getTopRight().getX())
                maxX = c.getTopRight().getX();
            if(maxY < c.getTopRight().getY())
                maxY = c.getTopRight().getY();
        }
        return new Corners(new Point2D(minX,maxY), new Point2D(maxX,maxY), new Point2D(maxX,minY), new Point2D(minX,minY));
    }

    public Corners calculateBoundingBoxSelf(){
        Point2D o = getAbsoluteCenterPosition();
        Point2D tl = new Point2D(o.getX() - (this.size.getWidth()/2), o.getY() + (this.size.getHeight()/2));
        Point2D tr = new Point2D(o.getX() + (this.size.getWidth()/2), o.getY() + (this.size.getHeight()/2));
        Point2D bl = new Point2D(o.getX() - (this.size.getWidth()/2), o.getY() - (this.size.getHeight()/2));
        Point2D br = new Point2D(o.getX() + (this.size.getWidth()/2), o.getY() - (this.size.getHeight()/2));
        return  new Corners(tl, tr, br, bl);
    }

    public Box clone() throws java.lang.CloneNotSupportedException{
        Box boxClone = (Box)super.clone();
        boxClone.connectorList = new ArrayList<>();
        boxClone.connectorToParent = null;
        boxClone.isRoot = true;
        boxClone.id = new String("" + this.id);
        boxClone.size = new Dimension2D(this.getSize().getWidth(), this.getSize().getHeight());
        if(this.getChildBoxCount() > 0)
            for(Connector c : getConnectorsToChildren())
                boxClone.connectChild​(c.clone());
        return boxClone;
    }

    public void connectChild​(Connector connector) {
        if(connector == null){
            throw new NullPointerException();
        }
        connector.getChildBox().isRoot = false;
        connector.setParentBox(this);
        this.connectorList.add(connector);
    }

    public javafx.geometry.Point2D getAbsoluteCenterPosition(){
        Point2D p = new Point2D(0,0);
        if(!isRoot()){
            return this.connectorToParent.getOffsetFromParentBox().add(this.connectorToParent.getParentBox().getAbsoluteCenterPosition());
        }
        return  p;
    }

    public int getChildBoxCount(){
        return connectorList.size();
    }

    public java.util.List<Box> getChildBoxes(){
        List<Box> childBoxes = new ArrayList<>();
        for (Connector connector: connectorList) {
            childBoxes.add(connector.getChildBox());
        }
        childBoxes.sort(new ComparebyID());
        return childBoxes;
    }

    public java.util.List<Connector> getConnectorsToChildren(){
        return connectorList;
    }

    public Connector getConnectorToParent(){
        if(!this.hasConnectorToParent()){
            throw new NullPointerException();
        }else {
            return this.connectorToParent;
        }
    }

    public int getDescendantBoxCount(){
        return getDescendantBoxes().size();
    }

    public java.util.List<Box> getDescendantBoxes(){
        List<Box> descendantBoxes = new ArrayList<>();
        if(getChildBoxCount() == 0){
            descendantBoxes.sort(new ComparebyID());
            return descendantBoxes;
        }else {
            descendantBoxes.addAll(getChildBoxes());
            for (Box b : getChildBoxes()) {
                descendantBoxes.addAll(b.getDescendantBoxes());
            }
            descendantBoxes.sort(new ComparebyID());
            return  descendantBoxes;
        }
    }

    public java.lang.String getID(){
        if(this.id == null){
            throw new NullPointerException();
        }
        return  this.id;
    }

    public javafx.geometry.Dimension2D getSize(){
        if(this.size == null){
            throw new NullPointerException();
        }
        return size;
    }

    public boolean hasConnectorToParent(){
        return (connectorToParent != null);
    }

    public boolean isRoot(){
        return isRoot;
    }

    void setConnectorToParent​(Connector connector){
        if(connector == null){
            throw new NullPointerException();
        }
        this.connectorToParent = connector;
    }

    public java.lang.String toString(){
        String childBoxesString = "     ChildBoxes(" + getChildBoxCount() + "): ";
        String cornersSelfString = "     CornersSelf: " + calculateBoundingBoxSelf().toString() + "\n";
        String cornersAllString = "     CornersAll: " + calculateBoundingBoxAll().toString() + "\n";
        String descendantBoxesString = "     DescendantBoxes(" + getDescendantBoxCount() + "): ";
        String connectorString = "     ChildConnectors(" + getConnectorsToChildren().size() + "): ";
        String boxString = this.getID() + " {isRoot: " + isRoot() + ", Size: [" + this.getSize().getWidth() + ", " + this.getSize().getHeight() + "], AbsoluteCenter: [" + getAbsoluteCenterPosition().getX() + ", " + getAbsoluteCenterPosition().getY() + "], AreaSelf: " + calculateAreaSelf() + ", AreaAll: " + calculateAreaAll();
        if(this.hasConnectorToParent()){
            boxString += (", OffsetFromParent: [" + this.getConnectorToParent().getOffsetFromParentBox().getX() + ", " + this.getConnectorToParent().getOffsetFromParentBox().getY() + "], ConnectorToParent: " + getConnectorToParent().toString() + "}: \n");
        }else{
            boxString += (", ConnectorToParent: (NULL)}: \n");
        }
        int counter = 0;
        for(Connector c : getConnectorsToChildren()){
            counter ++;
            connectorString += (counter + ": " + c.toString());
            if(counter != getConnectorsToChildren().size()){
                connectorString += ", ";
            }
        }
        connectorString += "\n";
        counter = 0;
        for(Box b : getDescendantBoxes()){
            counter ++;
            descendantBoxesString += b.getID();
            if(counter != getDescendantBoxCount()){
                descendantBoxesString += ", ";
            }
        }
        descendantBoxesString += "\n";
        counter = 0;
        for(Box b : getChildBoxes()){
            counter ++;
            childBoxesString += b.getID();
            if(counter != getChildBoxCount()){
                childBoxesString += ", ";
            }
        }
        childBoxesString += "\n";
        return boxString + cornersSelfString + cornersAllString + connectorString + childBoxesString + descendantBoxesString;
    }
}
