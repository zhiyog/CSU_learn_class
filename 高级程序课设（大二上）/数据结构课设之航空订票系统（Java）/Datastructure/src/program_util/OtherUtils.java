package program_util;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JTable;

public class OtherUtils {
	public static String get_nowtime() {//��ȡ��ǰʱ�䷽��
		SimpleDateFormat formatter= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date(System.currentTimeMillis());
		return formatter.format(date);
	}
	public static String build_string(JTable table,int count,int start,int end) {//���ӱ���л�ȡ��������װ���ַ���
		String string="";
		for(int i=start;i<=end;i++) {
			string+=table.getValueAt(count, i).toString()+"/";
		}
		return string.substring(0,string.length()-1);
	}
	public static String produced_seat_number(int total,int remaining,int count) {//��λ�����ɷ�����������Ʊ����ʣ��Ʊ������������
		int start_seat_number=total-remaining+1;
		String seat_number="";
		for(int i=0;i<count;i++) {
			seat_number+=String.format("%03d", start_seat_number)+",";
			start_seat_number++;
		}
		return seat_number.substring(0,seat_number.length()-1);
	}
	public static String[] seat_number_deletion(String seat_number,int count) {//��λ��ɾ������������ԭ��λ�ţ���Ʊ��
		String[] result=new String[2];
			result[0]=seat_number.substring(0,seat_number.length()-4*count);
			result[1]=seat_number.substring(seat_number.length()-4*count+1,seat_number.length());//ʣ�����λ��
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
