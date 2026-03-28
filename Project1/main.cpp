#include <graphics.h>
#include <iostream>


int main()
{
   initgraph(1280,720);
   BeginBatchDraw();
   //圆心位置
   int x = 300,y = 300;
   
   while(true)
   {
      ExMessage message;
      while (peekmessage(&message))
      {
         //鼠标移动逻辑
         if (message.message == WM_MOUSEMOVE)
         {
            //更新圆心位置
            x = message.x;
            y = message.y;
         }
         
      }
      cleardevice();
      solidcircle(x,y,100);
      //输出绘图
      FlushBatchDraw();
   }
   EndBatchDraw();
   
   return 0;
}
