import java.awt.Graphics;
import java.awt.Color;
import javax.swing.JFrame;
import java.awt.Canvas;
import java.awt.Polygon;
import java.util.Comparator;

public class Square extends Canvas implements Comparable<Square>
{
    private final static int SIDE_LENGTH = 30;
    private int centerX;
    private int centerY;
    private Color color;
    private Polygon square;
    
    
    
    public Square()
    {
        centerX = -100;
        centerY = -100;
        color = Color.RED;
    }
    
    public Square(int x,int y, Color col)
    {
        centerX = x;
        centerY = y;
        color = col;
        construct(); 
    }
    
    public void construct()
    {
        int[] x1 = {get1X(),get2X(),get3X(),get4X()};
        int[] y1 = {get1Y(),get2Y(),get3Y(),get4Y()};
        int numSides = 4;
        setSquare(new Polygon(x1,y1,numSides));
    }
    
    public int getCenterX(){return centerX;}
    public int getCenterY(){return centerY;}
    public Color getColor(){return color;}
    public int getSideLength(){return SIDE_LENGTH;}
    public Polygon getSquare(){return square;}
    
    public void setCenterX(int x) {centerX = x;}
    public void setCenterY(int y) {centerY = y;}
    public void setColor(Color x){color = x;}
    public void setSquare(Polygon x){square = x;}
    
    public int get1X(){return getCenterX() - SIDE_LENGTH/2;}
    public int get1Y(){return getCenterY() - SIDE_LENGTH/2;}
    public int get2X(){return getCenterX() + SIDE_LENGTH/2;}
    public int get2Y(){return getCenterY() - SIDE_LENGTH/2;}
    public int get3X(){return getCenterX() + SIDE_LENGTH/2;}
    public int get3Y(){return getCenterY() + SIDE_LENGTH/2;}
    public int get4X(){return getCenterX() - SIDE_LENGTH/2;}
    public int get4Y(){return getCenterY() + SIDE_LENGTH/2;}
    
    public double getDistance(Square sq){
        return (Math.sqrt(Math.pow(getCenterX() - sq.getCenterX(), 2) + Math.pow(getCenterY() - sq.getCenterY(), 2)) );   }
        
    public int compareTo(Square sq)
    {
        if(getCenterX() == sq.getCenterX())
            return getCenterY() - sq.getCenterY();
        return getCenterX() - sq.getCenterX();
    }
    public boolean equals(Square sq)
    {
        return this.compareTo(sq) == 0;
    }
    
    public void paint(Graphics window)
    {
        int[] x = {get1X(),get2X(),get3X(),get4X()};
        int[] y = {get1Y(),get2Y(),get3Y(),get4Y()};
        int numSides = 4;
        window.setColor(color);
        window.fillPolygon(x, y, numSides);
        window.setColor(new Color(0,0,0,40));
        window.drawPolygon(x, y, numSides);
    }
}