package program_util;

import java.awt.Dimension;
import java.awt.Toolkit;

public class MyScreen {
	public static int getMyScreenWidth()
	{
		int width;
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize(); //�õ���Ļ�ĳߴ�
		width=screenSize.width;
		return width;
	}
	public static int getMyScreenHeight()
	{
		int height;
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize(); //�õ���Ļ�ĳߴ�
		height=screenSize.height;
		return height;
	}
}
