package main_program;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;
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
import program_util.DateChooser;
import program_util.FileOperations;
import program_util.OtherUtils;

public class AddPanel extends JPanel implements ActionListener{
	Font font=new Font("΢���ź�", Font.PLAIN, 15);
	
	static JButton booking_route=new JButton("��Ʊ");
	static JButton refresh_button=new JButton("ˢ��");
	static JButton belong_order=new JButton("����");
	static JButton search_button=new JButton("����");
	static JButton return_button=new JButton("����");
	
	static JLabel starting_station=new JLabel("��ʼվ");
	static JLabel terminal_station=new JLabel("�յ�վ");
	static JLabel departure_time=new JLabel("����");
	
	static JTextField starting_station_textField=new JTextField();
	static JTextField terminal_station_textField=new JTextField();
	static JTextField departure_time_textField=new JTextField();
	
	private static JTable table;
	public JPanel tablePanel;
	private static DefaultTableModel table_mode;
	static String[] tab_title = { "�����", "��ʼվ", "�յ�վ", "����ʱ��","��վʱ��","��Ա����","��Ʊ��","ʣ��Ʊ��" };//��ͷ
	
	public static String[][] queue_to_array(Queue<String[]> queue){
		int count=0;
		String[][] get_queue_data=new String[queue.size()][7];
		while (queue.size()>0){
			get_queue_data[count]=queue.poll();
			count++;
		}
		return get_queue_data;
	}
	public void delete() {
		int count=table.getSelectedRow();
		if(count>=0) {
			String getname= table.getValueAt(count, 0).toString();
			FileOperations.delete_txt_line("src/data/storage/flight.txt", getname, false);
			refresh_table();
		}else {
			JOptionPane.showMessageDialog(null, "     ��ѡ���б��е�ĳһ�У���", "��ʾ", 0);
		}
	}
	public static void refresh_table() {//�б�ˢ��
		FileOperations.read_txt("src/data/storage/flight.txt",Constant.queue);
		table_mode =new DefaultTableModel();
		table_mode.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			table_mode.addRow(Constant.queue.poll());
		}
		table.setModel(table_mode);
	}
	public void search_table() {
		FileOperations.filter_txt("src/data/storage/flight.txt",starting_station_textField.getText(),terminal_station_textField.getText(),departure_time_textField.getText(),Constant.queue);
		table_mode =new DefaultTableModel();
		table_mode.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			table_mode.addRow(Constant.queue.poll());
		}
		table.setModel(table_mode);
	}
	public static void booking() {//��Ʊ����
		int count=table.getSelectedRow();
		if(count>=0) {
			String get_name= table.getValueAt(count, 0).toString();
			int get_total= Integer.parseInt(table.getValueAt(count, 6).toString());
			int get_remaining= Integer.parseInt(table.getValueAt(count, 7).toString());
			//---------------����---------------------------------------------------------------
			JFrame booking_JFrame=new JFrame();
			JPanel booking_JPanel=new JPanel();
			booking_JFrame.setTitle("��д��Ʊ��Ϣ");
			booking_JFrame.setResizable(false);
			booking_JPanel.setLayout(null);
			booking_JFrame.setBounds(MainFrame.location_x,MainFrame.location_y,300,230);
			JLabel flight_number=new JLabel("����ţ�");
			JLabel remaining_votes=new JLabel("ʣ��Ʊ����");
			JLabel passenger_name=new JLabel("�˿�������");
			JLabel phone_number=new JLabel("�ֻ��ţ�");
			JLabel tickets_number=new JLabel("����������");
			JTextField flight_number_TextField=new JTextField();
			JTextField remaining_votes_TextField=new JTextField();
			JTextField passenger_name_TextField=new JTextField();
			JTextField phone_number_TextField=new JTextField();
			JTextField tickets_number_TextField=new JTextField();
			JButton confirm_button=new JButton("ȷ��");
			JButton cancel_button=new JButton("ȡ��");
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
			//---------------����---------------------------------------------------------------
			flight_number_TextField.setText(get_name);
			remaining_votes_TextField.setText(""+get_remaining);
			confirm_button.addActionListener(
				new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						int number_of_tickets=Integer.parseInt(tickets_number_TextField.getText().trim());
						//--------------------------------------������Ʊ��������------------------------------------------------
						if(number_of_tickets>get_remaining) {
							int whether_num=JOptionPane.showConfirmDialog(null, "��ǰ��Ʊ���㣬�Ƿ񽫲����Ʊ��Ӻ�����", "��Ʊ����", JOptionPane.YES_NO_OPTION);
							if(whether_num==JOptionPane.YES_OPTION) {
								int alternate_number=number_of_tickets-get_remaining;//��ӵ���Ʊ������
								number_of_tickets=get_remaining;
								FileOperations.write_txt("src/data/storage/alternate.txt", "\n"+get_name.trim()+"/"+passenger_name_TextField.getText().trim()+"/"+phone_number_TextField.getText().trim()+"/"+alternate_number+"/"+OtherUtils.get_nowtime());
								if(number_of_tickets==0) {
									return;
								}
							}else {
								return;
							}
						}
						//--------------------------------------������Ʊ��������------------------------------------------------
						String seat_number=OtherUtils.produced_seat_number(get_total,get_remaining,number_of_tickets);
						FileOperations.write_txt("src/data/storage/booking.txt", "\n"+get_name.trim()+"/"+passenger_name_TextField.getText().trim()+"/"+phone_number_TextField.getText().trim()+"/"+number_of_tickets+"/"+seat_number+"/"+OtherUtils.get_nowtime());
						FileOperations.revise_txt_line("src/data/storage/flight.txt",OtherUtils.build_string(table, count, 0, 7),OtherUtils.build_string(table, count, 0, 6)+"/"+(get_remaining-number_of_tickets));
						booking_JFrame.dispose();
						refresh_table();
						JOptionPane.showMessageDialog(null, "��Ʊ�ˣ�"+passenger_name_TextField.getText().trim()+"\n"+"��λ�ţ�"+seat_number, "��Ʊ�ɹ�", 1);
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
			JOptionPane.showMessageDialog(null, "     ��ѡ���б��е�ĳһ�У���", "��ʾ", 0);
		}
	}
	public AddPanel(){
		this.setLayout(null);
		this.setBackground(Color.white);
		tablePanel=new JPanel();
		tablePanel.setLayout(new GridLayout(1,1));
		table=new JTable();
		refresh_table();
        JScrollPane jScrollPane=new JScrollPane(table);
        tablePanel.add(jScrollPane);
        tablePanel.setVisible(true);
        tablePanel.setBounds(10,40,925,370);
        tablePanel.setBackground(Color.white);
        this.add(tablePanel);
        
        booking_route.setBounds(10,5,80,30);
        this.add(booking_route);
        belong_order.setBounds(100,5,80,30);
        this.add(belong_order);
        refresh_button.setBounds(190,5,80,30);
        this.add(refresh_button);
        return_button.setBounds(280,5,80,30);
        this.add(return_button);
        starting_station.setBounds(435,5,60,30);
        this.add(starting_station);
        starting_station_textField.setBounds(495,7,60,27);
        this.add(starting_station_textField);
        terminal_station.setBounds(565,5,60,30);
        this.add(terminal_station);
        terminal_station_textField.setBounds(625,7,60,27);
        this.add(terminal_station_textField);
        departure_time.setBounds(695,5,40,30);
        this.add(departure_time);
        departure_time_textField.setBounds(735,7,100,27);
		DateChooser dateChooser2 = DateChooser.getInstance("yyyy-MM-dd");
		dateChooser2.register(departure_time_textField);
        this.add(departure_time_textField);
        search_button.setBounds(855,5,80,30);
        this.add(search_button);
        
        starting_station.setFont(font);
        terminal_station.setFont(font);
        departure_time.setFont(font);
        
        booking_route.addActionListener(this);
        belong_order.addActionListener(this);
        search_button.addActionListener(this);
        refresh_button.addActionListener(this);
        return_button.addActionListener(this);
        
        this.setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(booking_route)) {
			booking();
		}else if(e.getSource().equals(belong_order)) {
			OrderWindow.order_window(table);
		}else if(e.getSource().equals(search_button)) {
			search_table();
		}else if(e.getSource().equals(refresh_button)) {
			refresh_table();
		}else if(e.getSource().equals(return_button)) {
			MainPanel.cardLayout.show(MainPanel.jPanel,"featuresPanel");
		}
	}
}