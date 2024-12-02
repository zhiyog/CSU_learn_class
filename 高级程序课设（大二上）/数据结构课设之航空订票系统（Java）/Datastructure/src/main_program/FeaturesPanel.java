package main_program;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

//import com.sun.org.apache.xerces.internal.impl.xs.SchemaGrammar.BuiltinSchemaGrammar;

public class FeaturesPanel extends JPanel implements MouseListener{
	static Font welcome_text_font=new Font("Î¢ÈíÑÅºÚ", Font.PLAIN, 25);
	static JLabel welcome_text=new JLabel("»¶Ó­Ê¹ÓÃ º½¿Õ¶©Æ±ÏµÍ³");
	static JLabel icon_search=new JLabel(new ImageIcon("src/data/icon/icon_search.png"));
	static JLabel icon_add=new JLabel(new ImageIcon("src/data/icon/icon_add.png"));
	static JLabel icon_delete=new JLabel(new ImageIcon("src/data/icon/icon_delete.png"));
	//static JLabel icon_exit=new JLabel(new ImageIcon("src/data/icon/icon_exit.png"));
	static JLabel icon_search_text=new JLabel("º½°à¼ìË÷");
	static JLabel icon_add_text=new JLabel("»úÆ±Ô¤¶¨");
	static JLabel icon_delete_text=new JLabel("¶©µ¥¹ÜÀí");
	
	boolean searchPanel_on=true;
	boolean addPanel_on=true;
	boolean refundPanel_on=true;
	public FeaturesPanel() {
		this.setLayout(null);
		welcome_text.setBounds(30,30,400,30);
		welcome_text.setFont(welcome_text_font);
		this.add(welcome_text);
		
		icon_search.setBounds(220, 120, 128, 128);
		icon_search.addMouseListener(this);
		this.add(icon_search);
		icon_search_text.setBounds(240, 250, 128, 30);
		icon_search_text.setFont(welcome_text_font);
		icon_search_text.addMouseListener(this);
		this.add(icon_search_text);
		
		
		icon_add.setBounds(390,120,128,128);
		icon_add.addMouseListener(this);
		this.add(icon_add);
		icon_add_text.setBounds(400, 250, 128, 30);
		icon_add_text.setFont(welcome_text_font);
		icon_add_text.addMouseListener(this);
		this.add(icon_add_text);
		
		icon_delete.setBounds(560,120,128,128);
		icon_delete.addMouseListener(this);
		this.add(icon_delete);
		icon_delete_text.setBounds(570, 250, 128, 30);
		icon_delete_text.setFont(welcome_text_font);
		icon_delete_text.addMouseListener(this);
		this.add(icon_delete_text);
		
		this.setBackground(Color.white);
		this.setVisible(true);
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource().equals(icon_search)||e.getSource().equals(icon_search_text)) {
			if(searchPanel_on)
			{
				SearchPanel searchPanel=new SearchPanel();
				MainPanel.jPanel.add(searchPanel,"searchPanel");
				searchPanel_on=false;
			}
			MainPanel.cardLayout.show(MainPanel.jPanel,"searchPanel");
		}else if(e.getSource().equals(icon_add)||e.getSource().equals(icon_add_text)) {
			if(addPanel_on)
			{
				AddPanel addPanel=new AddPanel();
				MainPanel.jPanel.add(addPanel,"addPanel");
				addPanel_on=false;
			}
			MainPanel.cardLayout.show(MainPanel.jPanel,"addPanel");
		}else if(e.getSource().equals(icon_delete)||e.getSource().equals(icon_delete_text)) {
			if(refundPanel_on)
			{
				RefundPanel refundPanel=new RefundPanel();
				MainPanel.jPanel.add(refundPanel,"refundPanel");
				refundPanel_on=false;
			}
			MainPanel.cardLayout.show(MainPanel.jPanel,"refundPanel");
		}
	}
	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}
