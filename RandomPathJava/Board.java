import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.awt.Color;
import java.awt.Font;
import javax.swing.JFrame;
import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.*;
import java.util.Scanner;
import java.awt.Point;


/* Bug is when pulling it can pull from two spaces next to each other resulting in a broken path */
public class Board extends Canvas implements MouseListener
{
    private BufferedImage back;
    private Square[][] board;
    private boolean[] pressBoolean = {false,false, false, false};
    private Square startSquare = new Square();
    private Square finishSquare = new Square();
    private static final int MAX_PATH_LENGTH = 150;
    private static final int MAX_PATH_LENGTH_VARIANCE = 10;
    private static final double PULL_PROBABILITY_BASE = 1; // .8 is good
    private static final double PULL_PROBABILITY_MULT = .06; //.33 is good
    
    public Board() throws IOException
    {
        board = new Square[20][20];
        for(int x = 0; x < board.length; x++)
        {
            for(int y = 0; y<board[x].length; y++)
            {
                board[x][y] = new Square();
                int s = board[x][y].getSideLength();
                board[x][y].setCenterX((int)Math.round(10+y*s+s*.5));
                board[x][y].setCenterY((int)Math.round(10+x*s+s*.5));
                board[x][y].construct();
            }
        }
        addMouseListener(this);
    }
    
    public Square[][] getBoard()           {return board;}
    
    
    public Square[] getAdjacentSquares(Square sq) //returns as North, East, South, West
    {
        for(int x = 0; x < board.length; x++)
        {
            for(int y = 0; y<board[x].length; y++)
            {
                if(board[x][y].equals(sq))
                {
                    if(x == 0 && y == 0)                                                                    //top left corner
                        return new Square[] {null,board[x][y+1], board[x+1][y], null};                          //returns East and South 
                    else if(x == 0 && y == board[x].length - 1)                                             //top right corner
                        return new Square[] {null,null, board[x+1][y], board[x][y-1]};                          //returns South and West
                    else if(x == board.length - 1 && y == 0)                                                //bottom left corner
                        return new Square[] {board[x-1][y],board[x][y+1], null, null};                          //returns North and East
                    else if(x == board.length-1 && y == board[x].length - 1)                                //bottom right corner
                        return new Square[] {board[x-1][y],null, null, board[x][y-1]};                          //returns North and West
                    else if(x == 0)                                                                         //North edge
                        return new Square[] {null,board[x][y+1], board[x+1][y], board[x][y-1]};                 //returns no North
                    else if(y == board[x].length - 1)                                                       //East edge
                        return new Square[] {board[x-1][y], null, board[x+1][y], board[x][y-1]};                //returns no East
                    else if(x == board.length - 1)                                                          //South edge
                        return new Square[] {board[x-1][y],board[x][y+1], null, board[x][y-1]};                 //returns no South
                    else if(y == 0)                                                                         //West edge
                        return new Square[] {board[x-1][y],board[x][y+1], board[x+1][y], null};                 //returns no West
                    else                                                                                    //center
                        return new Square[] {board[x-1][y],board[x][y+1], board[x+1][y], board[x][y-1]};        //return all
                }
                
            }
        }
        return new Square[] {null,null,null,null};
    }
    public Square getNorthSquare(Square sq)
    {
        return getAdjacentSquares(sq)[0];
    }
    public Square getEastSquare(Square sq)
    {
        return getAdjacentSquares(sq)[1];
    }
    public Square getSouthSquare(Square sq)
    {
        return getAdjacentSquares(sq)[2];
    }
    public Square getWestSquare(Square sq)
    {
        return getAdjacentSquares(sq)[3];
    }
    public Square getAdjacentSquareWithShortestDistace(Square start, Square finish)
    {
        Square[] sqs = getAdjacentSquares(start);
        double c = getDistance(start, finish);
        
        ArrayList<Square> possibilities = new ArrayList<Square>();
        if(getDistance(sqs[0], finish) < c) possibilities.add(sqs[0]); //north closer than base
        if(getDistance(sqs[1], finish) < c) possibilities.add(sqs[1]); //east closer than base
        if(getDistance(sqs[2], finish) < c) possibilities.add(sqs[2]); //south closer than base
        if(getDistance(sqs[3], finish) < c) possibilities.add(sqs[3]); //west closer than base
        
        return possibilities.get((int) (Math.random() * possibilities.size() )); //random direction thats closer
    }
    public double getDistance(Square start, Square finish)
    {
        if(finish == null)
        {
            System.out.println("ERROR Board.getDistance : finish is null");
            return -1;
        }
        return (start == null ? Double.MAX_VALUE : start.getDistance(finish));
    }
    
    public void findLongerPath(int maxGreenToUse)
    {
        for(int x = 0; x < board.length; x++)
        {
            for(int y = 0; y<board[x].length; y++)
            {
                if(MAX_PATH_LENGTH-totalGreen() <= 2)
                    return;
                if(board[x][y].getColor().equals(Color.BLUE))
                {
                    Square sq = board[x][y];
                    String ans = acceptableToPull(sq);
                    boolean failed;
                    if(!ans.equals("false")){
                        failed = pull(sq, ans, maxGreenToUse) == -1;
                        System.out.println("After pull Green Count is : " + failed);
                        System.out.println("After pull real Green Count is : " + totalGreen());}
                }
            }
        }
    }
    
    public String acceptableToPull(Square sq)
    {
        if(sq ==null)
        {
            System.out.println("ACCEPTABLE TO PULL SQ WAS NULL");
            return "false";
        }
        Square east = getEastSquare(sq);
        Square west = getWestSquare(sq);
        Square north = getNorthSquare(sq);
        Square south = getSouthSquare(sq);
        boolean[] direction = {false,false,false,false};
        if(east!=null && west!=null && east.getColor().equals(Color.BLUE) && west.getColor().equals(Color.BLUE))
        {
            Square east2 = getEastSquare(east);
            Square west2 = getWestSquare(west);
            if((east2 == null || east2.getColor().equals(Color.BLUE) || east2.getColor().equals(Color.RED)) && (west2 == null || west2.getColor().equals(Color.BLUE) || west2.getColor().equals(Color.RED)))
            {
                if(north == null || north.getColor().equals(Color.RED) || north.getColor().equals(Color.BLUE))
                    direction[0] = true;
                if(south == null || south.getColor().equals(Color.RED) || south.getColor().equals(Color.BLUE))
                    direction[2] = true;
                if(!direction[0] && !direction[2])
                    return "false";
                if(direction[0]) //more testing on north
                {
                    if(north == null)
                        return "north";
                    Square northWest = getWestSquare(north);
                    Square northEast = getEastSquare(north);
                    if((northWest.getColor().equals(Color.BLUE) || northWest.getColor().equals(Color.RED)) && (northEast.getColor().equals(Color.BLUE) || northEast.getColor().equals(Color.RED)))
                    {
                        return "north";
                    }
                }
                else if(direction[2])
                {
                    if(south == null)
                        return "south";
                    Square southWest = getWestSquare(south);
                    Square southEast = getEastSquare(south);
                    if((southWest.getColor().equals(Color.BLUE) || southWest.getColor().equals(Color.RED)) && (southEast.getColor().equals(Color.BLUE) || southEast.getColor().equals(Color.RED)))
                    {
                        return "south";
                    }
                }
            }
        }
        else if(north!=null && south!=null && north.getColor().equals(Color.BLUE) && south.getColor().equals(Color.BLUE))
        {
            Square north2 = getNorthSquare(north);
            Square south2 = getSouthSquare(south);
            if((north2 == null || north2.getColor().equals(Color.BLUE) || north2.getColor().equals(Color.RED)) && (south2 == null || south2.getColor().equals(Color.BLUE) || south2.getColor().equals(Color.RED)))
            {
                if(east == null || east.getColor().equals(Color.RED) || east.getColor().equals(Color.BLUE))
                    direction[1] = true;
                if(west == null || west.getColor().equals(Color.RED) || west.getColor().equals(Color.BLUE))
                    direction[3] = true;
                if(!direction[1] && !direction[3])
                    return "false";
                if(direction[1]) //more testing on east
                {
                    if(east == null)
                        return "east";
                    Square northEast = getEastSquare(north);
                    Square southEast = getEastSquare(south);
                    if((northEast.getColor().equals(Color.BLUE) || northEast.getColor().equals(Color.RED)) && (southEast.getColor().equals(Color.BLUE) || southEast.getColor().equals(Color.RED)))
                    {
                        return "east";
                    }
                }
                else if(direction[3])
                {
                    if(west == null)
                        return "west";
                    Square northWest = getWestSquare(north);
                    Square southWest = getWestSquare(south);
                    if((northWest.getColor().equals(Color.BLUE) || northWest.getColor().equals(Color.RED)) && (southWest.getColor().equals(Color.BLUE) || southWest.getColor().equals(Color.RED)))
                    {
                        return "west";
                    }
                }
            }
        }
        else
            return "false";
        return "false";
    }
    
    public int pull(Square sq, String direction, int maxGreenToUse)
    {
        Square[] sqs = getAdjacentSquares(sq);
        boolean willPull = Math.random() <= PULL_PROBABILITY_BASE;
        System.out.println("base pull result : " + willPull);
        if(MAX_PATH_LENGTH-totalGreen() >= 2 && willPull)
        {
            if(direction.equals("north"))
            {
                sqs[2].setColor(Color.RED);
                sqs[1].setColor(Color.GREEN);
                sq.setColor(Color.GREEN);
                sqs[3].setColor(Color.GREEN);
                maxGreenToUse-=2;
                colorBlue();
                if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
                {
                    String res = acceptableToPull(sqs[0]);
                    if(!res.equals("false"))
                        maxGreenToUse = pull(sqs[0],res,maxGreenToUse,0);
                }
            }
            else if(direction.equals("east"))
            {
                sqs[3].setColor(Color.RED);
                sqs[0].setColor(Color.GREEN);
                sq.setColor(Color.GREEN);
                sqs[2].setColor(Color.GREEN);
                maxGreenToUse-=2;
                colorBlue();
                if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
                {
                    String res = acceptableToPull(sqs[1]);
                    if(!res.equals("false"))
                        maxGreenToUse = pull(sqs[1],res,maxGreenToUse,0);
                }
            }
            else if(direction.equals("south"))
            {
                sqs[0].setColor(Color.RED);
                sqs[1].setColor(Color.GREEN);
                sq.setColor(Color.GREEN);
                sqs[3].setColor(Color.GREEN);
                maxGreenToUse-=2;
                colorBlue();
                if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
                {
                    String res = acceptableToPull(sqs[2]);
                    if(!res.equals("false"))
                        maxGreenToUse = pull(sqs[2],res,maxGreenToUse,0);
                }
            }
            else if(direction.equals("west"))
            {
                sqs[1].setColor(Color.RED);
                sqs[0].setColor(Color.GREEN);
                sq.setColor(Color.GREEN);
                sqs[2].setColor(Color.GREEN);
                maxGreenToUse-=2;
                colorBlue();
                if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
                {
                    String res = acceptableToPull(sqs[3]);
                    if(!res.equals("false"))
                        maxGreenToUse = pull(sqs[3],res,maxGreenToUse,0);
                }
            }
        }
        else
            return -1;
        return maxGreenToUse;
    }
    
    public int pull(Square sq, String direction, int maxGreenToUse, int recursionForm)
    {
        Square[] sqs = getAdjacentSquares(sq);
        if(direction.equals("north"))
        {
            sqs[2].setColor(Color.RED);
            sqs[1].setColor(Color.GREEN);
            sq.setColor(Color.GREEN);
            sqs[3].setColor(Color.GREEN);
            maxGreenToUse-=2;
            colorBlue();
            if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
            {
                String res = acceptableToPull(sqs[0]);
                if(!res.equals("false"))
                    maxGreenToUse = pull(sqs[0],res,maxGreenToUse,0);
            }
        }
        else if(direction.equals("east"))
        {
            sqs[3].setColor(Color.RED);
            sqs[0].setColor(Color.GREEN);
            sq.setColor(Color.GREEN);
            sqs[2].setColor(Color.GREEN);
            maxGreenToUse-=2;
            colorBlue();
            if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
            {
                String res = acceptableToPull(sqs[1]);
                if(!res.equals("false"))
                    maxGreenToUse = pull(sqs[1],res,maxGreenToUse,0);
            }
        }
        else if(direction.equals("south"))
        {
            sqs[0].setColor(Color.RED);
            sqs[1].setColor(Color.GREEN);
            sq.setColor(Color.GREEN);
            sqs[3].setColor(Color.GREEN);
            maxGreenToUse-=2;
            colorBlue();
            if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
            {
                String res = acceptableToPull(sqs[2]);
                if(!res.equals("false"))
                    maxGreenToUse = pull(sqs[2],res,maxGreenToUse,0);
            }
        }
        else if(direction.equals("west"))
        {
            sqs[1].setColor(Color.RED);
            sqs[0].setColor(Color.GREEN);
            sq.setColor(Color.GREEN);
            sqs[2].setColor(Color.GREEN);
            maxGreenToUse-=2;
            colorBlue();
            if(MAX_PATH_LENGTH-totalGreen() >=2 && Math.random() <= PULL_PROBABILITY_MULT)
            {
                String res = acceptableToPull(sqs[3]);
                if(!res.equals("false"))
                    maxGreenToUse = pull(sqs[3],res,maxGreenToUse,0);
            }
        }
        else
            return -1;
        return maxGreenToUse;
    }
    
    public void paintString(Graphics window, String word, int x, int y, Color color)
    {
        window.setColor(color);
        Scanner chopper = new Scanner(word);
        String output = "";
        while(chopper.hasNext())
        {
            output += chopper.next() + " ";
            if(output.length() > 30)
            {
                window.drawString(output,x,y);
                y+=12;
                output = "";
            }
        }
        window.drawString(output,x,y);
    }
    
    public void paint(Graphics window)
    {
        Graphics2D twoDGraph = (Graphics2D)window;
        
        if(back==null)
           back = (BufferedImage)(createImage(getWidth(),getHeight()));
        Graphics graphToBack = back.createGraphics();
        
        graphToBack.clearRect(0,0, getWidth(),getHeight());
       
        for(int x = 0; x < board.length; x++)
        {
            for(int y = 0; y<board[x].length; y++)
            {
                board[x][y].paint(graphToBack);
            }
        }
        
        paintString(graphToBack,"S", startSquare.getCenterX() -4, startSquare.getCenterY() + 4, Color.BLACK); //paint start
        paintString(graphToBack,"F", finishSquare.getCenterX() -4, finishSquare.getCenterY() + 4, Color.BLACK); //paint start
        twoDGraph.drawImage(back, null, 0, 0);
    }
    
    public void update(Graphics g) 
    { 
         paint(g);
    }
    
    public int totalGreen()
    {
        int green = 0;
        for(int x = 0; x < board.length; x++)
        {
            for(int y = 0; y<board[x].length; y++)
            {
                if(board[x][y].getColor().equals(Color.GREEN))
                    green++;       
            }
        }
        return green;
    }
    public void colorBlue()
    {
        Square[] sqs = {};
        for(int x = 0; x < board.length; x++)
        {
            for(int y = 0; y<board[x].length; y++)
            {
                sqs = getAdjacentSquares(board[x][y]);
                for(Square s : sqs)
                {
                    if(s == null)
                        continue;
                    if(s.getColor().equals(Color.GREEN) && board[x][y].getColor().equals(Color.RED) )
                        board[x][y].setColor(Color.BLUE);
                }
            }
        }
    }
    
    public void mousePressed(MouseEvent e)
    {
        if(!pressBoolean[0])
        {
            for(int x = 0; x < board.length; x++)
            {
                for(int y = 0; y<board[x].length; y++)
                {
                    if(board[x][y].getSquare().contains(e.getX(),e.getY()))
                    {
                        startSquare = board[x][y];
                        pressBoolean[0] = true;
                    }
                }
            }
        }
        else if(!pressBoolean[1])
        {
            for(int x = 0; x < board.length; x++)
            {
                for(int y = 0; y<board[x].length; y++)
                {
                    if(board[x][y].getSquare().contains(e.getX(),e.getY()) && !board[x][y].equals(startSquare))
                    {   
                        finishSquare = board[x][y];
                        pressBoolean[1] = true;
                    }
                }
            }
        }
        else if(!pressBoolean[2])
        {
            Square currentSquare = startSquare;
            currentSquare.setColor(Color.GREEN);
            double northDist = 0, eastDist = 0, southDist = 0, westDist = 0;
            while(!currentSquare.equals(finishSquare))
            {
                currentSquare = getAdjacentSquareWithShortestDistace(currentSquare, finishSquare);
                currentSquare.setColor(Color.GREEN);
            }
            pressBoolean[2] = true;
            colorBlue();
        }
        else if (!pressBoolean[3])
        {
            int numGreen = totalGreen();
            int greenLeft = 0;
            //while(numGreen < MAX_PATH_LENGTH -  MAX_PATH_LENGTH_VARIANCE && (numGreen < MAX_PATH_LENGTH - 2))
            //{
                greenLeft = MAX_PATH_LENGTH-numGreen;
                findLongerPath(greenLeft);
            //}
            //pressBoolean[3] = true;
        }
        /*else
        {
            pressBoolean = new boolean[] {false,false, false, false};
            for(int x = 0; x < board.length; x++)
            {
                for(int y = 0; y<board[x].length; y++)
                {  
                    board[x][y].setColor(Color.RED);
                }
            }
        }*/
        repaint();
    }
    
    public void mouseReleased(MouseEvent e) {
        
    }
    
    public void mouseEntered(MouseEvent e) {
      
    }
    
    public void mouseExited(MouseEvent e) {
        
    }
    
    public void mouseClicked(MouseEvent e) 
    {
        
    }
}