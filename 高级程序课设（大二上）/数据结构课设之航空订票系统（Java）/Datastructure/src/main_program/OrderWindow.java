package main_program;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Queue;

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

//import com.sun.corba.se.spi.orbutil.fsm.Guard.Result;

import program_util.FileOperations;
import program_util.OtherUtils;

public class OrderWindow {
	public static void refresh_table(String src,DefaultTableModel table_mode,JTable table,String[] tab_title) {//列表刷新
		FileOperations.read_txt(src,Constant.queue);
		table_mode =new DefaultTableModel();
		table_mode.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			table_mode.addRow(Constant.queue.poll());
		}
		table.setModel(table_mode);
	}
	public static void refresh_order_table(JTable jTable,DefaultTableModel defaultTableModel,String src,String message,String[] tab_title) {//订单列表刷新
		FileOperations.search_txt_line(src,message,Constant.queue,1);
		defaultTableModel=new DefaultTableModel();
		defaultTableModel.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			defaultTableModel.addRow(Constant.queue.poll());
		}
		jTable.setModel(defaultTableModel);
	}
	public static void order_window(JTable table) {
		int count=table.getSelectedRow();
		String[] order_tab_title = { "航班号", "购票人", "手机号", "购买数量","座位号","购票时间" };//订单列表表头
		String[] alternate_tab_title = { "航班号", "购票人", "手机号", "候补数量","候补时间" };//候补列表表头
		if(count>=0) {
			String get_name= table.getValueAt(count, 0).toString();
			int get_total=Integer.parseInt(table.getValueAt(count, 6).toString());
			int get_remaining=Integer.parseInt(table.getValueAt(count, 7).toString());
			JFrame belong_order_JFrame=new JFrame();
			JPanel belong_order_JPanel=new JPanel();
			JPanel belong_alternate_JPanel=new JPanel();
			belong_order_JPanel.setLayout(new GridLayout(1,1));
			belong_alternate_JPanel.setLayout(new GridLayout(1,1));
			
			JTable belong_order_table = new JTable();
			JTable belong_alternate_table=new JTable();
			DefaultTableModel belong_order_table_mode = null;
			DefaultTableModel belong_alternate_table_mode=null;
			JTabbedPane tabbedPane=new JTabbedPane();
			
			refresh_order_table(belong_order_table,belong_order_table_mode,"src/data/storage/booking.txt",get_name,order_tab_title);
			refresh_order_table(belong_alternate_table,belong_alternate_table_mode,"src/data/storage/alternate.txt",get_name,alternate_tab_title);
			
			belong_order_JFrame.setTitle(get_name+"航班所有订单信息"+"     总票量："+get_total+"    剩余："+get_remaining);
			belong_order_JFrame.setResizable(false);
			belong_order_JFrame.setBounds(MainFrame.location_x,MainFrame.location_y,800,450);
			belong_order_JPanel.setBackground(Color.white);
			belong_alternate_JPanel.setBackground(Color.white);
			
			JScrollPane jScrollPane1=new JScrollPane(belong_order_table);
			belong_order_JPanel.add(jScrollPane1);
			JScrollPane jScrollPane2=new JScrollPane(belong_alternate_table);
			belong_alternate_JPanel.add(jScrollPane2);
			
			tabbedPane.setBounds(0, 0, 650, 400);
			tabbedPane.add("成功购票",belong_order_JPanel);
			tabbedPane.add("候补购票",belong_alternate_JPanel);
			belong_order_JFrame.add(tabbedPane);
			belong_order_JFrame.setVisible(true);
		}else {
			JOptionPane.showMessageDialog(null, "     请选中列表中的某一行！！", "提示", 1);
		}
	}
	public static void refund_window(DefaultTableModel table_mode,JTable table,String[] tab_title) {
		int count=table.getSelectedRow();
		if(count>=0) {
			JFrame jFrame=new JFrame();
			JPanel jPanel=new JPanel();
			jFrame.setBounds(MainFrame.location_x, MainFrame.location_y, 420, 180);
			JLabel flight_number=new JLabel("航班号：");
			JLabel ticket_buyer=new JLabel("购票人：");
			JLabel phone_number=new JLabel("手机号");
			JLabel number_of_tickets=new JLabel("购票数量：");
			JLabel ticket_purchase_time=new JLabel("购票时间：");
			JLabel number_of_refunds=new JLabel("退票数量：");
			JButton confirm_Button=new JButton("确认");
			JButton cancel_Button=new JButton("取消");
			
			JTextField flight_number_TextField=new JTextField();
			JTextField ticket_buyer_TextField=new JTextField();
			JTextField phone_number_TextField=new JTextField();
			JTextField number_of_tickets_TextField=new JTextField();
			JTextField ticket_purchase_time_TextField=new JTextField();
			JTextField number_of_refunds_TextField=new JTextField();
			
			jPanel.setLayout(null);
			jPanel.setBackground(Color.white);
			flight_number.setBounds(10, 10, 80, 20);jPanel.add(flight_number);
			flight_number_TextField.setBounds(90, 10, 100, 20);jPanel.add(flight_number_TextField);
			ticket_buyer.setBounds(200, 10, 80, 20);jPanel.add(ticket_buyer);
			ticket_buyer_TextField.setBounds(290, 10, 100, 20);jPanel.add(ticket_buyer_TextField);
			
			phone_number.setBounds(10, 40, 80, 20);jPanel.add(phone_number);
			phone_number_TextField.setBounds(90, 40, 100, 20);jPanel.add(phone_number_TextField);
			number_of_tickets.setBounds(200, 40, 80, 20);jPanel.add(number_of_tickets);
			number_of_tickets_TextField.setBounds(290, 40, 100, 20);jPanel.add(number_of_tickets_TextField);
			
			ticket_purchase_time.setBounds(10, 70, 80, 20);jPanel.add(ticket_purchase_time);
			ticket_purchase_time_TextField.setBounds(90,70,300,20);jPanel.add(ticket_purchase_time_TextField);
			number_of_refunds.setBounds(10, 100, 80, 20);jPanel.add(number_of_refunds);
			number_of_refunds_TextField.setBounds(90, 100, 100, 20);jPanel.add(number_of_refunds_TextField);
			
			confirm_Button.setBounds(330,100,60,25);jPanel.add(confirm_Button);
			cancel_Button.setBounds(260,100,60,25);jPanel.add(cancel_Button);
			
			flight_number_TextField.setEditable(false);
			ticket_buyer_TextField.setEditable(false);
			phone_number_TextField.setEditable(false);
			number_of_tickets_TextField.setEditable(false);
			ticket_purchase_time_TextField.setEditable(false);
			
			String flight_number_get=table.getValueAt(count, 0).toString();
			String ticket_buyer_get=table.getValueAt(count, 1).toString();
			String phone_number_get=table.getValueAt(count, 2).toString();
			
			String ticket_purchase_time_get=table.getValueAt(count, 5).toString();
			int number_of_tickets_get=Integer.parseInt(table.getValueAt(count, 3).toString());
			
			flight_number_TextField.setText(flight_number_get);
			ticket_buyer_TextField.setText(ticket_buyer_get);
			phone_number_TextField.setText(phone_number_get);
			number_of_tickets_TextField.setText(""+number_of_tickets_get);
			ticket_purchase_time_TextField.setText(ticket_purchase_time_get);
			
			if(number_of_tickets_get<2) {
				number_of_refunds_TextField.setText("1");
				number_of_refunds_TextField.setEditable(false);
			}
			confirm_Button.addActionListener(
				new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						// TODO Auto-generated method stub
						int number_of_refunds_get=Integer.parseInt(number_of_refunds_TextField.getText());
						String[] refund_seat=OtherUtils.seat_number_deletion(table.getValueAt(count, 4).toString(),number_of_refunds_get);
						if(number_of_refunds_get<=0) {
							JOptionPane.showMessageDialog(null, "     退票数量不能是0和负数！！", "提示", 1);
							return;
						}else if(number_of_refunds_get>number_of_tickets_get) {
							JOptionPane.showMessageDialog(null, "     退票数量超出购买数量！！", "提示", 1);
							return;
						}else if(number_of_refunds_get==number_of_tickets_get) {
							FileOperations.delete_txt_line("src/data/storage/booking.txt", flight_number_get, false);
						}else if(number_of_refunds_get<number_of_tickets_get) {
							String old_message_booking=OtherUtils.build_string(table, count, 0, 5);
							String new_message_booking=OtherUtils.build_string(table, count, 0, 2)+"/"+(number_of_tickets_get-number_of_refunds_get)+"/"+refund_seat[0]+"/"+ticket_purchase_time_get;
							FileOperations.revise_txt_line("src/data/storage/booking.txt", old_message_booking, new_message_booking);
						}
						String old_message_flight=FileOperations.read_txt_lines("src/data/storage/flight.txt",table.getValueAt(count, 0).toString());
						String[] get_array=old_message_flight.split("/");
						String new_message_flight=get_array[0]+"/"+get_array[1]+"/"+get_array[2]+"/"+get_array[3]+"/"+get_array[4]+"/"+get_array[5]+"/"+get_array[6]+"/"+(Integer.parseInt(get_array[7])+number_of_refunds_get);
						FileOperations.revise_txt_line("src/data/storage/flight.txt",old_message_flight,new_message_flight);
						jFrame.dispose();
						refresh_table("src/data/storage/booking.txt", table_mode, table,tab_title);
						JOptionPane.showMessageDialog(null, "     退票成功！！", "提示", 1);
						
						FileOperations.search_txt_line("src/data/storage/alternate.txt",flight_number_get,Constant.queue,1);
						if(Constant.queue.size()>0) {
							JOptionPane.showMessageDialog(null, "当前航班存在候补乘客，请转到“候补购票”面板查看", "提示", 1);
							Constant.queue.clear();
						}
					}
				}
			);
			cancel_Button.addActionListener(
				new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						// TODO Auto-generated method stub
						jFrame.dispose();
					}
				}
			);
			jFrame.add(jPanel);
			jFrame.setTitle("退票");
			jFrame.setResizable(false);
			jFrame.setVisible(true);
		}else {
			JOptionPane.showMessageDialog(null, "     请选中列表中的某一行！！", "提示", 1);
		}
	}

	public static void details_window(JTable table) {//详情界面
		int count=table.getSelectedRow();
		if(count>=0) {
			JFrame jFrame=new JFrame();
			JPanel jPanel=new JPanel();
			jFrame.setBounds(MainFrame.location_x, MainFrame.location_y, 430, 220);
			JLabel flight_number=new JLabel("航班号：");
			JLabel starting_station=new JLabel("起始站：");
			JLabel end_station=new JLabel("终点站：");
			JLabel departure_time=new JLabel("出发时间：");
			JLabel arrival_time=new JLabel("到站时间：");
			JLabel ticket_buyer=new JLabel("购票人：");
			JLabel phone_number=new JLabel("手机号");
			JLabel number_of_tickets=new JLabel("购票数量：");
			JLabel ticket_purchase_time=new JLabel("购票时间：");
			
			JTextField flight_number_TextField=new JTextField();
			JTextField ticket_buyer_TextField=new JTextField();
			JTextField phone_number_TextField=new JTextField();
			JTextField number_of_tickets_TextField=new JTextField();
			JTextField ticket_purchase_time_TextField=new JTextField();
			JTextField starting_station_TextField=new JTextField();
			JTextField end_station_TextField=new JTextField();
			JTextField departure_time_TextField=new JTextField();
			JTextField arrival_time_TextField=new JTextField();
			
			jPanel.setLayout(null);
			jPanel.setBackground(Color.white);
			flight_number.setBounds(10, 10, 80, 20);jPanel.add(flight_number);
			flight_number_TextField.setBounds(90, 10, 110, 20);jPanel.add(flight_number_TextField);
			ticket_buyer.setBounds(210, 10, 80, 20);jPanel.add(ticket_buyer);
			ticket_buyer_TextField.setBounds(290, 10, 110, 20);jPanel.add(ticket_buyer_TextField);
			
			phone_number.setBounds(10, 40, 80, 20);jPanel.add(phone_number);
			phone_number_TextField.setBounds(90, 40, 110, 20);jPanel.add(phone_number_TextField);
			number_of_tickets.setBounds(210, 40, 80, 20);jPanel.add(number_of_tickets);
			number_of_tickets_TextField.setBounds(290, 40, 110, 20);jPanel.add(number_of_tickets_TextField);
			
			ticket_purchase_time.setBounds(10, 70, 80, 20);jPanel.add(ticket_purchase_time);
			ticket_purchase_time_TextField.setBounds(90,70,310,20);jPanel.add(ticket_purchase_time_TextField);
			starting_station.setBounds(10,100,80,20);jPanel.add(starting_station);
			starting_station_TextField.setBounds(90,100,110,20);jPanel.add(starting_station_TextField);
			end_station.setBounds(210,100,80,20);jPanel.add(end_station);
			end_station_TextField.setBounds(290,100,110,20);jPanel.add(end_station_TextField);
			departure_time.setBounds(10,130,80,20);jPanel.add(departure_time);
			departure_time_TextField.setBounds(90,130,110,20);jPanel.add(departure_time_TextField);
			arrival_time.setBounds(210,130,80,20);jPanel.add(arrival_time);
			arrival_time_TextField.setBounds(290,130,110,20);jPanel.add(arrival_time_TextField);
			
			flight_number_TextField.setEditable(false);
			ticket_buyer_TextField.setEditable(false);
			phone_number_TextField.setEditable(false);
			number_of_tickets_TextField.setEditable(false);
			ticket_purchase_time_TextField.setEditable(false);
			starting_station_TextField.setEditable(false);
			end_station_TextField.setEditable(false);
			departure_time_TextField.setEditable(false);
			arrival_time_TextField.setEditable(false);
			
			flight_number_TextField.setText(table.getValueAt(count, 0).toString());
			ticket_buyer_TextField.setText(table.getValueAt(count, 1).toString());
			phone_number_TextField.setText(table.getValueAt(count, 2).toString());
			number_of_tickets_TextField.setText(table.getValueAt(count, 3).toString());
			ticket_purchase_time_TextField.setText(table.getValueAt(count, 5).toString());
			
			String[] get_array=FileOperations.read_txt_lines("src/data/storage/flight.txt", table.getValueAt(count, 0).toString()).split("/");
			starting_station_TextField.setText(get_array[1]);
			end_station_TextField.setText(get_array[2]);
			departure_time_TextField.setText(get_array[3]);
			arrival_time_TextField.setText(get_array[4]);
			
			jFrame.add(jPanel);
			jFrame.setTitle("详情");
			jFrame.setResizable(false);
			jFrame.setVisible(true);
		}else {
			JOptionPane.showMessageDialog(null, "     请选中列表中的某一行！！", "提示", 1);
		}
	}
}
