
ClearOutput();   --清除输出窗口内容        align = "alClient", 

pb      = VCL.Panel(nil,"PB");   pb._       ={width=400,height=100, caption = "",color=VCL.clBtnFace}
pb.txt1 = VCL.Label(pb,"txt1");  pb.txt1._  ={left=10, top=20, autosize=false, width=60,caption="文件名称：",}
pb.edit1 = VCL.Edit(pb,"edit1"); pb.edit1._ ={left=75, top=18, width=200,text="请输入文件名..."}
pb.btn1  = VCL.Button(pb,"BTN1");pb.btn1._  ={left=280,top=16, caption="...", width=50,onclick="OpenFile"}
pb.btn2  = VCL.Button(pb,"BTN2");pb.btn2._  ={left=50, top=60, width=200,caption="发送", onclick="btnClicked"}

ShowVclForm(pb.Height+8);
--ShowOutputForm();
CloseCodeForm();

function OpenFile()
   pb.edit1.text=GetFileName();
end;

function btnClicked(sender)
    print("发送文件名称："..pb.edit1.text); 
    local f = io.open(pb.edit1.text, "rb")     
    if f==nil then print("file open error");return;end;

    local size = f:seek("end");   
    print("file size:"..size);
    f:seek("set")  
    local s; 
    s = f:read(size);
    if not s then f:close(); return; end
    
    -------------- 去掉空格 ------------------- 
    s1="";
    for i=1 ,#s do    
       c =string.byte(s, i);
       if c~=0x20 then  --space
          if c~=0x0d then   --return
              if c~=0x0a then    --nextline   
                  s1=s1..string.char(c);
              end; 
          end;    
       end;
    end;
    --print("trimed str:"..s1); 
    
    -------------- 发送 ------------------- 
    print("send start...");         
    for i=1,(#s1 /2) do
          s=string.sub(s1,i*2-1,i*2);               
          --print(StrToInt('$'..s));
          SendByte(StrToInt('$'..s));
          --print(s);
          if i%50==0 then print("."); Wait(1);end;
    end;       
    f:close();
    print("send end");
end;