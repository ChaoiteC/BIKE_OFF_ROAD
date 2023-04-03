 
void main()
{
printf("------- 右键菜单 ---------");   
printf("在终端模式下，终端窗口中的右键菜单定义如下");  


SetMenuItemText(0,"send ps");
SetMenuItemText(1,"tftp 快速传输");
SetMenuItemText(2,"执行");
SetMenuItemText(3,"-");
SetMenuItemText(4,"ls");
SetMenuItemText(7,"-");

}

void MenuItemClick(int idx)
{
   printf("MenuItem %d clicked!",idx);
   if(idx==0)
   {
     SendString("ps\r");
   }
   else if(idx==1)
   {
      char s[100];
      int len=GetCommWinSelText(s,100);
      char buf[100];
      sprintf(buf,"tftp -s -l ./%s 192.168.11.2\n",s); 
      SendString(buf);
   }
   else if(idx==2)
   {
      //CopyToClipboard();
      //SendString("./"..GetClipboardText());
   }
   else if(idx==4)
   {
      SendString("ls\r");
   }
   else if(idx==5)
   {
      SendString("cd \\\r");
   }
   else if(idx==6)
   {
      //CopyToClipboard();
      //SendString("cd "..GetClipboardText().."\r");
   }


}
  
