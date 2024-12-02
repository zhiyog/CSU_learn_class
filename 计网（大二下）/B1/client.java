package chat;

import javax.swing.*;
import com.sun.org.apache.bcel.internal.generic.NEW;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

public class client extends JFrame implements Runnable,ActionListener {
    //north
    private JMenuBar bar = new JMenuBar();
    private JMenu menu = new JMenu("关于");
    private JMenuItem about = new JMenuItem("关于本软件");
    private JMenuItem exit = new JMenuItem("退出");
    JPanel north = new JPanel();
    //west
    JPanel west = new JPanel();
    DefaultListModel<String> dl = new DefaultListModel<String>();//用来修改JList
    private JList<String> userList = new JList<String>(dl);//用来展示和选择
    JScrollPane listPane = new JScrollPane(userList);
    //center
    JPanel center = new JPanel();
    JTextArea jta = new JTextArea(10,20);
    JScrollPane js = new JScrollPane(jta);
    JPanel operPane = new JPanel();//发送消息的操作面板
    JLabel input = new JLabel("请输入:");
    JTextField jtf = new JTextField(24);

    JButton jButton = new JButton("发消息");

    private JButton jbt = new JButton("发送消息");
    private JButton jbt1 = new JButton("私发消息");
    private BufferedReader br = null;
    private PrintStream ps = null;
    private String nickName = null;

    //私聊面板
    JTextArea jTextArea = new JTextArea(11,45);
    JScrollPane js1 = new JScrollPane(jTextArea);
    JTextField jTextField = new JTextField(25);
    String suser = new String();

    double MAIN_FRAME_LOC_X;//父窗口x坐标
    double MAIN_FRAME_LOC_Y;//父窗口y坐标

    boolean FirstSecret = true;//是否第一次私聊
    String sender=null;//私聊发送者的名字
    String receiver=null;//私聊接收者的名字

    public client() throws Exception{
        //north 菜单栏
        bar.add(menu);
        menu.add(about);
        menu.add(exit);
        about.addActionListener(this);
        exit.addActionListener(this);
        BorderLayout bl = new BorderLayout();
        north.setLayout(bl);
        north.add(bar,BorderLayout.NORTH);
        add(north,BorderLayout.NORTH);

        //east 好友列表
        Dimension dim = new Dimension(100,150);
        west.setPreferredSize(dim);//在使用了布局管理器后用setPreferredSize来设置窗口大小
        //Dimension dim2 = new Dimension(100,150);
        //listPane.setPreferredSize(dim2);
        BorderLayout bl2 = new BorderLayout();
        west.setLayout(bl2);
        west.add(listPane,BorderLayout.CENTER);//显示好友列表
        add(west,BorderLayout.EAST);
        userList.setFont(new Font("隶书",Font.BOLD,18));

        //center 聊天消息框  发送消息操作面板
        jta.setEditable(false);//消息显示框是不能编辑的
        jTextArea.setEditable(false);

        BorderLayout bl3 = new BorderLayout();
        center.setLayout(bl3);
        FlowLayout fl = new FlowLayout(FlowLayout.LEFT);
        operPane.setLayout(fl);
        operPane.add(input);
        operPane.add(jtf);
        operPane.add(jbt);
        operPane.add(jbt1);
        center.add(js,BorderLayout.CENTER);//js是消息展示框JScrollPane
        center.add(operPane,BorderLayout.SOUTH);
        add(center,BorderLayout.CENTER);

        js.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);//需要时才显示滚动条

        //鼠标事件，点击
        jbt.addActionListener(this);
        jbt1.addActionListener(this);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        //this.setAlwaysOnTop(true);

        nickName = JOptionPane.showInputDialog("用户名：");
        this.setTitle(nickName + "的聊天室");
        this.setSize(700,400);
        this.setVisible(true);

        Socket s = new Socket("127.0.0.1", 9999);
        br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        ps = new PrintStream(s.getOutputStream());
        new Thread(this).start();//run()
        ps.println("LOGIN#" + nickName);//发送登录信息，消息格式：LOGIN#nickName

        jtf.setFocusable(true);//设置焦点

        //键盘事件，实现当输完要发送的内容后，直接按回车键，实现发送
        //监听键盘相应的控件必须是获得焦点（focus）的情况下才能起作用
        jtf.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_ENTER) {
                    ps.println("MSG#" + nickName + "#" +  jtf.getText());//发送消息的格式：MSG#nickName#message
                    //发送完后，是输入框中内容为空
                    jtf.setText("");
                }
            }
        });

        //私聊消息框按回车发送消息
        jTextField.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_ENTER) {
                    handleSS();
                }
            }
        });

        //监听系统关闭事件，退出时给服务器端发出指定消息
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                ps.println("OFFLINE#" + nickName);//发送下线信息，消息格式：OFFLINE#nickName
            }
        });

        this.addComponentListener(new ComponentAdapter() {//监听父窗口大小的改变
            public void componentMoved(ComponentEvent e) {
                Component comp = e.getComponent();
                MAIN_FRAME_LOC_X = comp.getX();
                MAIN_FRAME_LOC_Y = comp.getY();
            }
        });
    }

    public void run(){//客户端与服务器端发消息的线程
        while (true){
            try{
                String msg = br.readLine();//读取服务器是否发送了消息给该客户端
                String[] strs = msg.split("#");
                //判断是否为服务器发来的登陆信息
                if(strs[0].equals("LOGIN")){
                    if(!strs[1].equals(nickName)){//不是本人的上线消息就显示，本人的不显示
                        jta.append(strs[1] + "上线啦！\n");
                        dl.addElement(strs[1]);//DefaultListModel来更改JList的内容
                        userList.repaint();
                    }
                }else if(strs[0].equals("MSG")){//接到服务器发送消息的信息
                    if(!strs[1].equals(nickName)){//别人说的
                        jta.append(strs[1] + "说：" + strs[2] + "\n");
                    }else{
                        jta.append("我说：" + strs[2] + "\n");
                    }
                }else if(strs[0].equals("USERS")){//USER消息，为新建立的客户端更新好友列表
                    dl.addElement(strs[1]);
                    userList.repaint();
                } else if(strs[0].equals("ALL")){
                    jta.append("系统消息：" + strs[1] + "\n");
                }else if(strs[0].equals("OFFLINE")){
                    if(strs[1].equals(nickName)) {//如果是自己下线的消息，说明被服务器端踢出聊天室，强制下线
                        javax.swing.JOptionPane.showMessageDialog(this, "您已被系统请出聊天室！");
                        System.exit(0);
                    }
                    jta.append(strs[1] + "下线啦！\n");
                    dl.removeElement(strs[1]);
                    userList.repaint();
                }else if((strs[2].equals(nickName) || strs[1].equals(nickName)) && strs[0].equals("SMSG")){
                    if(!strs[1].equals(nickName)){
                        jTextArea.append(strs[1] + "说：" + strs[3] + "\n");
                        jta.append("系统提示：" + strs[1] + "私信了你" + "\n");
                    }else{
                        jTextArea.append("我说：" + strs[3] + "\n");
                    }
                }else if((strs[2].equals(nickName) || strs[1].equals(nickName)) && strs[0].equals("FSMSG"))
                {
                    sender = strs[1];
                    receiver = strs[2];
                    //接收方第一次收到私聊消息，自动弹出私聊窗口
                    if(!strs[1].equals(nickName)) {
                        FirstSecret = false;
                        jTextArea.append(strs[1] + "说：" + strs[3] + "\n");
                        jta.append("系统提示：" + strs[1] + "私信了你" + "\n");
                        handleSec(strs[1]);
                    }
                    else {
                        jTextArea.append("我说：" + strs[3] + "\n");
                    }
                }
            }catch (Exception ex){//如果服务器端出现问题，则客户端强制下线
                javax.swing.JOptionPane.showMessageDialog(this, "您已被系统请出聊天室！");
                System.exit(0);
            }
        }
    }


    @Override
    public void actionPerformed(ActionEvent e) {//鼠标点击事件
        String label = e.getActionCommand();
        if(label.equals("发送消息")){//群发
            handleSend();
        }else if(label.equals("私发消息") && !userList.isSelectionEmpty()){//未点击用户不执行
            suser = userList.getSelectedValuesList().get(0);//获得被选择的用户
            handleSec(suser);//创建私聊窗口
            sender = nickName;
            receiver = suser;
        }else if(label.equals("发消息")){
            handleSS();//私发消息
        }else if(label.equals("关于本软件")){
            JOptionPane.showMessageDialog(this, "1.可以在聊天框中进行群聊\n\n2.可以点击选择用户进行私聊");
        }else if(label.equals("退出")){
            JOptionPane.showMessageDialog(this, "您已成功退出！");
            ps.println("OFFLINE#" + nickName);
            System.exit(0);
        } else{
            System.out.println("不识别的事件");
        }
    }

    public void handleSS(){//在私聊窗口中发消息
        String name=sender;
        if(sender.equals(nickName)) {
            name = receiver;
        }
        if(FirstSecret) {
            ps.println("FSMSG#" + nickName + "#" + name + "#" + jTextField.getText());
            jTextField.setText("");
            FirstSecret = false;
        }
        else {
            ps.println("SMSG#" + nickName + "#" + name + "#" + jTextField.getText());
            jTextField.setText("");
        }
    }

    public void handleSend(){//群发消息
        //发送信息时标识一下来源
        ps.println("MSG#" + nickName + "#" +  jtf.getText());
        //发送完后，是输入框中内容为空
        jtf.setText("");
    }

    public void handleSec(String name){ //建立私聊窗口
        JFrame jFrame = new JFrame();//新建了一个窗口
        JPanel JPL = new JPanel();
        JPanel JPL2 = new JPanel();
        FlowLayout f2 = new FlowLayout(FlowLayout.LEFT);
        JPL.setLayout(f2);
        JPL.add(jTextField);
        JPL.add(jButton);
        JPL2.add(js1,BorderLayout.CENTER);
        JPL2.add(JPL,BorderLayout.SOUTH);
        jFrame.add(JPL2);

        jButton.addActionListener(this);
        jTextArea.setFont(new Font("宋体", Font.PLAIN,15));
        jFrame.setSize(400,310);
        jFrame.setLocation((int)MAIN_FRAME_LOC_X+20,(int)MAIN_FRAME_LOC_Y+20);//将私聊窗口设置总是在父窗口的中间弹出
        jFrame.setTitle("与" + name + "私聊中");
        jFrame.setVisible(true);

        jTextField.setFocusable(true);//设置焦点

        jFrame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                jTextArea.setText("");
                FirstSecret = true;
            }
        });
    }//私聊窗口

    public static void main(String[] args)throws Exception{
        new client();
    }
}

