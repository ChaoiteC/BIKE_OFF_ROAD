--Lua�ű����Դ���
ClearOutput();   --��������������
Print("------- �Զ��嶨ʱ������ʾ ---------");   --��ӡ��ʾ��Ϣ���������
Print("�����Զ��巢�����ݣ����Լ���У������");   --��ӡ��ʾ��Ϣ���������

buf={0x49,50,51,52,53};    --���鶨��

SetButtonText(1,"��ʱ����")

function Button1Clicked()
   send();
end

function send()
  wav=GetExeDir().."\\wav\\notify.wav";
  PlayWave(wav);  --���Ϳ�ʼ��������ʾ
  for i=1,20 do
    s="send: "..IntToHex(i,2).." ";
    SendByte(i);    --����֡��
    SendByte(5);    --�������ݳ���
    cs=i;
    for j=1,5 do
      SendByte(buf[j]);  --������������
      s=s..IntToHex(buf[j],2).." ";
      cs=cs+buf[j];
    end
    cs =cs % 256;
    s=s..IntToHex(cs,2);
    SendByte(cs);  --����У���
    Print(s);
    Wait(500);  --�ȴ� ����
  end;
  wav=GetExeDir().."\\wav\\ding.wav";
  PlayWave(wav);  --���ͽ�����������ʾ

end;
send();