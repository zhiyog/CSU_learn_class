//============================================================================
// eclipse IDE 2021-09
// Name        : MyProject0501.java
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Java Project
//============================================================================
package main_program;
import java.awt.Color;
import java.awt.Font;
import java.util.Enumeration;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.UIManager;
import javax.swing.plaf.FontUIResource;

import program_util.MyScreen;

public class MainFrame extends JFrame{
	static MainFrame mainFrame;
	MainPanel mainPanel=new MainPanel();
	static String main_name="航空订票系统";//窗口名称
	static ImageIcon main_icon=new ImageIcon("src/data/icon/main_icon.png");//窗口图标
	static boolean main_resizable_window=false;//默认不允许修改窗口大小
	static int widthframe=960;//窗口宽度
	static int heightframe=460;//窗口高度
	public static int location_x=MyScreen.getMyScreenWidth()/2-widthframe/2;//设置窗口出现位置
	public static int location_y=MyScreen.getMyScreenHeight()/2-heightframe/2;
	public MainFrame()
	{
		try{														//使用Windows原生主题
			String lookAndFeel="com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
			UIManager.setLookAndFeel(lookAndFeel);
		}
		catch(Exception e){
			e.printStackTrace();
		}
		InitGlobalFont(new Font("微软雅黑", Font.PLAIN, 12));
		this.setIconImage(main_icon.getImage());
		this.setTitle(main_name);
		this.setResizable(main_resizable_window);
		this.setBounds(location_x,location_y,widthframe,heightframe);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.add(mainPanel);
		mainPanel.setBackground(Color.white);
		this.setVisible(true);
	}
	public static void main(String args[]) {
		mainFrame=new MainFrame();
	}

	private static void InitGlobalFont(Font font) {
		FontUIResource fontRes = new FontUIResource(font);
		for (Enumeration<Object> keys = UIManager.getDefaults().keys(); keys.hasMoreElements();) {
			Object key = keys.nextElement();
			Object value = UIManager.get(key);
			if (value instanceof FontUIResource) {
				UIManager.put(key, fontRes);
			}
		}
	}
}
