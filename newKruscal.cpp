#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool visited[100];

struct graph //Cấu trúc ma trận kề có trọng số của đồ thị
{
    int sodinh=0;
    int dd[50][50]={0};
};

graph caykhung; //Đồ thị sẽ lưu trữ cây khung
bool makecycle; //Biến kiểm tra xem khi chọn cạnh có tạo chu trình hay không
string cactinh[50];

struct edge //Cấu trúc các cạnh của đồ thị
{
    int a;
    int e;
    int b;
};

void readgraph(graph &u) //Hàm đọc ma trận từ đồ thị
{
    ifstream is("graph.txt");
    is >> u.sodinh;
    for(int i=0; i<u.sodinh; i++)
    {
        for(int j=0; j<u.sodinh; j++)
        {
            is >> u.dd[i][j];
        }
    }
    caykhung.sodinh=u.sodinh; //Gán cho số đỉnh của cây = ma trận
    
    is.ignore();
    for(int i=0; i<u.sodinh; i++)
    {
        getline(is, cactinh[i]);
    }



}

void cycle(int x, int y) //Hàm kiểm tra có tạo ra chu trình hay không
{
    //Ý tưởng thuật toán: Đưa vào hai đỉnh của một cạnh. Xét tất cả các đỉnh liên thông với đỉnh đầu (đỉnh x(a)) của cạnh này. 
    //Các đối tượng xét chỉ bao gồm các cạnh đã chọn để sau này làm cây khung ngắn nhất.
    //Nếu trong số các đỉnh liên thông với đỉnh đầu bao gồm đỉnh cuối (đỉnh y(b)) của cạnh đó thì ghi nhận là tạo ra chu trình. Hủy thuật toán.
    //Visited dùng để ghi nhận đỉnh này đã xét.
    for(int i=0; i< caykhung.sodinh; i++)
    {
        visited[x]=true;                                       //Coi như đỉnh này đã được xét qua.
        if(x==y || makecycle==true) {makecycle=true; break;}   //Nếu đỉnh x đang xét chính là đỉnh y thì coi như tạo ra chu trình. Hủy hàm. Ghi nhận rằng tạo ra chu trình (makecycle=true);
        if(caykhung.dd[x][i] > 0 && !visited[i])               //Xét các đỉnh liên thông với đỉnh x. Sử dụng đệ quy để coi như đỉnh liên thông với x đó trở thành đỉnh x. Đệ quy quay lại xét các đỉnh liên thông với x mới.
        cycle(i, y);
    }
}

bool compare(edge a, edge b) //Hàm so sánh. Dùng để sử dụng hàm sort các struct.
{
    return a.e < b.e;
}

void prin(vector<edge> eg)//Hàm in các cạnh có trong cây khung
{
    int s=0;

    for(int i=0; i<eg.size(); i++)
    {
        cout << cactinh[eg[i].a] << "--" << cactinh[eg[i].b] << " = " << eg[i].e << endl; 
        s+=eg[i].e;
    }
    cout << "Tong chieu dai cay khung duong sat ngan nhat can phai xay dung la: ";
    cout << s;
}

void kruscal(graph u)
{
    vector<edge> ed;                //Tập các cạnh tồn tại trong đồ thị
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

    sort(ed.begin(), ed.end(), compare); //Sắp xếp các cạnh từ bé đến lớn

    vector<edge> eg;                     //Tập chứa các cạnh có trong cây khung cuối cùng
    for(int i=0; i< ed.size(); i++)      //Xét từng cạnh của đồ thị 
    {
        makecycle=false;                 //Gán giá trị tạo chu trình = 0 để sử dụng cho hàm xét chu trình.
        for(int j=0; j<u.sodinh; j++)    //Gán giá trị các cạnh đã xét = 0 để sử dụng cho hàm xét chu trình
        visited[j] = {false};

        cycle(ed[i].a, ed[i].b);         //Xét tạo ra chu trình không

        if(makecycle==false)             //Sau khi xét mà giá trị tạo chu trình vẫn bằng false thì ghi nhận cạnh này vào cây khung.
        {
           eg.push_back(ed[i]);
        }
        caykhung.dd[ed[i].a][ed[i].b] = ed[i].e; //Lưu cạnh này vào đồ thị chứa cây khung cuối cùng
        caykhung.dd[ed[i].b][ed[i].a] = ed[i].e;
    }

    prin(eg); //In các cạnh cây khung

}

int main()
{
    graph u;
    readgraph(u);
    kruscal(u);
}