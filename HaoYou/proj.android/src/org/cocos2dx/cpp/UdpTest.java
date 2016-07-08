package org.cocos2dx.cpp;

import java.io.*;
import java.net.*;

public class UdpTest {			

	public static void send(int i,int phone)
	{

 		try {
        String ip;
        if(phone==1)ip="192.168.191.3";
        else ip="192.168.191.2";

           //首先创建一个DatagramSocket对象

           DatagramSocket socket = new DatagramSocket(4567);

           //创建一个InetAddree

		   InetAddress serverAddress = InetAddress.getByName(ip);

          Integer atk = i;

           String str = atk.toString();  //这是要传输的数据

           byte data [] = str.getBytes();  //把传输内容分解成字节

           DatagramPacket packet = new

		   DatagramPacket(data,data.length,serverAddress,4567);

           //调用socket对象的send方法，发送数据

           socket.send(packet);

           socket.close();

       } catch (Exception e) {

           // TODO Auto-generated catch block

           e.printStackTrace();

       }
   
	}

	public static int get()
	{
    try {

		    DatagramSocket socket = new DatagramSocket(4567);

        byte data [] = new byte[1024];

        DatagramPacket packet = 

		    new DatagramPacket(data,data.length);

      	socket.receive(packet);

        String result = new 

		    String(packet.getData(),packet.getOffset(),

		    packet.getLength());

        socket.close();
           
        int i = Integer.parseInt(result);

        return i;

       } catch (Exception e) {

           // TODO Auto-generated catch block

           e.printStackTrace();

       }
      return 0;
	}
}