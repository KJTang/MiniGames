package org.cocos2dx.cpp;

public class SocketTest
{

	public static void start_server(){
        SocketServer server = new SocketServer(12345);
        server.beginListen();
     }
	public static void connect_server(int i){

          String ip = (i & 0xFF ) + "." +       
          ((i >> 8 ) & 0xFF) + "." +       
          ((i >> 16 ) & 0xFF) + "." +       
          ( i >> 24 & 0xFF) ;

          SocketClient client = new SocketClient("192.168.191.3",12345);
          System.out.println(client.sendMsg("nimei1"));
          client.closeSocket();
          client = new SocketClient("192.168.191.3",12345);
          System.out.println(client.sendMsg("end"));
          client.closeSocket();
	}
}