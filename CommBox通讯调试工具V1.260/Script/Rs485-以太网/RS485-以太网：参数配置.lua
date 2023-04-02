--Lua�ű����Դ���
 

ClearOutput();       --��������������
Print("------- ��̫����������RS485ת�������� ---------");   --��ӡ��ʾ��Ϣ���������
PrintToCommWin("");
PrintToCommWin("��̫����������RS485ת��������");

--------------------------------------------------------------------------------
AddLuaTreeNode(0,"��������" ,"");
AddLuaTreeNode(1,"1. �贮�ں�" ,"SetComNum");
AddLuaTreeNode(1,"2. �貨����" ,"SetComBaud");
AddLuaTreeNode(1,"3. �·�����" ,"DownComParam"); 

AddLuaTreeNode(0,"����IP����" ,"");
AddLuaTreeNode(2,"1. IP��ַ" ,"SetLocalIP");
AddLuaTreeNode(2,"2. ��������" ,"SetLocalMask");
AddLuaTreeNode(2,"3. ����" ,"SetLocalGateway");
AddLuaTreeNode(2,"4. MAC��ַ" ,"SetLocalMac");
AddLuaTreeNode(2,"5. ���ض˿�" ,"SetLocalPort");
AddLuaTreeNode(2,"5. �·�����" ,"DownloadLocalParam");

AddLuaTreeNode(0,"�ͻ���IP���˿ں�����" ,"");
AddLuaTreeNode(3,"1. �ͻ���IP��ַ" ,"SetRemoteIP");
AddLuaTreeNode(3,"2. �ͻ��˶˿�" ,"SetRemotePort");
AddLuaTreeNode(3,"5. �·�����" ,"DownloadRemoteParam");
 
Baud=9600;
ComNum=0;



function SetComNum()
   s=GetString("���ô��ں�(0~1):",IntToStr(ComNum));
   print(s);
   ComNum=StrToInt(s);
   SetLuaTreeNodeParam(0,1,ComNum);
end;
function SetComBaud()
   s=GetString("���ô��ںŲ�����:",IntToStr(Baud));
   print(s);
   Baud=StrToInt(s);
   SetLuaTreeNodeParam(0,2,Baud);
end;

function DownComParam()
   SetComParam();
end; 


function SetComParam()
   ClearSendBuf();
   SendByteToBuf(0xff);
   SendByteToBuf(0xfe);
   SendByteToBuf(ComNum);
   
   tmp0= bit_shr(Baud,24); tmp0= bit_and(tmp0,0xff);
   tmp1= bit_shr(Baud,16); tmp1= bit_and(tmp1,0xff);
   tmp2= bit_shr(Baud,8); tmp2= bit_and(tmp2,0xff);
   tmp3= bit_shr(Baud,0); tmp3= bit_and(tmp3,0xff);
           
   SendByteToBuf(tmp0);
   SendByteToBuf(tmp1);
   SendByteToBuf(tmp2);
   SendByteToBuf(tmp3);
   
   cs=tmp0+tmp1+tmp2+tmp3;
   cs= bit_and(cs,0xff);
   cs=256-cs;
   SendByteToBuf(cs);
   FlushSendBuf();
end;

LocalIP="192.168.1.110";
LocalMask="255.255.255.0";
LocalGateway="192.168.1.254";
LocalMac="11:22:33:44:55:66";
LocalPort="80";




function SetLocalIP()
   LocalIP=GetString("���ñ���IP��ַ",LocalIP);
   print(LocalIP); 
   SetLuaTreeNodeParam(1,1,LocalIP);  
end; 

function SetLocalMask()
   LocalMask=GetString("��������",LocalMask);
   print(LocalMask);
   SetLuaTreeNodeParam(1,2,LocalMask);   
end;

function SetLocalGateway()
   LocalGateway= GetString("��������",LocalGateway);
   print(LocalGateway);
   SetLuaTreeNodeParam(1,3,LocalGateway);
end;

function SetLocalMac()
   LocalMac= GetString("����Mac��ַ",LocalMac);
   print(LocalMac);
   SetLuaTreeNodeParam(1,4,LocalMac);
end;

function SetLocalPort()
   LocalPort=GetString("���ñ��ض˿�",LocalPort);
   print(LocalPort);
   SetLuaTreeNodeParam(1,5,LocalPort);
end;

RemoteIP="192.168.1.111";
RemotePort="80";




function SetRemoteIP()
   RemoteIP=GetString("���ÿͻ���IP��ַ",RemoteIP);
   print(RemoteIP);
   SetLuaTreeNodeParam(2,1,RemoteIP);   
end;

function SetRemotePort()
   RemotePort=GetString("���ÿͻ���IP�˿�",RemotePort);
   print(RemotePort);
   SetLuaTreeNodeParam(2,2,RemotePort);   
end;


SetLuaTreeNodeParam(0,1,ComNum);
SetLuaTreeNodeParam(0,2,Baud);
SetLuaTreeNodeParam(1,1,LocalIP);
SetLuaTreeNodeParam(1,2,LocalMask);
SetLuaTreeNodeParam(1,3,LocalGateway);
SetLuaTreeNodeParam(1,4,LocalMac);
SetLuaTreeNodeParam(1,5,LocalPort);
SetLuaTreeNodeParam(2,1,RemoteIP);
SetLuaTreeNodeParam(2,2,RemotePort);


function DownloadLocalParam()
   data={};
   mac={};
 
   data[1]=0xff;
   data[2]=0xfe;
   data[3]=0x11;    
  
   val=inet_addr(LocalIP);
   data[4]= bit_shr(val,24);
   data[5]= bit_shr(val,16);
   data[6]= bit_shr(val,8);   
   data[7]= bit_shr(val,0);   
   
   val=inet_addr(LocalMask);
   data[8]= bit_shr(val,24);
   data[9]= bit_shr(val,16);
   data[10]= bit_shr(val,8);
   data[11]= bit_shr(val,0);  
   
   val=inet_addr(LocalGateway);
   data[12]= bit_shr(val,24);
   data[13]= bit_shr(val,16);
   data[14]= bit_shr(val,8);
   data[15]= bit_shr(val,0);     
    
   data[16]= StrToInt("$"..SubString(LocalMac,1,2));
   data[17]= StrToInt("$"..SubString(LocalMac,4,2));
   data[18]= StrToInt("$"..SubString(LocalMac,7,2));
   data[19]= StrToInt("$"..SubString(LocalMac,10,2));
   data[20]= StrToInt("$"..SubString(LocalMac,13,2));
   data[21]= StrToInt("$"..SubString(LocalMac,16,2));
     
   lp = StrToInt(LocalPort);
   data[22]= bit_shr(lp,24);
   data[23]= bit_shr(lp,16);
   data[24]= bit_shr(lp,8);
   data[25]= bit_shr(lp,0);
   Print(LocalPort);
   Print(lp);
   Print(data[22]);      
   Print(data[23]);
   Print(data[24]);
   Print(data[25]);
      
   cs=0;
   for i=4,25 do
     cs=cs+bit_and(data[i],0xff);
   end;
   cs=256-cs;
   data[26]=cs;
   
   ClearSendBuf();
   for i=1,26 do
     SendByteToBuf(data[i]);
   end;
   FlushSendBuf();
end; 


function DownloadRemoteParam()
   data={};

   data[1]=0xff;
   data[2]=0xfe;
   data[3]=0x22;

   val=inet_addr(LocalIP);
   data[4]= bit_shr(val,24);
   data[5]= bit_shr(val,16);
   data[6]= bit_shr(val,8);
   data[7]= bit_shr(val,0);

   lp = StrToInt(LocalPort);
   data[8]= bit_shr(lp,24);
   data[9]= bit_shr(lp,16);
   data[10]= bit_shr(lp,8);
   data[11]= bit_shr(lp,0);
         
   cs=0;
   for i=4,11 do
     cs=cs+bit_and(data[i],0xff);
   end;
   cs=256-cs;
   data[12]=cs;

   ClearSendBuf();
   for i=1,12 do
     SendByteToBuf(data[i]);
   end;
   FlushSendBuf();
end;