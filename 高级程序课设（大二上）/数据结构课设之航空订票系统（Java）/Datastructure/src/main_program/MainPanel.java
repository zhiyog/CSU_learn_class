package main_program;

import java.awt.CardLayout;

import javax.swing.JPanel;

public class MainPanel extends JPanel{
	MainFrame mainFrame;
	public static JPanel jPanel=new JPanel();
	public static CardLayout cardLayout=new CardLayout();
	FeaturesPanel featuresPanel=new FeaturesPanel();
	public MainPanel() {
		this.setLayout(null);
		jPanel.setLayout(cardLayout);
		jPanel.removeAll();
		jPanel.add(featuresPanel,"featuresPanel");
		cardLayout.show(jPanel, "featuresPanel");
		jPanel.setBounds(0,0,mainFrame.widthframe,mainFrame.heightframe);
		this.add(jPanel);
		this.setVisible(true);
	}
}
