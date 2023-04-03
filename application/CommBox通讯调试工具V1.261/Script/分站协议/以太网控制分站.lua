--Lua�ű����Դ���
ClearOutput();       --��������������
Print("------- ��̫�����Ʒ�վ���� ---------");   --��ӡ��ʾ��Ϣ���������
PrintToCommWin("");
PrintToCommWin("------- ��̫�����Ʒ�վ���� ---------");

xhjmode={
"00��ϵͳͣ����ѭ����",
"01��ͣ������ֺϣ�",
"02��׼������ֺϣ�",
"03��ѯ�ʣ���ƽ��棩",
"04������ǰ��������������",
"05���������ˣ�����������",
"06���������У�����������",
"07���������У�����������",
"08������ǰ��������������",
"09��������ˣ�����������",
"10���������У�����������",
"11���������У�����������",
"12��ǰ���������ƣ�",
"13�����ˣ������ƣ�",
"14�����У������ƣ�",
"15�����У������ƣ�"
}
--------------------------------------------------------------------------------
AddLuaTreeNode(0,"��վ����"        ,"");
AddLuaTreeNode(1,"1. ���Ϳհ�"     ,"SendEmptyPacket");
AddLuaTreeNode(1,"2. ѭ�����Ϳհ�" ,"RecycleSend");
AddLuaTreeNode(1,"3. վ������"     ,"ConfigStation"); 
AddLuaTreeNode(1,"4. ��ص�ѹ"     ,"QueryBatteryVoltage");
AddLuaTreeNode(1,"5. ״̬��ѯ"     ,"QueryStationState");
AddLuaTreeNode(1,"6. վ������"     ,"StationBeep");
AddLuaPickTreeNode(1,"6. ��ǰ���" ,"SetPoint","1","1","2","3","4");


AddLuaTreeNode(0,"�źŻ�����"         ,"");
AddLuaPickTreeNode(2,"1. �źŻ�ģʽ"  ,"InputSignallampMode",xhjmode[2],
                     xhjmode[1],xhjmode[2],xhjmode[3],xhjmode[4],
                     xhjmode[5],xhjmode[6],xhjmode[7],xhjmode[8],
                     xhjmode[9],xhjmode[10],xhjmode[11],xhjmode[12],
                     xhjmode[13],xhjmode[14],xhjmode[15],xhjmode[16]);
AddLuaTreeNode(2,"2. �źŻ�����"      ,"ContrlSignallampMode");
AddLuaTreeNode(2,"3. �źŻ�--ͣ��"    ,"ContrlSignallampMode_Red");
AddLuaTreeNode(2,"4. �źŻ�--����ǰ��" ,"ContrlSignallampMode_BeepGo");
AddLuaTreeNode(2,"5. �źŻ�--ǰ��"    ,"ContrlSignallampMode_Go");
AddLuaTreeNode(2,"6. ��ѯ�źŻ�ģʽ"  ,"QuerySignallampMode");

AddLuaTreeNode(0,"ת�޻�����"        ,"");
AddLuaTreeNode(3,"1. ת�޻�-��λ"    ,"ContrlSwitchModeDW");
AddLuaTreeNode(3,"2. ת�޻�-��λ"    ,"ContrlSwitchModeFW");
AddLuaTreeNode(3,"3. ת�޻���ѯ"     ,"QuerySwitchMode");

AddLuaTreeNode(0,"��Ѷ������"        ,"");
AddLuaTreeNode(4,"1. ��Ϣ����"       ,"ReceiverFilt");
AddLuaTreeNode(4,"2. ��Ϣ������"     ,"ReceiverNotFilt");
AddLuaTreeNode(4,"3. ״̬��ѯ"       ,"QueryReceiverMode");
AddLuaTreeNode(4,"4. ����"           ,"ReceiverOpen");
AddLuaTreeNode(4,"5. �ر�"           ,"ReceiverClose");

AddLuaTreeNode(0,"����������"        ,"");
AddLuaTreeNode(5,"1. ����������"   ,"AxlerPulsSet");
AddLuaTreeNode(5,"2. ����"           ,"AxlerOpen");
AddLuaTreeNode(5,"3. �ر�"           ,"AxlerClose");
AddLuaTreeNode(5,"4. ״̬"           ,"QueryAxlerMode");


sn=0x00;
RemoteIP="192.168.1.200";
RemotePort="8000";  
DevPoint=1; --��� 
slMode=0x01;--�źŻ�ģʽ
 
SA=16;
DA=200;

function TreeValueEdited()
   DevPoint=StrToInt(GetTreeNodeValue(0,7));
   s=GetTreeNodeValue(1,1); PrintToCommWin(s); 
   s=SubString(s,1,2); slMode =StrToInt(s);
   
end;

SetLuaTreeNodeParam(0,1,"FF FF C8 02 86 00 B0");
SetLuaTreeNodeParam(0,2,"�ѹر�");
--SetLuaTreeNodeParam(0,3,"δʵ��");
SetLuaTreeNodeParam(0,4,"FF FF C8 06 86 01 03 00 80 01 27");
SetLuaTreeNodeParam(0,6,"3��");
SetLuaTreeNodeParam(0,7,DevPoint);
SetLuaTreeNodeParam(1,1,slMode);


local reSend=0;
function Timer100ms()
    if reSend==1 then
       --PrintToCommWin("send...");
       SendEmptyPacket();
    end;
end;
function RecycleSend()
    if reSend==0 then
       reSend=1;
       SetLuaTreeNodeParam(0,2,"�ѿ���");
    else
       reSend=0;
       SetLuaTreeNodeParam(0,2,"�ѹر�");       
    end;
    
end; 

function SendPacket(dat)
   local cmd={};
   if dat==nil then  len=0; else   len=#dat; end;
   
   cmd[1]=DA;  --DA
   cmd[2]=0x02+len; --IL
   cmd[3]=SA;   --SA
   cmd[4]=sn; --LINK
   cs=0;
   for i=1,4 do  cs=cs+cmd[i];  end;
   for i=1,len do  cs=cs+dat[i];  end;
   cs=cs % 256;  cs=256 - cs; 
   ClearSendBuf();
   SendByteToBuf(0xff); SendByteToBuf(0xff);
   for i=1,4 do    SendByteToBuf(cmd[i]); end;
   for i=1,len do  SendByteToBuf(dat[i]); end; 
   SendByteToBuf(cs);
   FlushSendBuf();   
   sn=sn+1;
end;

function SendEmptyPacket()
   SendPacket(nil); 
end;

function QueryBatteryVoltage()  --��ص�ѹ��ѯ 
  local  cmd={};
   cmd[1]=0x03; --PL  
   cmd[2]=0x00; --���
   cmd[3]=0x80; --DATA:
   cmd[4]=0x01; --DATA:��ص�ѹ 
   SendPacket(cmd); 
end;
function QueryStationState()   --��վ״̬��ѯ 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=0x00; --���
   cmd[3]=0x80; --DATA:
   cmd[4]=0x02; --DATA:��վ״̬ 
   SendPacket(cmd);
end;
function ConfigStation()   --��վ���� 
  local  cmd={0x1B,0x00,0x80,0x00 ,0x1A,0x00,0x3A,0x4A ,0x00,0x00,0x00,0x00 ,0x1C,0x2C,0x00,0x00 ,0x19,0x00,0x39,0x00 ,0x18,0x00,0x00,0x00 ,0x00,0x00,0x00,0x00};
   --cmd[1]=0x03; --PL
   --cmd[2]=0x00; --���
   --cmd[3]=0x80; --DATA:
   --cmd[4]=0x02; --DATA:��վ״̬
   SendPacket(cmd);
end;



function StationBeep()         --վ������ 
  local  cmd={};
   cmd[1]=0x04; --PL  
   cmd[2]=0x00; --���
   cmd[3]=0x80; --DATA:
   cmd[4]=0x04; --DATA:   
   cmd[5]=0x03; --DATA:   
   SendPacket(cmd);
end;
--------------------------------------------------------------------------------
function InputSignallampMode()   --�źŻ�����
   s=GetString("�ź�ģʽ(0~15):",slMode); 
   slMode=StrToInt(s);
   SetLuaTreeNodeParam(1,1,slMode);
   ContrlSignallampMode();
end; 

function SetPoint()   --������� 
   s=GetString("�豸���(1~4):",DevPoint);
   DevPoint=StrToInt(s);
   SetLuaTreeNodeParam(0,7,DevPoint);
 
end;

function ContrlSignallampMode()   --�źŻ����� 
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x81; --DATA:
   cmd[4]=0x00; --DATA:
   cmd[5]=slMode;  --mode:
   SendPacket(cmd);
end;
 
function  ContrlSignallampMode_Red()    -- �źŻ�����-ͣ��
   slMode=0x01;
   ContrlSignallampMode(); 
end;
function  ContrlSignallampMode_BeepGo() --�źŻ�����-����ǰ��
   slMode=0x08;
   ContrlSignallampMode();
end;
function  ContrlSignallampMode_Go()     -- �źŻ�����-ǰ��
   slMode=12;
   ContrlSignallampMode();
end;

function QuerySignallampMode()   --��ѯ�źŻ�ģʽ 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x81;   --DATA:
   cmd[4]=0x01;   --DATA: 
   SendPacket(cmd);
end;
--------------------------------------------------------------------------------
function ContrlSwitchModeDW()   --ת�޻�����  ����λ 
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x82;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x04;   --DATA: ��λ 
   SendPacket(cmd);
end;
function ContrlSwitchModeFW()   --ת�޻�����  ����λ
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x82;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x08;   --DATA: ��λ
   SendPacket(cmd);
end;

function QuerySwitchMode()   --ת�޻���ѯ
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x82;   --DATA:
   cmd[4]=0x01;   --DATA:
   SendPacket(cmd);
   print("ת�޻���ѯ");
end;
-------------------------------------------------------------------------------- 

function ReceiverFilt()   --��Ѷ����Ϣ����
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x01;   --DATA:   
   SendPacket(cmd);    
end;
function ReceiverNotFilt()   --��Ѷ����Ϣ������
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x00;   --DATA:
   SendPacket(cmd);
end;
function QueryReceiverMode()   --��Ѷ��״̬��ѯ 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x01;   --DATA:
   SendPacket(cmd);
end;

function ReceiverOpen()   --��Ѷ������ 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x02;   --DATA:
   SendPacket(cmd);
end;

function ReceiverClose()   --��Ѷ���ر�
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x03;   --DATA:
   SendPacket(cmd);
end;
-------------------------------------------------------------------------------- 

function AxlerPulsSet()   --���������������� 
  local  cmd={};
   cmd[1]=0x0B; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x03;   --DATA:
   cmd[6]=0x03;   --DATA:   
   cmd[7]=0x03;   --DATA:   
   cmd[8]=0x03;   --DATA:   
   cmd[9]=0x03;   --DATA:   
   cmd[10]=0x03;   --DATA: 
   cmd[11]=0x03;   --DATA:
   cmd[12]=0x03;   --DATA:     
   SendPacket(cmd);
end;

function AxlerOpen()   --����������
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x01;   --DATA:
   cmd[5]=0x03;   --DATA:    
   SendPacket(cmd);
end;
function AxlerClose()   --�������ر� 
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x02;   --DATA:
   cmd[5]=0x03;   --DATA:
   SendPacket(cmd);
end;

function QueryAxlerMode()   --��������ѯ
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --���
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x03;   --DATA:
 
   SendPacket(cmd);
end;

---------------------------------���յ����ݽ��еĴ���--------------------------------------------------------------------------------
function ReceivedByte(dat) --�������н��յ�����ʱ�����Զ����ô˺���
   --PutBufData(dat);
   --Print("����:"..IntToHex(dat,2));
   Print(IntToHex(dat,2));   
   --EncodeDat();
   return 1;
end