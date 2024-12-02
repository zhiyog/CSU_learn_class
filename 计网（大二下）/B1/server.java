package chat;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

class server extends JFrame implements Runnable, ListSelectionListener, ActionListener {
    private Socket s = null;
    private ServerSocket ss = null;
    private ArrayList<ChatThread> users = new ArrayList<ChatThread>(); //容量能够动态增长的数组
    DefaultListModel<String> dl = new DefaultListModel<String>();
    private JList<String> userList = new JList<String>(dl);//显示对象列表并且允许用户选择一个或多个项的组件。单独的模型 ListModel 维护列表的内容。

    private JPanel jpl = new JPanel();
    private JButton jbt = new JButton("踢出聊天室");
    private JButton jbt1 = new JButton("群发消息");
    //群发消息输入栏
    private JTextField jtf = new JTextField();

    public server() throws Exception{
        this.setTitle("服务器端");
        this.add(userList, "North");//放在北面
        this.add(jpl, "South");

        //仅将群发消息输入栏设为一栏
        jtf.setColumns(1);
        jpl.setLayout(new BorderLayout());
        jpl.add(jtf, BorderLayout.NORTH);
        jpl.add(jbt,BorderLayout.EAST);//踢出聊天室
        jpl.add(jbt1, BorderLayout.WEST);//群发消息

        //实现群发
        jbt1.addActionListener(this);
        //实现踢人
        jbt.addActionListener(this);


        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLocation(400,100);
        this.setSize(500, 400);
        this.setVisible(true);
        this.setAlwaysOnTop(true);
        ss = new ServerSocket(9999);
        new Thread(this).start();//监听用户端的加入
    }
    @Override
    public void run() {
        while(true){
            try{
                s = ss.accept();
                ChatThread ct = new ChatThread(s); //为该客户开一个线程
                users.add(ct); //将每个线程加入到users
                //发送Jlist里的用户登陆信息，为了防止后面登陆的用户无法更新有前面用户的好友列表
                ListModel<String> model = userList.getModel();//获取Jlist的数据内容
                for(int i = 0; i < model.getSize(); i++){
                    ct.ps.println("USERS#" + model.getElementAt(i));
                }
                ct.start();
            }catch (Exception ex){
                ex.printStackTrace();
                javax.swing.JOptionPane.showMessageDialog(this,"服务器异常！");
                System.exit(0);
            }
        }
    }

    //群发消息按钮点击事件监听
    @Override
    public void actionPerformed(ActionEvent e) {
        String label = e.getActionCommand();
        if(label.equals("群发消息")){
            handleAll();
        }else if(label.equals("踢出聊天室")){
            try {
                handleExpel();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }

    public void handleAll(){
        if(!jtf.getText().equals("")){
            sendMessage("ALL#" + jtf.getText());
            //发送完后，是输入框中内容为空
            jtf.setText("");
        }
    }//群发消息

    public void handleExpel() throws IOException {
        sendMessage("OFFLINE#" + userList.getSelectedValuesList().get(0));
        dl.removeElement(userList.getSelectedValuesList().get(0));//更新defaultModel
        userList.repaint();//更新Jlist
    }//踢人

    public class ChatThread extends Thread{
        Socket s = null;
        private BufferedReader br = null;
        private PrintStream ps = null;
        public boolean canRun = true;
        String nickName = null;
        public ChatThread(Socket s) throws Exception{
            this.s = s;
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            ps = new PrintStream(s.getOutputStream());
        }
        public void run(){
            while(canRun){
                try{
                    String msg = br.readLine();//接收客户端发来的消息
                    String[] strs = msg.split("#");
                    if(strs[0].equals("LOGIN")){//收到来自客户端的上线消息
                        nickName = strs[1];
                        dl.addElement(nickName);
                        userList.repaint();
                        sendMessage(msg);
                    }else if(strs[0].equals("MSG") || strs[0].equals("SMSG") || strs[0].equals("FSMSG")){
                        sendMessage(msg);
                    }else if(strs[0].equals("OFFLINE")){//收到来自客户端的下线消息
                        sendMessage(msg);
                        //System.out.println(msg);
                        dl.removeElement(strs[1]);
                        // 更新List列表
                        userList.repaint();
                    }
                }catch (Exception ex){}
            }
        }
    }

    public void sendMessage(String msg){  //服务器端发送给所有用户
        for(ChatThread ct : users){
            ct.ps.println(msg);
        }
    }

    @Override
    public void valueChanged(ListSelectionEvent e) {
        // TODO 自动生成的方法存根

    }

    public static void main(String[] args) throws Exception{
        new server();
    }
}

