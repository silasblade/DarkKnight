#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
using namespace std;

struct graph //Khai báo cấu trúc đồ thị với số đỉnh và độ dài các cạnh
{
    int sodinh;
    int dd[100][100];
};
string cactinh[50];
void readgraph(graph &u) //Đọc ma trận kề có trọng số từ file
{
    ifstream is("graph.txt"); //Cú pháp mở file
    is >> u.sodinh; //Nhập số đỉnh là thông tin đầu tiên của file
    for(int i=0; i<u.sodinh; i++) //Thủ tục nhập các cạnh của đồ thị vào
    for(int j=0; j<u.sodinh; j++)
    {
        is >> u.dd[i][j];
    }

    is.ignore();
    for(int i=0; i<u.sodinh; i++)
    {
        getline(is, cactinh[i]);
    }
}

int minvex(int* vex, bool* vexcheck, graph u) //Tìm ra cạnh nhỏ nhất so với các cạnh đang nối với cây hiện tại 
{
    int min=INT_MAX; //Giá trị nhỏ nhất cho vô cực
    int minum=0; //Gán tên đỉnh đó đang có cạnh nhỏ nhất nối với cây  
    for(int i=0; i<u.sodinh; i++) //Chạy từ đỉnh 0 tới đỉnh cuối
    {
        if(vex[i]<min && !vexcheck[i]) //Nếu đỉnh nối với cây có cạnh nhỏ hơn các đỉnh khác, và đỉnh đó chưa bị chọn
        {
            min=vex[i]; //Giá trị cạnh nhỏ nhất hiện tại là:
            minum=i; //Gán tên đỉnh có cạnh nối cây nhỏ nhất
        }
    }
    return minum; //Trả về tên đỉnh có cạnh nối với đỉnh của cây hiện tại đang là nhỏ nhất
}

void prim(graph u)
{
    int vex[100]; //Khai báo tập các cạnh của các đỉnh hiện đang nối với cây khung mà mình đăng chọn
    bool vexcheck[100]; //Xác nhận xem đỉnh đã được chọn hay chưa
    for(int i=0; i<u.sodinh; i++) //Vòng lặp ban đầu
    {
        vex[i]=INT_MAX; //Gán giá trị vô hạn cho các cạnh đang nối với cây hiện tại đang tìm, có nghĩa là đỉnh này chưa nối với cây
        vexcheck[i]=false; //Xác định cạnh nối đỉnh này với cây là chưa tối ưu
    }
    vex[0]=0; //Khai báo khoảng cách từ đỉnh ban đầu với đỉnh ban đầu được chọn = 0 

    int branch[100]; //Khai báo các đỉnh, đỉnh cho biết đỉnh nào nối với cây bằng đỉnh nào
    branch[0]=0; //Đỉnh nối với đỉnh ban đầu là chính nó


    for(int i=1; i<u.sodinh; i++) //Vòng lặp chạy từ đỉnh 1 đến đỉnh cuối, số lần lặp tương ứng với số cạnh nối với đỉnh tìm ra
    {
       int add=minvex(vex, vexcheck, u); //Add là đỉnh được chọn trước đó (có cạnh nối với cây ngắn nhất so với các đỉnh có cạnh đang nối với cây hiện tại)
       vexcheck[add]=true; //Xác nhận đỉnh được chọn

        for(int v=0; v<u.sodinh; v++) //Vòng lặp chạy từ đỉnh 0 tới đỉnh cuối, cập nhật lại các cạnh nối đỉnh chưa chọn với cây cho tối ưu.
        {
            if(vex[v] > u.dd[add][v] && u.dd[add][v] && vexcheck[v]==false) //Điều kiện là nếu cạnh nối với đỉnh vừa chọn, cạnh đó tồn tại, đỉnh nối với đỉnh vừa chọn chưa bị chọn
            {
                vex[v]=u.dd[add][v]; //Gán cho tập các cạnh nối với đỉnh trong cây của mỗi đỉnh bất kỳ giá trị nhỏ nhất mà nó nhận được
                branch[v]=add; //Xác định đỉnh nối với đỉnh đang nối với cây là đỉnh nào.
            }
        }

        
         
    }

    for(int i=1; i<u.sodinh; i++) // Vòng lặp xuất ra các đỉnh nối với nhau và trọng số của chúng
    {
        cout << cactinh[branch[i]] << "--" << cactinh[i] << " = " << vex[i] << endl;
    }

    cout << "Tong chieu dai cay khung duong sat ngan nhat can phai xay dung la:: ";
    int S=0;
    for(int i=0; i<u.sodinh; i++)
    {
        S+=vex[i];
    }
    cout << S;

    
}

int main()
{
   graph u;
   readgraph(u);
   prim(u);
   int trash;
   cin >> trash;
}