#include <graphics.h>
#include <iostream>

char board_data[3][3] =
{
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

char current_piece = 'o';

bool CheckWin(char player)
{
    if (board_data[0][0] == player && board_data[0][1] == player && board_data[0][2] == player)
        return true;
    if (board_data[1][0] == player && board_data[1][1] == player && board_data[1][2] == player)
        return true;
    if (board_data[2][0] == player && board_data[2][1] == player && board_data[2][2] == player)
        return true;
    if (board_data[0][0] == player && board_data[1][0] == player && board_data[2][0] == player)
        return true;
    if (board_data[0][1] == player && board_data[1][1] == player && board_data[2][1] == player)
        return true;
    if (board_data[0][2] == player && board_data[1][2] == player && board_data[2][2] == player)
        return true;
    if (board_data[0][0] == player && board_data[1][1] == player && board_data[2][2] == player)
        return true;
    if (board_data[0][2] == player && board_data[1][1] == player && board_data[2][0] == player)
        return true;
    return false;
}

bool CheckDraw()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (board_data[i][j] == '_')
            {
                return false;
            }
        }
    }
    return true;
}

void DrawBoard()
{
    line(0, 200, 600, 200);
    line(0, 400, 600, 400);
    line(200, 0, 200, 600);
    line(400, 0, 400, 600);
}

void DrawPawn()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            switch (board_data[i][j])
            {
            case 'o':
                circle(200 * j + 100, 200 * i + 100, 100);
                break;
            case 'x':
                line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
                line(200 * (j + 1), 200 * i, 200 * j, 200 * (i + 1));
                break;
            default:
                break;
            }
        }
    }
}

void DrawTipText()
{
    static TCHAR tip_text[64];
    _stprintf_s(tip_text,_T("当前棋子类型：%s"), current_piece);
    settextcolor(RGB(225,175,45));
    outtextxy(0,0,tip_text);
}

int main()
{
    initgraph(600, 600);
    BeginBatchDraw();

    bool running = true;
    ExMessage msg;
    while (running)
    {
        //消息处理
        while (peekmessage(&msg))
        {
            if (msg.message == WM_LBUTTONDOWN)
            {
                // 计算点击了 棋盘上哪个格子
                int x = msg.x;
                int y = msg.y;
                int index_x = x / 200;
                int index_y = y / 200;

                //尝试落子
                if (board_data[index_y][index_x] == '_')
                {
                    board_data[index_y][index_x] = current_piece;
                    //切换棋子类型
                    if (current_piece == 'o')
                    {
                        current_piece = 'x';
                    }
                    else
                    {
                        current_piece = 'o';
                    }
                }
            }
        }
        //数据处理
        if (CheckWin('c'))
        {
            MessageBox(GetHWnd(),_T("x Player Win"),_T("Game Over"),MB_OK);
            running = false;
        }
        else if (CheckWin('o'))
        {
            MessageBox(GetHWnd(),_T("o Player Win"),_T("Game Over"),MB_OK);
            running = false;
            
        }
        else if (CheckDraw())
        {
            MessageBox(GetHWnd(),_T("平局"),_T("Game Over"),MB_OK);
            running = false;
        }


        //画面更新
        cleardevice();
        DrawBoard();
        DrawPawn();
        DrawTipText();
        FlushBatchDraw();
    }


    EndBatchDraw();

    return 0;
}
