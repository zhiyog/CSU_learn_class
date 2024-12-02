package main_program;

import java.awt.Color;
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
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

import program_util.DateChooser;
import program_util.FileOperations;

public class SearchPanel extends JPanel implements ActionListener{
	static JButton add_route=new JButton("添加航班");
	static JButton delete_route=new JButton("删除航班");
	static JButton belong_order=new JButton("订单");
	static JTextField search_bar=new JTextField();
	static JButton search_button=new JButton("搜索");
	static JButton refresh_button=new JButton("刷新");
	static JButton return_button=new JButton("返回");
	private JTable table;
	public JPanel tablePanel;
	private DefaultTableModel table_mode;
	String[] tab_title = { "航班号", "起始站", "终点站", "出发时间","到站时间","乘员定额","总票量","剩余票数" };//表头
	String[] order_tab_title = { "航班号", "乘客姓名", "手机号", "购买数量","购票时间" };//订单列表表头
	
	public static String[][] queue_to_array(Queue<String[]> queue){
		int count=0;
		String[][] get_queue_data=new String[queue.size()][7];
		while (queue.size()>0){
			get_queue_data[count]=queue.poll();
			count++;
		}
		return get_queue_data;
	}
	public void add_window() {
		JFrame add_window_JFrame=new JFrame();
		JPanel add_window_JPanel=new JPanel();
		JTextField flight_number=new JTextField();//航班号
		JTextField starting_station=new JTextField();//起始站
		JTextField terminal_station=new JTextField();//终点站
		JTextField departure_time=new JTextField();//出发时间
		JTextField arrival_time=new JTextField();//到站时间
		JTextField crew_quota=new JTextField();//乘员定额
		JTextField total_votes=new JTextField();//总票量
		JLabel flight_number_title=new JLabel("航班号");
		JLabel starting_station_title=new JLabel("起始站");
		JLabel terminal_station_title=new JLabel("终点站");
		JLabel departure_time_title=new JLabel("出发时间");
		JLabel arrival_time_title=new JLabel("到站时间");
		JLabel crew_quota_title=new JLabel("乘员定额");
		JLabel total_votes_title=new JLabel("总票量");
		JButton sure_button=new JButton("确定");
		JButton cancel_button=new JButton("取消"); 
		
		add_window_JFrame.setTitle("添加航班");
		add_window_JFrame.setResizable(false);
		add_window_JFrame.setBounds(MainFrame.location_x,MainFrame.location_y,500,300);
		
		add_window_JPanel.setLayout(null);
		flight_number_title.setBounds(20,10,80,20);
		add_window_JPanel.add(flight_number_title);
		flight_number.setBounds(90,10,200,20);
		add_window_JPanel.add(flight_number);
		starting_station_title.setBounds(20,40,80,20);
		add_window_JPanel.add(starting_station_title);
		starting_station.setBounds(90,40,200,20);
		add_window_JPanel.add(starting_station);
		terminal_station_title.setBounds(20,70,80,20);
		terminal_station.setBounds(90,70,200,20);
		add_window_JPanel.add(terminal_station);
		add_window_JPanel.add(terminal_station_title);
		departure_time_title.setBounds(20,100,80,20);
		departure_time.setBounds(90,100,200,20);
		DateChooser dateChooser1 = DateChooser.getInstance("yyyy-MM-dd HH:MM");
		dateChooser1.register(departure_time);
		add_window_JPanel.add(departure_time_title);
		add_window_JPanel.add(departure_time);
		arrival_time_title.setBounds(20,130,80,20);
		arrival_time.setBounds(90,130,200,20);
		DateChooser dateChooser2 = DateChooser.getInstance("yyyy-MM-dd HH:MM");
		dateChooser2.register(arrival_time);
		add_window_JPanel.add(arrival_time_title);
		add_window_JPanel.add(arrival_time);
		crew_quota_title.setBounds(20,160,80,20);
		crew_quota.setBounds(90,160,200,20);
		add_window_JPanel.add(crew_quota_title);
		add_window_JPanel.add(crew_quota);
		total_votes_title.setBounds(20,190,80,20);
		total_votes.setBounds(90,190,200,20);
		add_window_JPanel.add(total_votes_title);
		add_window_JPanel.add(total_votes);
		
		sure_button.setBounds(300,220,60,30);
		add_window_JPanel.add(sure_button);
		cancel_button.setBounds(380,220,60,30);
		add_window_JPanel.add(cancel_button);
		
		add_window_JPanel.setBackground(Color.white);
		add_window_JFrame.add(add_window_JPanel);
		add_window_JFrame.setVisible(true);
		sure_button.addActionListener(
			new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String get_data="\n"+flight_number.getText()+"/"+starting_station.getText()+"/"+terminal_station.getText()+"/"+departure_time.getText()
					+"/"+arrival_time.getText()+"/"+crew_quota.getText()+"/"+total_votes.getText()+"/"+total_votes.getText();
					FileOperations.write_txt("src/data/storage/flight.txt",get_data);
					refresh_table();
					add_window_JFrame.dispose();
				}
			}
		);
		cancel_button.addActionListener(
			new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					add_window_JFrame.dispose();
				}
			}
		);
	}
	public void delete() {
		int count=table.getSelectedRow();
		if(count>=0) {
			String getname= table.getValueAt(count, 0).toString();
			FileOperations.delete_txt_line("src/data/storage/flight.txt", getname, false);
			refresh_table();
		}else {
			JOptionPane.showMessageDialog(null, "     请选中列表中的某一行！！", "提示", 0);
		}
	}
	public void refresh_table() {//列表刷新
		FileOperations.read_txt("src/data/storage/flight.txt",Constant.queue);
		table_mode =new DefaultTableModel();
		table_mode.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			table_mode.addRow(Constant.queue.poll());
		}
		table.setModel(table_mode);
	}
	public void refresh_order_table(JTable jTable,DefaultTableModel defaultTableModel,String src,String message) {//订单列表刷新
		FileOperations.search_txt_line(src,message,Constant.queue,1);
		defaultTableModel=new DefaultTableModel();
		defaultTableModel.setColumnIdentifiers(order_tab_title);
		while(Constant.queue.size()>0) {
			defaultTableModel.addRow(Constant.queue.poll());
		}
		jTable.setModel(defaultTableModel);
	}
	public void search_table() {
		FileOperations.search_txt_line("src/data/storage/flight.txt",search_bar.getText(),Constant.queue,0);
		table_mode =new DefaultTableModel();
		table_mode.setColumnIdentifiers(tab_title);
		while(Constant.queue.size()>0) {
			table_mode.addRow(Constant.queue.poll());
		}
		table.setModel(table_mode);
	}
	public SearchPanel(){
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
        
        add_route.setBounds(10,5,80,30);
        this.add(add_route);
        delete_route.setBounds(100,5,80,30);
        this.add(delete_route);
        belong_order.setBounds(190,5,80,30);
        this.add(belong_order);
        refresh_button.setBounds(280,5,80,30);
        this.add(refresh_button);
        return_button.setBounds(370,5,80,30);
        this.add(return_button);
        search_bar.setBounds(635,7,200,27);
        this.add(search_bar);
        search_button.setBounds(855,5,80,30);
        this.add(search_button);
        
        add_route.addActionListener(this);
        delete_route.addActionListener(this);
        belong_order.addActionListener(this);
        search_button.addActionListener(this);
        refresh_button.addActionListener(this);
        return_button.addActionListener(this);
        
        this.setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(add_route)) {
			add_window();
		}else if(e.getSource().equals(delete_route)) {
			delete();
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
