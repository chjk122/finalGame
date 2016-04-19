import java.awt.Graphics; 
import javax.swing.JFrame;
import java.io.*;

public class Main extends JFrame
{
	private static final int WIDTH = 1210;
	private static final int HIGHT = 900;
	
	public Main() throws IOException
	{
		setSize(WIDTH,HIGHT);
		getContentPane().add(new Board());
      	setVisible(true);
      	setResizable(false);
	}
    public static void main(String[] args) throws IOException
    {
        Main game = new Main();
        
    }
}