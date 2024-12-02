package program_util;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JTable;

public class OtherUtils {
	public static String get_nowtime() {//获取当前时间方法
		SimpleDateFormat formatter= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date(System.currentTimeMillis());
		return formatter.format(date);
	}
	public static String build_string(JTable table,int count,int start,int end) {//将从表格中获取的数据组装成字符串
		String string="";
		for(int i=start;i<=end;i++) {
			string+=table.getValueAt(count, i).toString()+"/";
		}
		return string.substring(0,string.length()-1);
	}
	public static String produced_seat_number(int total,int remaining,int count) {//座位号生成方法，传入总票数，剩余票数，购买数量
		int start_seat_number=total-remaining+1;
		String seat_number="";
		for(int i=0;i<count;i++) {
			seat_number+=String.format("%03d", start_seat_number)+",";
			start_seat_number++;
		}
		return seat_number.substring(0,seat_number.length()-1);
	}
	public static String[] seat_number_deletion(String seat_number,int count) {//座位号删减方法，传入原座位号，退票数
		String[] result=new String[2];
			result[0]=seat_number.substring(0,seat_number.length()-4*count);
			result[1]=seat_number.substring(seat_number.length()-4*count+1,seat_number.length());//剩余的座位号
		return result;
	}
	public static String array_to_string(String[] data,int start,int end) {
		String result="";
		for(int i=start;i<=end;i++) {
			result+=data[i]+"/";
		}
		return result.substring(0,result.length()-1);
	}
}
