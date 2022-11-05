#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct graph //Khai báo cấu trúc đồ thị với số đỉnh và độ dài các cạnh
{
    int sodinh;
    int dd[100][100];
};

bool edgecheck[100];
bool visitid;

void readgraph(graph &u) //Đọc ma trận kề có trọng số từ file
{
    ifstream is("graph.txt"); //Cú pháp mở file
    is >> u.sodinh; //Nhập số đỉnh là thông tin đầu tiên của file
    for(int i=0; i<u.sodinh; i++) //Thủ tục nhập các cạnh của đồ thị vào
    for(int j=0; j<u.sodinh; j++)
    {
        is >> u.dd[i][j];
    }
}


struct edge
{
    int a;
    int e;
    int b;
};

void swap(edge &a, edge &b)
{
    edge temp;
    temp.a=a.a;
    temp.b=a.b;
    temp.e=a.e;

    a.a=b.a;
    a.b=b.b;
    a.e=b.e;

    b.a=temp.a;
    b.b=temp.b;
    b.e=temp.e;
}

bool checkexist(int x, int y, vector<edge> eg)
{
    for(int i=0; i<eg.size(); i++)
    {
        if(x==eg[i].a && y==eg[i].b && edgecheck[i]==false) {edgecheck[i]=true; return 1;}
        if(x==eg[i].b && y==eg[i].a && edgecheck[i]==false) {edgecheck[i]=true; return 1;}
    }
    return 0;
}

void checklt(graph u, int x, int y, bool visited[], vector<edge> eg)
{
    for(int i=0; i<u.sodinh; i++)
    {
        if(visitid==true) break;
        if(u.dd[x][i] > 0 && visited[i]==true)
        if(checkexist(x,i,eg))
        {
        if(i==y || visitid==true) {visitid=true; break;}
        checklt(u, i, y, visited, eg);
        }
    }
}

void sortrank(vector<edge> &ed)
{
    for (int i = 0; i < ed.size(); i++)
    for (int j = i; j < ed.size(); j++)
    if(ed[j].e < ed[i].e) swap(ed[j], ed[i]);
    cout << endl;
}

void getedge(graph u)
{
    vector<edge> eg; //Tập các cạnh sẽ được chọn làm cây khung ngắn nhất

    bool vexcheck[100]; //Tập các đỉnh và xác định chúng đã bao gồm trong cây hay chưa
    for(int i=0; i<u.sodinh; i++)
    {
        vexcheck[i]=false;
    }

    vector<edge> ed; //Tập các cạnh tồn tại trong đồ thị
    for(int i=0; i<u.sodinh; i++)
    for(int j=i; j<u.sodinh; j++)
    {
        if(u.dd[i][j])
        {
            edge p;
            p.a=i;
            p.b=j;
            p.e=u.dd[i][j];
            ed.push_back(p);
        }
    }

    sortrank(ed);// Sắp xếp các cạnh theo thứ tự tăng dần
    
    for(int i=0; i<ed.size(); i++)
    {   
        visitid=false;
        for(int i=0; i<eg.size(); i++)
        {
              edgecheck[i]=false;
        }

        checklt(u, ed[i].a, ed[i].b, vexcheck, eg);

        if(visitid==false)
        {
            eg.push_back(ed[i]);
            vexcheck[ed[i].a]=true;
            vexcheck[ed[i].b]=true;
        }
    }
    

    for(int i=0; i<eg.size(); i++)
    {
        cout << eg[i].a << "--" << eg[i].b << " = " << eg[i].e << endl; 
    }
    
    
 
}

void kruscal(edge e)
{
    vector<edge> ed;
}

int main()
{
      graph u;
      readgraph(u);
      getedge(u);
      int a;
      cin>> a;
}