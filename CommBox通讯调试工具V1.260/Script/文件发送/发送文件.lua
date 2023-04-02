ClearOutput();   --清除输出窗口内容

pb      = VCL.Panel(nil,"PB");   pb._      ={align = "alClient", height=40, caption = ""}
pb.txt1 = VCL.Label(pb,"txt1");  pb.txt1._ ={left=10, top=12, autosize=false, width=60,caption="文件名称：",}
pb.edit1 = VCL.Edit(pb,"edit1"); pb.edit1._ ={left=75, top=10, width=200,text="请输入文件名..."}
pb.btn1  = VCL.Button(pb,"BTN1");pb.btn1._  ={left=280, top=8, caption="...", width=50,onclick="OpenFile"}
pb.btn2  = VCL.Button(pb,"BTN2");pb.btn2._  ={left=50, top=62, width=200,caption="发送", onclick="btnClicked"}

ShowVclForm(pb.Height+100);
ShowOutputForm(370);
CloseCodeForm();
HideLeftTools();
HideRightTools(); 

function OpenFile()
   pb.edit1.text=GetFileName();
end;
function btnClicked(sender)
    --local f = io.open("c:\\J Link.log", "rb") 
    local f = io.open(pb.edit1.text, "rb")     
    if f==nil then print("file open error");return;end;

    local block = 1000
    while true do
        local bytes = f:read(block)
        if not bytes then break end
        print(#bytes);
        SendString(bytes); 
        Wait(1);
    end
    f:close();
    print("ok");
end;