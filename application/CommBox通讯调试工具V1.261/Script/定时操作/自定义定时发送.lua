--Lua脚本语言窗口
ClearOutput();   --清除输出窗口内容
Print("------- 自定义定时命令演示 ---------");   --打印提示信息到输出窗口
Print("可以自定义发送数据，可以加入校验数据");   --打印提示信息到输出窗口

buf={0x49,50,51,52,53};    --数组定义

SetButtonText(1,"定时发送")

function Button1Clicked()
   send();
end

function send()
  wav=GetExeDir().."\\wav\\notify.wav";
  PlayWave(wav);  --发送开始，语音提示
  for i=1,20 do
    s="send: "..IntToHex(i,2).." ";
    SendByte(i);    --发送帧号
    SendByte(5);    --发送数据长度
    cs=i;
    for j=1,5 do
      SendByte(buf[j]);  --发送数据内容
      s=s..IntToHex(buf[j],2).." ";
      cs=cs+buf[j];
    end
    cs =cs % 256;
    s=s..IntToHex(cs,2);
    SendByte(cs);  --发送校验和
    Print(s);
    Wait(500);  --等待 毫秒
  end;
  wav=GetExeDir().."\\wav\\ding.wav";
  PlayWave(wav);  --发送结束，语音提示

end;
send();