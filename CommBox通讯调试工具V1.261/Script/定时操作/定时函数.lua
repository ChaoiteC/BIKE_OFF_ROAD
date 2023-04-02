function Timer1000ms()
   SendString(GetDateTimeStr()..'\r');
   --SendString("1234567890abcdefghijklmnopqrst");  
 
end; 

function Timer500ms()
   for i=0,10 do SendByte(i); end;

end;