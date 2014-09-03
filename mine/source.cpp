#include <stdio.h>
#include <windows.h>
#include <vector>
#include<stdlib.h>
#include<iostream>
using namespace std;

struct point
{
    double x,y;	//存储矩形位置
    int area;  //该点大小
    double vx,vy,ay;  //x速度，y加速度
    int color;
};
//vector<point> vec;
vector<point> vec1;

RECT g_rect = {0};
HINSTANCE   g_hInst = NULL;
HWND        hwnd 	= NULL;
HDC			hdc 	= NULL;
HDC 		buffer	= NULL;
HBITMAP 	bmp;

HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render(HDC buf);

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    if( FAILED( InitWindow( hInstance, true) ) )
        return 0;
    MSG msg = {0};

    GetClientRect(hwnd,&g_rect);

    hdc = GetDC(hwnd);
    buffer = CreateCompatibleDC(hdc);
    bmp = CreateCompatibleBitmap(hdc,g_rect.right,g_rect.bottom);

//    point pp;
//    for(int i=0; i<10; i++)
//    {
//        pp.x=rand()%10;
//        pp.y=rand()%300;
//        vec.push_back(pp);
//    }
    while(WM_QUIT != msg.message)
    {
        if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Render(buffer);
            BitBlt(hdc,0,0,g_rect.right - g_rect.left,g_rect.bottom - g_rect.top,buffer,0,0,SRCCOPY);
        }
    }
    return ( int )msg.wParam;
}

HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, NULL );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "CrystalMiao";
    wcex.hIconSm = LoadIcon( wcex.hInstance, NULL );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 1366, 768 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    hwnd = CreateWindow( "CrystalMiao","Crystal Miao", WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                         NULL );
    if(!hwnd )
        return E_FAIL;

    ShowWindow( hwnd, nCmdShow );

////////////////////////////////////////////////////
    return S_OK;
}

bool isDown = false;

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    point pt;
    switch( message )
    {
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    case WM_MOUSEMOVE:
        if(isDown == false)
        {
            break;
        }
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        //vec.push_back(pt);
        break;
    case WM_LBUTTONDOWN:
        isDown = true;
        break;
    case WM_LBUTTONUP:
        isDown = false;
        break;
    case WM_KEYDOWN:
        printf("%c",wParam);
        break;
    default:
        return DefWindowProc( hWnd, message, wParam, lParam );
    }
    return 0;
}

HPEN pen = CreatePen(PS_SOLID,1,RGB(255,0,0));
HBRUSH brush = CreateSolidBrush(RGB(0,255,0));
HBRUSH brush1 = CreateSolidBrush(RGB(0,0,0));
HBRUSH brush2 = CreateSolidBrush(RGB(0,215,0));
HBRUSH brush3 = CreateSolidBrush(RGB(0,170,0));
HBRUSH brush4 = CreateSolidBrush(RGB(0,120,0));
HBRUSH brush5 = CreateSolidBrush(RGB(0,65,0));
HBRUSH brush6 = CreateSolidBrush(RGB(255,255,255));
HBRUSH b0 = CreateSolidBrush(RGB(210,0,210));
HBRUSH b1 = CreateSolidBrush(RGB(0,255,255));
HBRUSH b2 = CreateSolidBrush(RGB(255,0,255));
HBRUSH b3 = CreateSolidBrush(RGB(255,255,0));
HBRUSH b4 = CreateSolidBrush(RGB(0,128,255));
HBRUSH b5 = CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));


int beforex[5],beforey[5];
int x=0,y=0,x1=0,y1=0;
int time = 0,blank;
void coordinate()
{
    x1=rand()*1366/(double)RAND_MAX;
    y1=rand()*768/(double)RAND_MAX;
    blank=rand()%100;  //每个烟花出现的时间间隔
}
int cc=0;
void Render(HDC buf)
{
    if(!time||blank == time)
    {
        cc++;
        cc%=6;
        time=0;
        while(((x1*x1+y1*y1-x*x-y*y)<20)&&((x1*x1+y1*y1-x*x-y*y)>(-20))||y1>400) //如果两个烟花中心离得太近就舍掉重新取
            coordinate();
        x=x1;
        y=y1;
        int num=rand()%200+300;            //每个烟花的分支数
        int basicarea=rand()%4+4;        //每个分支上的圆的基础大小

        for(int i=0; i<num; i++)
        {
            point pnow;
            pnow.x=x;
            pnow.y=y;
            pnow.color=cc;
            if(i%2==1)
                pnow.area=basicarea+2;
            else
                pnow.area=basicarea-2;
                pnow.vx=rand()*11/(double)RAND_MAX-5;
                pnow.vy=rand()*11/(double)RAND_MAX-5;
            while((pnow.vx*pnow.vx+pnow.vy*pnow.vy)>25)
            {
                pnow.vx=rand()*11/(double)RAND_MAX-5;
                pnow.vy=rand()*11/(double)RAND_MAX-5;
            }
            pnow.ay=-0.2;
            vec1.push_back(pnow);
        }
    }
    time++;
    SelectObject(buf,bmp);//这行不用管。我的框架忘记添加了
    SelectObject(buf,brush1);
    Rectangle(buf,0,0,1366,768);
    //Add your render code here.
    //SelectObject(buf,pen);
    SelectObject(buf,brush);
    for(int i=0; i<vec1.size(); i++)
    {
        switch(vec1[i].color)
        {
        case 0:
            SelectObject(buf,b0);
            break;
        case 1:
            SelectObject(buf,b1);
            break;
        case 2:
            SelectObject(buf,b2);
            break;
        case 3:
            SelectObject(buf,b3);
            break;
        case 4:
            SelectObject(buf,b4);
            break;
        case 5:
            SelectObject(buf,brush);
            break;
        case 6:
            SelectObject(buf,b5);
        default:
            SelectObject(buf,b1);
            break;
        }

        Ellipse(buf,vec1[i].x,vec1[i].y,vec1[i].x + vec1[i].area,vec1[i].y + vec1[i].area);
        for(int i=4;i>0;i--)
        {
            beforex[i]=beforex[i-1];
            beforey[i]=beforey[i-1];
        }
        beforex[0]=vec1[i].x-vec1[i].vx;
        beforey[0]=vec1[i].y-vec1[i].vy;
        for(int j=0; j<5; j++)
        {
            switch(j)
            {
            case 0:
                SelectObject(buf,brush2);
                break;
            case 1:
                SelectObject(buf,brush3);
                break;
            case 2:
                SelectObject(buf,brush4);
                break;
            case 3:
                SelectObject(buf,brush5);
                break;
            case 4:
                SelectObject(buf,brush6);
                break;
            default:
                ;
                break;
            }
            Ellipse(buf,beforex[j],beforey[j],beforex[j]+4,beforey[j]+4);
        }
        vec1[i].x+=vec1[i].vx;
        vec1[i].y+=vec1[i].vy;
        vec1[i].vy-=vec1[i].ay;
        if(vec1[i].x>1366||vec1[i].y>768)
        {
            vector<point>::iterator it = vec1.begin()+i;
            vec1.erase(it);
        }
    }
    Sleep(8);

}
