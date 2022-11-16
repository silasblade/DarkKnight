#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct graph //Khai báo cấu trúc đồ thị với số đỉnh và độ dài các cạnh
{
    int sodinh;       //Số đỉnh
    int dd[100][100]; //Ma trận kề có trọng số
};

struct edge //Cấu trúc cạnh
{
    int a; //Đỉnh đầu
    int e; //Độ dài cạnh
    int b; //Đỉnh đuôi
};

bool edgecheck[100]; //Kiểm tra cạnh đã đi qua chưa. Dùng cho duyệt đồ thị
bool visitid;        //Kiểm tra trả về kết quả dùng cho việc xét có tạo ra chu trình hay không

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




void swap(edge &a, edge &b) //Hàm hoán đổi hai cạnh, dùng cho việc sắp xếp thứ tự độ dài cạnh
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

bool checkexist(int x, int y, vector<edge> eg) //Hàm kiểm tra cây khung đang chọn đã bao gồm cạnh này chưa
{
    for(int i=0; i<eg.size(); i++)
    {
        if(x==eg[i].a && y==eg[i].b && edgecheck[i]==false) {edgecheck[i]=true; return 1;} //Nếu đỉnh đầu và đỉnh cuối của cạnh đưa vào có tồn tại trong cây khung đang chọn hay chưa
        if(x==eg[i].b && y==eg[i].a && edgecheck[i]==false) {edgecheck[i]=true; return 1;}
    }
    return 0;
}

void checklt(graph u, int x, int y, bool visited[], vector<edge> eg) //Hàm kiểm tra xem có tạo ra chu trình hay không
{
    for(int i=0; i<u.sodinh; i++) //Duyệt cây bắt đầu từ đỉnh của cạnh đang xét có tạo ra chu trình hay không, nếu cây chứa đỉnh còn lại thì tạo ra chu trình 
    {
        if(visitid==true) break; //Nếu visitid == true thì hủy vòng lặp, từ đỏ hủy dần quá trình đệ quy nhiều lần.
        //if(u.dd[x][i] > 0 && visited[i]==true)  
        if(checkexist(x,i,eg)) //Xét những cạnh có trong cây khung đã chọn chứa đỉnh đang xét 
        {
            if(i==y || visitid==true) {visitid=true; break;} //Nếu đỉnh bất kỳ có trong cây liên quan tới đỉnh đầu có chứa đỉnh cuối thì xác nhận tạo ra chu trình
            checklt(u, i, y, visited, eg);                   //Gọi đệ quy kiểm tra nếu đỉnh đuôi còn xét tiếp với những cạnh nối với đỉnh này
        }
    }
}

void sortrank(vector<edge> &ed) //Hàm sắp xếp các cạnh từ bé đến lớn
{
    for (int i = 0; i < ed.size(); i++)
    for (int j = i; j < ed.size(); j++)
    if(ed[j].e < ed[i].e) swap(ed[j], ed[i]);
    cout << endl;
}

void prin(vector<edge> eg)//Hàm in các cạnh có trong cây khung
{
    int s=0;

    for(int i=0; i<eg.size(); i++)
    {
        cout << eg[i].a << "--" << eg[i].b << " = " << eg[i].e << endl; 
        s+=eg[i].e;
    }
    cout << "Tong trong so cay khung: ";
    cout << s;
}

void Kruscal(graph u)
{
    vector<edge> eg; //Tập các cạnh sẽ được chọn làm cây khung ngắn nhất

    bool vexcheck[100]; //Tập các đỉnh và xác định chúng đã bao gồm trong cây hay chưa
    for(int i=0; i<u.sodinh; i++) //Gán cho tất cả các đỉnh đều chưa chứa trong cây
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
    
    for(int i=0; i<ed.size(); i++)//Duyệt tất cả các cạnh từ bé đến lớn
    {   
        visitid=false; //Đặt mặc định là cạnh không tạo ra chu trình
        for(int i=0; i<eg.size(); i++) //Đặt mặc định là các tất cả các cạnh đều chưa xét đã đi qua chưa
        {
              edgecheck[i]=false;
        }

        checklt(u, ed[i].a, ed[i].b, vexcheck, eg); //Hàm kiểm tra xem có tạo ra chu trình hay không

        if(visitid==false) //Nếu mà sau khi xét xong vẫn không tạo ra chu trình thì thêm cạnh vào cây khung
        {
            eg.push_back(ed[i]);
            vexcheck[ed[i].a]=true; //Đặt các đỉnh đều đã được xét
            vexcheck[ed[i].b]=true;
        }
    }

    prin(eg);

 
}

int main()
{
      graph u;
      readgraph(u);
      Kruscal(u);
      int a;
      cin>> a;
}