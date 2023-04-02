--Lua脚本语言窗口
ClearOutput();       --清除输出窗口内容
Print("------- 以太网控制分站测试 ---------");   --打印提示信息到输出窗口
PrintToCommWin("");
PrintToCommWin("------- 以太网控制分站测试 ---------");

xhjmode={
"00：系统停（黄循环）",
"01：停车（红分合）",
"02：准备（红分合）",
"03：询问（红黄交替）",
"04：谨慎前进（黄上移鸣）",
"05：谨慎后退（黄下移鸣）",
"06：谨慎左行（黄左移鸣）",
"07：谨慎右行（黄右移鸣）",
"08：响铃前进（绿上移鸣）",
"09：响铃后退（绿下移鸣）",
"10：响铃左行（绿左移鸣）",
"11：响铃右行（绿右移鸣）",
"12：前进（绿上移）",
"13：后退（绿下移）",
"14：左行（绿左移）",
"15：右行（绿右移）"
}
--------------------------------------------------------------------------------
AddLuaTreeNode(0,"分站命令"        ,"");
AddLuaTreeNode(1,"1. 发送空包"     ,"SendEmptyPacket");
AddLuaTreeNode(1,"2. 循环发送空包" ,"RecycleSend");
AddLuaTreeNode(1,"3. 站点配置"     ,"ConfigStation"); 
AddLuaTreeNode(1,"4. 电池电压"     ,"QueryBatteryVoltage");
AddLuaTreeNode(1,"5. 状态查询"     ,"QueryStationState");
AddLuaTreeNode(1,"6. 站点鸣响"     ,"StationBeep");
AddLuaPickTreeNode(1,"6. 当前点号" ,"SetPoint","1","1","2","3","4");


AddLuaTreeNode(0,"信号机命令"         ,"");
AddLuaPickTreeNode(2,"1. 信号机模式"  ,"InputSignallampMode",xhjmode[2],
                     xhjmode[1],xhjmode[2],xhjmode[3],xhjmode[4],
                     xhjmode[5],xhjmode[6],xhjmode[7],xhjmode[8],
                     xhjmode[9],xhjmode[10],xhjmode[11],xhjmode[12],
                     xhjmode[13],xhjmode[14],xhjmode[15],xhjmode[16]);
AddLuaTreeNode(2,"2. 信号机控制"      ,"ContrlSignallampMode");
AddLuaTreeNode(2,"3. 信号机--停车"    ,"ContrlSignallampMode_Red");
AddLuaTreeNode(2,"4. 信号机--响铃前进" ,"ContrlSignallampMode_BeepGo");
AddLuaTreeNode(2,"5. 信号机--前进"    ,"ContrlSignallampMode_Go");
AddLuaTreeNode(2,"6. 查询信号机模式"  ,"QuerySignallampMode");

AddLuaTreeNode(0,"转辙机命令"        ,"");
AddLuaTreeNode(3,"1. 转辙机-定位"    ,"ContrlSwitchModeDW");
AddLuaTreeNode(3,"2. 转辙机-反位"    ,"ContrlSwitchModeFW");
AddLuaTreeNode(3,"3. 转辙机查询"     ,"QuerySwitchMode");

AddLuaTreeNode(0,"收讯机命令"        ,"");
AddLuaTreeNode(4,"1. 信息过滤"       ,"ReceiverFilt");
AddLuaTreeNode(4,"2. 信息不过滤"     ,"ReceiverNotFilt");
AddLuaTreeNode(4,"3. 状态查询"       ,"QueryReceiverMode");
AddLuaTreeNode(4,"4. 开启"           ,"ReceiverOpen");
AddLuaTreeNode(4,"5. 关闭"           ,"ReceiverClose");

AddLuaTreeNode(0,"计轴器命令"        ,"");
AddLuaTreeNode(5,"1. 脉宽常数配置"   ,"AxlerPulsSet");
AddLuaTreeNode(5,"2. 开启"           ,"AxlerOpen");
AddLuaTreeNode(5,"3. 关闭"           ,"AxlerClose");
AddLuaTreeNode(5,"4. 状态"           ,"QueryAxlerMode");


sn=0x00;
RemoteIP="192.168.1.200";
RemotePort="8000";  
DevPoint=1; --点号 
slMode=0x01;--信号机模式
 
SA=16;
DA=200;

function TreeValueEdited()
   DevPoint=StrToInt(GetTreeNodeValue(0,7));
   s=GetTreeNodeValue(1,1); PrintToCommWin(s); 
   s=SubString(s,1,2); slMode =StrToInt(s);
   
end;

SetLuaTreeNodeParam(0,1,"FF FF C8 02 86 00 B0");
SetLuaTreeNodeParam(0,2,"已关闭");
--SetLuaTreeNodeParam(0,3,"未实现");
SetLuaTreeNodeParam(0,4,"FF FF C8 06 86 01 03 00 80 01 27");
SetLuaTreeNodeParam(0,6,"3次");
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
       SetLuaTreeNodeParam(0,2,"已开启");
    else
       reSend=0;
       SetLuaTreeNodeParam(0,2,"已关闭");       
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

function QueryBatteryVoltage()  --电池电压查询 
  local  cmd={};
   cmd[1]=0x03; --PL  
   cmd[2]=0x00; --点号
   cmd[3]=0x80; --DATA:
   cmd[4]=0x01; --DATA:电池电压 
   SendPacket(cmd); 
end;
function QueryStationState()   --分站状态查询 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=0x00; --点号
   cmd[3]=0x80; --DATA:
   cmd[4]=0x02; --DATA:分站状态 
   SendPacket(cmd);
end;
function ConfigStation()   --分站配置 
  local  cmd={0x1B,0x00,0x80,0x00 ,0x1A,0x00,0x3A,0x4A ,0x00,0x00,0x00,0x00 ,0x1C,0x2C,0x00,0x00 ,0x19,0x00,0x39,0x00 ,0x18,0x00,0x00,0x00 ,0x00,0x00,0x00,0x00};
   --cmd[1]=0x03; --PL
   --cmd[2]=0x00; --点号
   --cmd[3]=0x80; --DATA:
   --cmd[4]=0x02; --DATA:分站状态
   SendPacket(cmd);
end;



function StationBeep()         --站点鸣响 
  local  cmd={};
   cmd[1]=0x04; --PL  
   cmd[2]=0x00; --点号
   cmd[3]=0x80; --DATA:
   cmd[4]=0x04; --DATA:   
   cmd[5]=0x03; --DATA:   
   SendPacket(cmd);
end;
--------------------------------------------------------------------------------
function InputSignallampMode()   --信号机控制
   s=GetString("信号模式(0~15):",slMode); 
   slMode=StrToInt(s);
   SetLuaTreeNodeParam(1,1,slMode);
   ContrlSignallampMode();
end; 

function SetPoint()   --点号设置 
   s=GetString("设备点号(1~4):",DevPoint);
   DevPoint=StrToInt(s);
   SetLuaTreeNodeParam(0,7,DevPoint);
 
end;

function ContrlSignallampMode()   --信号机控制 
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x81; --DATA:
   cmd[4]=0x00; --DATA:
   cmd[5]=slMode;  --mode:
   SendPacket(cmd);
end;
 
function  ContrlSignallampMode_Red()    -- 信号机控制-停车
   slMode=0x01;
   ContrlSignallampMode(); 
end;
function  ContrlSignallampMode_BeepGo() --信号机控制-响铃前进
   slMode=0x08;
   ContrlSignallampMode();
end;
function  ContrlSignallampMode_Go()     -- 信号机控制-前进
   slMode=12;
   ContrlSignallampMode();
end;

function QuerySignallampMode()   --查询信号机模式 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x81;   --DATA:
   cmd[4]=0x01;   --DATA: 
   SendPacket(cmd);
end;
--------------------------------------------------------------------------------
function ContrlSwitchModeDW()   --转辙机控制  ：定位 
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x82;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x04;   --DATA: 定位 
   SendPacket(cmd);
end;
function ContrlSwitchModeFW()   --转辙机控制  ：反位
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x82;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x08;   --DATA: 定位
   SendPacket(cmd);
end;

function QuerySwitchMode()   --转辙机查询
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x82;   --DATA:
   cmd[4]=0x01;   --DATA:
   SendPacket(cmd);
   print("转辙机查询");
end;
-------------------------------------------------------------------------------- 

function ReceiverFilt()   --收讯机信息过滤
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x01;   --DATA:   
   SendPacket(cmd);    
end;
function ReceiverNotFilt()   --收讯机信息不过滤
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x00;   --DATA:
   cmd[5]=0x00;   --DATA:
   SendPacket(cmd);
end;
function QueryReceiverMode()   --收讯机状态查询 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x01;   --DATA:
   SendPacket(cmd);
end;

function ReceiverOpen()   --收讯机开启 
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x02;   --DATA:
   SendPacket(cmd);
end;

function ReceiverClose()   --收讯机关闭
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x83;   --DATA:
   cmd[4]=0x03;   --DATA:
   SendPacket(cmd);
end;
-------------------------------------------------------------------------------- 

function AxlerPulsSet()   --计轴器脉宽常数配置 
  local  cmd={};
   cmd[1]=0x0B; --PL
   cmd[2]=DevPoint*0x10; --点号
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

function AxlerOpen()   --计轴器开启
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x01;   --DATA:
   cmd[5]=0x03;   --DATA:    
   SendPacket(cmd);
end;
function AxlerClose()   --计轴器关闭 
  local  cmd={};
   cmd[1]=0x04; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x02;   --DATA:
   cmd[5]=0x03;   --DATA:
   SendPacket(cmd);
end;

function QueryAxlerMode()   --计轴器查询
  local  cmd={};
   cmd[1]=0x03; --PL
   cmd[2]=DevPoint*0x10; --点号
   cmd[3]=0x84;   --DATA:
   cmd[4]=0x03;   --DATA:
 
   SendPacket(cmd);
end;

---------------------------------接收到数据进行的处理--------------------------------------------------------------------------------
function ReceivedByte(dat) --当串口中接收到数据时，会自动调用此函数
   --PutBufData(dat);
   --Print("接收:"..IntToHex(dat,2));
   Print(IntToHex(dat,2));   
   --EncodeDat();
   return 1;
end