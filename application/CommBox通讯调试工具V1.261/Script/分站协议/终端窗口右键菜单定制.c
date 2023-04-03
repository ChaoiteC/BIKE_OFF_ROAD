 
void main()
{
printf("------- 右键菜单 ---------");   
printf("在终端模式下，终端窗口中的右键菜单定义如下");  


SetMenuItemText(0,"send ps");
SetMenuItemText(1,"粘贴");
SetMenuItemText(2,"执行");
SetMenuItemText(3,"-");
SetMenuItemText(4,"ls");
SetMenuItemText(5,"cd to root");
SetMenuItemText(6,"cd to dir");
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
      //SendString(GetClipboardText());
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
  
