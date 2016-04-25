import java.util.*;
import java.io.*;

public class parser
{
	public static void main(String[] args) throws FileNotFoundException
	{
		Scanner write = new Scanner(new File("map.txt"));
		PrintWriter write2 = new PrintWriter(new File("mapCode.txt"));
		String vectorName = "tile";

		while(write.hasNextLine())
		{
			String line = write.nextLine();
			line = removeTab(line);
			if(line.equals(""))
			{
				vectorName = "cubesters";
				continue;
			}
				write2.println(vectorName + "->push_back(" + "\"" + line + "\"" + ");");
		}
		write.close();
		write2.close();
	}

	public static String removeTab(String line)
	{	
		String newString = "";
		for(int x = 0; x < line.length(); x++)
		{
			//not a space or a tab
			if(line.charAt(x) != ' ' && line.charAt(x) != 9)
				newString += Character.toString(line.charAt(x));
		}
		return newString;
	}

	public static String removeTrailingSpace(String line)
	{	
		return line.trim();
	}		
}