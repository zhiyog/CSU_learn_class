package program_util;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.LineNumberReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;

import com.sun.org.apache.bcel.internal.generic.IF_ACMPEQ;

public class FileOperations {
	public static void read_txt(String src,Queue<String[]> queue){//读取文件方法
		try {
	        File file = new File(src); 
	        FileReader fileReader = new FileReader(file);  
	        LineNumberReader reader = new LineNumberReader(fileReader);
	        int number = 1;
	        String txt = "";
	        int lines = 0;//从第一行开始读取
	        while (txt != null) {
	            lines++;
	            txt = reader.readLine();  
	            if (lines > number&&txt!=null&&!txt.trim().equals("")) {
	            	String[] data=txt.split("/");
	            	queue.offer(data);
	            }
	        }
			reader.close();
			fileReader.close();
		}catch (IOException e) {
			System.out.println("读取文件出错");
		}
	}
	public static String read_txt_lines(String src,String flight_number){//读取文件某一行的方法，传入文件地址和航班号
		try {
	        File file = new File(src);
	        FileReader fileReader = new FileReader(file);  
	        LineNumberReader reader = new LineNumberReader(fileReader);
	        int number = 1;
	        String txt = "";
	        int lines = 0;//从第一行开始读取
	        while (txt != null) {
	            lines++;
	            txt = reader.readLine();
	            if (lines > number&&txt!=null&&!txt.trim().equals("")) {
	            	String[] data=txt.split("/");
	            	if(flight_number.trim().equals(data[0])) {
	        			reader.close();
	        			fileReader.close();
	            		return txt;
	            	}
	            }
	        }
			reader.close();
			fileReader.close();
		}catch (IOException e) {
			System.out.println("读取文件出错");
		}
		return null;
	}
    public static void write_txt(String src,String message){//写入文件
    	try {
	        File file = new File(src);
	        BufferedWriter out = new BufferedWriter(new FileWriter(file,true));
	        out.write(message);
	        out.flush();
	        out.close();
    	}catch (IOException e) {
			System.out.println("写入文件出错");
		}
    }
    public static Map<String, Object> delete_txt_line(String file, String message, boolean upRemoveLine) {//删除指定行，依据航班号匹配

        Map<String, Object> map = new HashMap<>(8);
        map.put("success", false);
        map.put("error", "");
        try {
            //获取原文件
            File oldFile = new File(file);
            if (!oldFile.isFile()) {
                map.put("error", "该文件未找到:" + file);
                return map;
            }
            //构造临时文件
            File newFile = new File(oldFile.getAbsolutePath() + ".tmp");
            BufferedReader br = new BufferedReader(new FileReader(file));
            PrintWriter pw = new PrintWriter(new FileWriter(newFile));

            String line = null;//某一行的值
            while ((line = br.readLine()) != null) {
            	String[] data=line.split("/");
                if (!data[0].trim().equals(message)) {
                    pw.println(line);
                    pw.flush();
                }
            }
            pw.close();
            br.close();
            //删除原文件
            if (!oldFile.delete()) {
                map.put("error", "该文件删除失败:" + file);
                return map;
            }
            //重命名
            if (!newFile.renameTo(oldFile)) {
                map.put("error", "该文件重命名失败:" + file);
                return map;
            }
            map.put("success", true);
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            map.put("error", ex.getMessage());
        } catch (IOException ex) {
            ex.printStackTrace();
            map.put("error", ex.getMessage());
        }
        return map;
    }
    public static Map<String, Object> revise_txt_line(String file, String old_message,String new_message) {//修改指定行

        Map<String, Object> map = new HashMap<>(8);
        map.put("success", false);
        map.put("error", "");
        try {
            //获取原文件
            File oldFile = new File(file);
            if (!oldFile.isFile()) {
                map.put("error", "该文件未找到:" + file);
                return map;
            }
            //构造临时文件
            File newFile = new File(oldFile.getAbsolutePath() + ".tmp");
            BufferedReader br = new BufferedReader(new FileReader(file));
            PrintWriter pw = new PrintWriter(new FileWriter(newFile));

            String line = null;//某一行的值
            while ((line = br.readLine()) != null) {
                if (!old_message.equals(line)) {
                    pw.println(line);
                    pw.flush();
                }else {
                    pw.println(new_message);
                    pw.flush();
                }
            }
            pw.close();
            br.close();
            //删除原文件
            if (!oldFile.delete()) {
                map.put("error", "该文件删除失败:" + file);
                return map;
            }
            //重命名
            if (!newFile.renameTo(oldFile)) {
                map.put("error", "该文件重命名失败:" + file);
                return map;
            }
            map.put("success", true);
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            map.put("error", ex.getMessage());
        } catch (IOException ex) {
            ex.printStackTrace();
            map.put("error", ex.getMessage());
        }
        return map;
    }

	public static void filter_txt(String src,String starting_point,String end_point,String departure_time,Queue<String[]> queue){//筛选航线方法
		try {
	        File file = new File(src); 
	        FileReader fileReader = new FileReader(file);  
	        LineNumberReader reader = new LineNumberReader(fileReader);
	        int number = 1;
	        String txt = "";
	        int lines = 0;
	        while (txt != null) {
	            lines++;
	            txt = reader.readLine();  
	            if (lines > number&&txt!=null&&!txt.trim().equals("")) {
	            	String[] data=txt.split("/");
	            	if(starting_point.trim().equals(data[1])&&end_point.trim().equals(data[2])&&departure_time.trim().equals(data[3].substring(0, 10)))
	            	queue.offer(data);
	            }
	        }
			reader.close();
			fileReader.close();
		}catch (IOException e) {
			System.out.println("读取文件出错");
		}
	}
	public static void search_txt_line(String src,String message,Queue<String[]> queue,int model){//关键词搜索,model:0为全部匹配，1为只匹配航班号
		try {
	        File file = new File(src); 
	        FileReader fileReader = new FileReader(file);  
	        LineNumberReader reader = new LineNumberReader(fileReader);
	        int number = 1;
	        String txt = "";
	        int lines = 0;//从第一行开始读取
	        message=message.trim();
	        while (txt != null) {
	            lines++;
	            txt = reader.readLine();  
	            if (lines > number&&txt!=null&&!txt.trim().equals("")) {
	            	String[] data=txt.split("/");
	            	if((model==0)&&(message.equals(data[0])||message.equals(data[1])||message.equals(data[2])||message.equals(data[3])||message.equals(data[4])||message.equals(data[5])))
	            		queue.offer(data);
	            	else if((model==1)&&(message.equals(data[0])))
	            		queue.offer(data);
	            }
	        }
			reader.close();
			fileReader.close();
		}catch (IOException e) {
			System.out.println("读取文件出错");
		}
	}
}
