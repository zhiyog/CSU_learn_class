package main_program;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

//import com.sun.javafx.image.BytePixelSetter;
import com.sun.org.apache.bcel.internal.generic.IF_ACMPEQ;

import program_util.FileOperations;
import program_util.OtherUtils;

public class RefundPanel extends JPanel implements ActionListener{
	JTabbedPane tabbedPane=new JTabbedPane();
	//-----------------成功购票界面------------------------------------------------
	static JButton refund_button=new JButton("退票");
	static JButton details_button1=new JButton("详情");
	static JButton refresh_button1=new JButton("刷新");
	static JButton search_button1=new JButton("搜索");
	static JButton return_button1=new JButton("返回");
	static JTextField search_bar1=new JTextField();
	JScrollPane jScrollPane1;
	public static JTable table1;
	public JPanel tablePanel1;
	public static DefaultTableModel table_mode1;
	static String[] order_tab_title1 = { "航班号", "购票人", "手机号", "数量","座位号","购票时间"};
	//-----------------候补购票界面------------------------------------------------
	static JButton booking_button=new JButton("订票");
	static JButton delete_button=new JButton("删除");
	static JButton refresh_button2=new JButton("刷新");
	static JButton search_button2=new JButton("搜索");
	static JButton return_button2=new JButton("返回");
	static JTextField search_bar2=new JTextField();
	JScrollPane jScrollPane2;
	public static JTable table2;
	public JPanel tablePanel2;
	public static DefaultTableModel table_mode2;
	static String[] order_tab_title2 = { "航班号", "购票人", "手机号", "数量","候补时间"};
	//--------------------------------------------------------------------------
	public RefundPanel() {
		this.setLayout(new GridLayout(1,1));
		this.setBackground(Color.white);
		//---------------成功购票界面----------------------------------------------
		tablePanel1=new JPanel();
		tablePanel1.setLayout(null);
		tablePanel1.setBackground(Color.white);
		table1=new JTable();
		refresh_table("src/data/storage/booking.txt", table_mode1, table1, order_tab_title1,true);
		jScrollPane1=new JScrollPane(table1);
		jScrollPane1.setBounds(5, 40, 930, 345);
		tablePanel1.add(jScrollPane1);
		
		refund_button.setBounds(5,5,60,25);
		tablePanel1.add(refund_button);
		details_button1.setBounds(75,5,60,25);
		tablePanel1.add(details_button1);
		refresh_button1.setBounds(145,5,60,25);
		tablePanel1.add(refresh_button1);
		return_button1.setBounds(215,5,60,25);
		tablePanel1.add(return_button1);
		search_bar1.setBounds(710, 6, 150, 23);
		tablePanel1.add(search_bar1);
		search_button1.setBounds(870, 5, 60, 25);
		tablePanel1.add(search_button1);
		
		refund_button.addActionListener(this);
		details_button1.addActionListener(this);
		refresh_button1.addActionListener(this);
		return_button1.addActionListener(this);
		search_button1.addActionListener(this);
		booking_button.addActionListener(this);
		//---------------候补购票界面----------------------------------------------
		tablePanel2=new JPanel();
		tablePanel2.setLayout(null);
		tablePanel2.setBackground(Color.white);
		table2=new JTable();
		refresh_table("src/data/storage/alternate.txt", table_mode2, table2, order_tab_title2,true);
		jScrollPane2=new JScrollPane(table2);
		jScrollPane2.setBounds(5, 40, 930, 345);
		tablePanel2.add(jScrollPane2);
		
		booking_button.setBounds(5,5,60,25);
		tablePanel2.add(booking_button);
		delete_button.setBounds(75,5,60,25);
		tablePanel2.add(delete_button);
		refresh_button2.setBounds(145,5,60,25);
		tablePanel2.add(refresh_button2);
		return_button2.setBounds(215,5,60,25);
		tablePanel2.add(return_button2);
		search_button2.setBounds(870, 5, 60, 25);
		tablePanel2.add(search_button2);
		search_bar2.setBounds(710, 6, 150, 23);
		tablePanel2.add(search_bar2);
		search_button2.setBounds(870, 5, 60, 25);
		tablePanel2.add(search_button2);
		
		delete_button.addActionListener(this);
		refresh_button2.addActionListener(this);
		return_button2.addActionListener(this);
		search_button2.addActionListener(this);
		//----------------------------------------------------------------------
		tabbedPane.add("成功购票",tablePanel1);
		tabbedPane.add("候补购票",tablePanel2);
		this.add(tabbedPane);
		this.setVisible(true);
	}
	public static void refresh_table(String src,DefaultTableModel table_mode,JTable table,String[] tab_title,boolean isReadtxt) {//列表刷新
		if(isReadtxt==true) {
			FileOperations.read_txt(src,Constant.queue);
		}
		table_mode =new DefaultTableModel();
		table_mode.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			table_mode.addRow(Constant.queue.poll());
		}
		table.setModel(table_mode);
	}
	public static void delete_line(JTable table) {
		int count=table.getSelectedRow();
		if(count>=0) {
			if(JOptionPane.showConfirmDialog(null, "是否删除当前所选候补信息", "注意", JOptionPane.YES_NO_OPTION)==JOptionPane.YES_OPTION) {
				FileOperations.delete_txt_line("src/data/storage/alternate.txt",table.getValueAt(count, 0).toString(),true);
				JOptionPane.showMessageDialog(null, "    删除成功！！", "提示", 1);
				refresh_table("src/data/storage/alternate.txt", table_mode2, table2, order_tab_title2,true);
			}
		}else {
			JOptionPane.showMessageDialog(null, "     请选中列表中的某一行！！", "提示", 1);
		}
	}
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(refund_button)) {//退票
			OrderWindow.refund_window(table_mode1,table1,order_tab_title1);
		}else if(e.getSource().equals(details_button1)) {//详情1
			OrderWindow.details_window(table1);
		}else if(e.getSource().equals(booking_button)){
			booking();
		}else if(e.getSource().equals(delete_button)) {//删除
			delete_line(table2);
		}else if(e.getSource().equals(refresh_button1)||e.getSource().equals(refresh_button2)) {//刷新
			refresh_table("src/data/storage/booking.txt", table_mode1, table1, order_tab_title1,true);
			refresh_table("src/data/storage/alternate.txt", table_mode2, table2, order_tab_title2,true);
		}else if(e.getSource().equals(return_button1)||e.getSource().equals(return_button2)) {//返回
			MainPanel.cardLayout.show(MainPanel.jPanel,"featuresPanel");
		}else if(e.getSource().equals(search_button1)) {
			FileOperations.search_txt_line("src/data/storage/booking.txt",search_bar1.getText(),Constant.queue,0);
			refresh_table("src/data/storage/booking.txt", table_mode1, table1, order_tab_title1,false);
		}else if(e.getSource().equals(search_button2)) {
			refresh_table("src/data/storage/alternate.txt", table_mode2, table2, order_tab_title2,false);
		}
	}
	public static void booking() {//订票界面
		int count=table2.getSelectedRow();
		if(count>=0) {
			String get_name= table2.getValueAt(count, 0).toString();
			String get_line=FileOperations.read_txt_lines("src/data/storage/flight.txt", get_name);
			String[] get_array=get_line.split("/");
			int get_total=Integer.parseInt(get_array[6]);
			int get_remaining=Integer.parseInt(get_array[7]);
			int get_alternate=Integer.parseInt(table2.getValueAt(count, 3).toString());
			//---------------界面搭建---------------------------------------------------------------
			JFrame booking_JFrame=new JFrame();
			JPanel booking_JPanel=new JPanel();
			booking_JFrame.setTitle("填写购票信息");
			booking_JFrame.setResizable(false);
			booking_JPanel.setLayout(null);
			booking_JFrame.setBounds(MainFrame.location_x,MainFrame.location_y,300,230);
			JLabel flight_number=new JLabel("航班号：");
			JLabel remaining_votes=new JLabel("剩余票数：");
			JLabel passenger_name=new JLabel("乘客姓名：");
			JLabel phone_number=new JLabel("手机号：");
			JLabel tickets_number=new JLabel("购买数量：");
			JTextField flight_number_TextField=new JTextField();
			JTextField remaining_votes_TextField=new JTextField();
			JTextField passenger_name_TextField=new JTextField();
			JTextField phone_number_TextField=new JTextField();
			JTextField tickets_number_TextField=new JTextField();
			JButton confirm_button=new JButton("确认");
			JButton cancel_button=new JButton("取消");
			flight_number.setBounds(20,10,80,20);flight_number_TextField.setBounds(100,10,150,20);flight_number_TextField.setEditable(false);
			booking_JPanel.add(flight_number);booking_JPanel.add(flight_number_TextField);
			remaining_votes.setBounds(20,40,80,20);remaining_votes_TextField.setBounds(100,40,150,20);remaining_votes_TextField.setEditable(false);
			booking_JPanel.add(remaining_votes);booking_JPanel.add(remaining_votes_TextField);
			passenger_name.setBounds(20,70,80,20);passenger_name_TextField.setBounds(100,70,150,20);
			booking_JPanel.add(passenger_name);booking_JPanel.add(passenger_name_TextField);
			phone_number.setBounds(20,100,80,20);phone_number_TextField.setBounds(100,100,150,20);
			booking_JPanel.add(phone_number);booking_JPanel.add(phone_number_TextField);
			tickets_number.setBounds(20,130,80,20);tickets_number_TextField.setBounds(100,130,150,20);
			booking_JPanel.add(tickets_number);booking_JPanel.add(tickets_number_TextField);
			confirm_button.setBounds(140,160,60,25);booking_JPanel.add(confirm_button);
			cancel_button.setBounds(210,160,60,25);booking_JPanel.add(cancel_button);
			booking_JPanel.setBackground(Color.white);
			booking_JFrame.add(booking_JPanel);
			booking_JFrame.setVisible(true);
			//---------------界面搭建---------------------------------------------------------------
			flight_number_TextField.setText(get_name);
			remaining_votes_TextField.setText(""+get_remaining);
			passenger_name_TextField.setText(table2.getValueAt(count, 1).toString());
			phone_number_TextField.setText(table2.getValueAt(count, 2).toString());
			if(get_alternate==1) {
				tickets_number_TextField.setEditable(false);
				tickets_number_TextField.setText("1");
			}
			confirm_button.addActionListener(
				new ActionListener() { 
					@Override
					public void actionPerformed(ActionEvent e) {
						int number_of_tickets=Integer.parseInt(tickets_number_TextField.getText().trim());
						if(number_of_tickets>get_alternate) {
							JOptionPane.showMessageDialog(null, "     输入的购买数量不能大于候补数量！！", "提示", 0);
							return;
						}else if(number_of_tickets>get_remaining){
							JOptionPane.showMessageDialog(null, "     输入的购买数量不能大于剩余数量！！", "提示", 0);
							return;
						}else if(number_of_tickets==get_alternate) {
							FileOperations.delete_txt_line("src/data/storage/alternate.txt", get_name, false);
						}else if(number_of_tickets<get_alternate) {
							String old_message_booking=OtherUtils.build_string(table2, count, 0, 4);
							String new_message_booking=OtherUtils.build_string(table2, count, 0, 2)+"/"+(get_alternate-number_of_tickets)+"/"+table2.getValueAt(count, 4).toString();
							FileOperations.revise_txt_line("src/data/storage/alternate.txt", old_message_booking, new_message_booking);
						}
						String seat_number=OtherUtils.produced_seat_number(get_total,get_remaining,number_of_tickets);
						String old_order=FileOperations.read_txt_lines("src/data/storage/booking.txt", get_name);
						String[] old_order_array=old_order.split("/");
						String new_order=OtherUtils.array_to_string(old_order_array, 0, 2)+"/"+(Integer.parseInt(old_order_array[3])+number_of_tickets)+"/"+old_order_array[4]+","+seat_number+"/"+OtherUtils.get_nowtime();
						FileOperations.revise_txt_line("src/data/storage/booking.txt",old_order,new_order);
						FileOperations.revise_txt_line("src/data/storage/flight.txt",get_line,OtherUtils.array_to_string(get_array, 0, 6)+"/"+(get_remaining-number_of_tickets));
						booking_JFrame.dispose();
						refresh_table("src/data/storage/alternate.txt",table_mode2,table2,order_tab_title2,true);
						refresh_table("src/data/storage/booking.txt", table_mode1, table1, order_tab_title1,true);
						JOptionPane.showMessageDialog(null, "购票人："+passenger_name_TextField.getText().trim()+"\n"+"座位号："+seat_number, "购票成功", 1);
					}
				}
			);
			cancel_button.addActionListener(
				new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						booking_JFrame.dispose();
					}
				}
			);
		}else {
			JOptionPane.showMessageDialog(null, "     请选中列表中的某一行！！", "提示", 0);
		}
	}
}
