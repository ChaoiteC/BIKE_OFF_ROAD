
void click()
{
    PrintToCommWin("aaaaaaaaabc");
}

void main()
{
    int a=AddTreeNode(0,"´®¿ÚÃüÁî" ,0);
    int b=AddTreeNode(a,"111" ,0);
    AddTreeNode(a,"222" ,click);
    AddTreeNode(b,"cccc" ,click);
}
