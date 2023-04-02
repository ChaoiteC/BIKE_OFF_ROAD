ClearOutput();   --清除输出窗口内容        align = "alClient",
ClearCommWin();
CloseSendForm();
--ShowOutputForm(170);--
CloseCodeForm();
HideLeftTools();
HideRightTools();
Update();

myForm   = VCL.Form("myForm1")
myForm._ = {left=50, top=1, height=150, width=350, position="poDesigned", caption="Image viewer demo",borderstyle="bsNone",};--Align="alClient", }
myForm.button1 = VCL.SpeedButton(myForm,"SB1")
myForm.button1._ = {left=10, top=70, width=240, height=30, caption="关闭",  onclick="OnClose"}

myForm.tm1 = VCL.Timer(myForm,"tm1")
myForm.tm1._ = {interval=500,  onTimer="OnTimer"}
myForm.lblSdTxt = VCL.Label(myForm,"lblSdTxt")
myForm.lblSdTxt._ = {left=10, top=8, width=70, height=20, caption="发送内容:",}

myForm.edtSdTxt = VCL.Edit(myForm,"btnSdTxt")
myForm.edtSdTxt._ = {left=80, top=5, width=170, height=20, text="12345",}
myForm.cb1 = VCL.CheckBox(myForm,"CB1"); 
myForm.cb1._  ={left=80, top=35,caption="定时发送", onclick="setattr"}

local closed=0;
ShowVclForm(myForm.Height+8);

function setattr()
end;
function OnTimer()
  if closed==0 then
  if myForm.cb1.checked then
     --Print(myForm.edtSdTxt.Text);
     SendString(myForm.edtSdTxt.Text);
  end;
  end;
end

function OnClose()
  closed=1;
  myForm:Close();
  myForm:Free();
  HideVclForm();
end
myForm:Show();--Modal()