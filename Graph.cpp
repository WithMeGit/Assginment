/*
* MSSV:18110100
* Ho Va Ten: Nguyen Ngoc Hung
* Assignment: Bai Thuc Hanh So 2_3
* IDE: Visual Studio 2019
*/

#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<queue>;
#include<sstream>
#include<algorithm>
using namespace std;

#define MAX 50
#define FALSE 0;
#define TRUE 1;
#define Extremely 10000;

class Graph
{
    int Vertex; // số đỉnh
    int StartVertex; // đỉnh đầu
    int EndVertex;// đỉnh cuối
    int wieght_matrix[MAX][MAX];
    int adj[MAX][MAX];
    bool visited[MAX];
    vector<string> vector_vertex;// vector sắp xếp các đỉnh
    int Adjacencymatrix[MAX][MAX];
public:
    void init(string file);
    void adjmatrix(string file);
    void SortVertex();
    void BFS(int n);
    void ConnectedComponent();
    int CheckEuler_cycle();
    void ResetAdj();
    void FindWayEuler_cycle(int& n);
    void PrintWayEuler_cycle();
    void Dijkstra();
};

void Graph::init(string filename)
{
    ifstream reader;
    reader.open(filename);
    string listedge;
    if (reader.is_open())
    {
        reader >> Vertex;
        reader >> StartVertex;
        reader >> EndVertex;
        while (!reader.eof())
        {
            reader >> listedge;

            stringstream ss(listedge);
            while (ss.good())
            {
                string substr;
                getline(ss, substr, '(');
                getline(ss, substr, ',');
                vector_vertex.push_back(substr);
                getline(ss, substr, ',');
                vector_vertex.push_back(substr);
                getline(ss, substr,')');
                break;
            }
        }
    }
    else
    {
        cout << "Ten file nhap sai hoac khong ton tai!!!" << endl;
    }
    reader.close();
}

void Graph::SortVertex()
{
    for (int i = 0; i < vector_vertex.size(); i++)
    {
        sort(vector_vertex.begin(), vector_vertex.end());
        auto last = unique(vector_vertex.begin(), vector_vertex.end());
vector_vertex.erase(last, vector_vertex.end());
    }
}

void Graph::adjmatrix(string filename)
{
    ifstream fsfile;
    fsfile.open(filename);
    string input;
    int i, j;
    if (fsfile.is_open())
    {
        int n;
        fsfile >> input;
        fsfile >> input;
        fsfile >> input;
        for (i = 0; i < Vertex; i++)
        {
            visited[i] = false;
            for (j = 0; j < Vertex; j++)
            {
                Adjacencymatrix[i][j] = 0;
            }
        }
        while (!fsfile.eof())
        {
            fsfile >> input;
            stringstream ss(input);

            char u = input[1];
            char v = input[3];
            int w;
            string t = input.substr(5, input.length() - 6);
            stringstream intTicket(t);
            intTicket >> w;
            Adjacencymatrix[((int)u - 97)][((int)v - 97)] = w;
            Adjacencymatrix[((int)v - 97)][((int)u - 97)] = w;
        }

        for (i = 0; i < Vertex; i++)
        {
            cout << "\t" << vector_vertex[i];
        }
        cout << "\n";
        for (i = 0; i < Vertex; i++)
        {
            cout << vector_vertex[i];
            for (j = 0; j < Vertex; j++)
            {
                cout << "\t";
                cout << Adjacencymatrix[i][j];
                wieght_matrix[i + 1][j + 1] = Adjacencymatrix[i][j];
                if (Adjacencymatrix[i][j] != 0)
                {
                    Adjacencymatrix[i][j] = 1;
                    adj[i + 1][j + 1] = Adjacencymatrix[i][j];
                }
            }
            cout << "\n";
        }  
    }
    else
    {
        cout << "Ten file nhap sai hoac khong ton tai!!!" << endl;
    }

    cout << endl;

    fsfile.close();
}

void Graph::BFS(int n) 
{
    queue<int> q;
    q.push(n);
    visited[n] = true;
    while (!q.empty())
    {
        int j = q.front();
        q.pop();
        for (int i = 1; i <= Vertex; i++)
        {
            if (visited[i] == false && adj[j][i] == 1)
            {
                q.push(i);
                visited[i] = true;
            }
        }
     }
}

void Graph::ConnectedComponent()
{
    int slt = 0;
    for (int i = 1; i <= Vertex; i++)
    {
        if (visited[i] == false)
        {
            slt++;// đếm số thành phần liên thông
            BFS(i);
        }
    }
    if (slt == 1) // nếu số thành phần liên thông = 1 => đồ thị liên thông không phải thì đồ thị không liên thông
    {
        cout << "Do thi nay co duong di lien thong ";
    }
    else
    {
        cout << "Do thi nay khong co duong di lien thong";
    }

    cout << endl;
}

int Graph::CheckEuler_cycle()
{
    int index = 0;
    int count = 0;
    for (int i = 1; i <= Vertex; i++)
    {
        for (int j = 1; j <= Vertex; j++)
        {
            index += adj[i][j];//đếm số bạc của đỉnh trong đồ thị
        }
        if (index % 2)
        {
            count++;
        }
    }
    if (count > 0)
    {
        return FALSE;//nếu có 1 đỉnh bậc lẻ => đồ thị không có chu trình euler
    }
    else
    {
        return TRUE;//nếu tất cả các đỉnh có bậc chẵn => đồ thị có chu trình euler
    }
}

void Graph::ResetAdj()
{
    for (int i = 0; i < Vertex; i++)
    {
        for (int j = 0; j < Vertex; j++)
        {
            adj[i + 1][j + 1] = Adjacencymatrix[i][j];
        }
    }
}

void Graph::FindWayEuler_cycle(int &n)
{
    int src, dst, top, indexEu;
    int stack[MAX];// stack lưu đỉnh đã xét
    int Euler[MAX];
    top = 1;
    stack[top] = n;
    indexEu = 0;
    do {
        src = stack[top]; 
        dst = 1;
        while (dst <= Vertex && adj[src][dst] == 0) 
            dst++;
        if (dst > Vertex) { 
            indexEu++;
            Euler[indexEu] = src;
            top--;
        }
        else {
            top++;
            stack[top] = dst;
            adj[src][dst] = 0;
            adj[dst][src] = 0;
        }
    } while (top != 0);
    for (int i = indexEu; i > 0; i--)
    {
        cout << (char)(Euler[i] + 'a' - 1) << "-> ";
    }
    ResetAdj();
    cout << endl;
}

void Graph::PrintWayEuler_cycle()
{
        if (CheckEuler_cycle())
    {
        cout << "co chu trinh euler" << endl;
        int index = 1;
        while (index <= Vertex)
        {
            FindWayEuler_cycle(index);
            index++;
        }
    }
    else
    {
        cout << "khong co chu trinh euler" << endl;
    }
}

void Graph::Dijkstra()
{
    int src, ext;
    int mark_way[MAX];// mảng đánh dấu đường đi
    int mark_space[MAX];// mảng đánh dấu khoảng cách
    int mark_vertex[MAX]; // mảng đánh dấu đỉnh

    for (int i = 1; i <= Vertex; i++)
    {
        for (int j = 1; j <= Vertex; j++)
        {
            if (wieght_matrix[i][j] == 0)
            {
                wieght_matrix[i][j] = Extremely;
            }
        }
    }

    for (int dst = 1; dst <= Vertex; dst++)
    {
        mark_space[dst] = wieght_matrix[StartVertex][dst];
        mark_way[dst] = StartVertex;
        mark_vertex[dst] = FALSE;
    }

    mark_way[StartVertex] = 0;
    mark_space[StartVertex] = 0;
    mark_vertex[StartVertex] = TRUE;

    while (!mark_vertex[EndVertex])
    {
        ext = Extremely;

        for (int dst = 1; dst <= Vertex; dst++)
        {
            if ((!mark_vertex[dst]) && (ext > mark_space[dst]))
            {
                src = dst;
                ext = mark_space[dst];
            }
        }

        mark_vertex[src] = TRUE;
        if (!mark_vertex[EndVertex])
        {
            for (int dst = 1; dst <= Vertex; dst++)
            {
                if ((!mark_vertex[dst]) && (mark_space[src] + wieght_matrix[src][dst] < mark_space[dst]))
                {
                    mark_space[dst] = mark_space[src] + wieght_matrix[src][dst];

                    mark_way[dst] = src;
                }
            }
        }
    }
     
    cout << "Duong di ngan nhat tu " << (char)(StartVertex + 'a' - 1) << " den " << (char)(EndVertex + 'a' - 1) << " la " << endl;

    cout << (char)(EndVertex + 'a' - 1) << "<--";

    int way = mark_way[EndVertex];

    while (way != StartVertex) {
        cout << (char)(way + 'a' - 1) << "<--";
        way = mark_way[way];
    }

    cout << (char)(StartVertex + 'a' - 1) << "(" << mark_space[EndVertex] << ")" << endl;
}


void main(void)
{
    Graph g;
    g.init("graph.txt");
    g.SortVertex();
    cout << "a. ma tran vo huong" << endl;
    g.adjmatrix("graph.txt");
    cout << "b. ";
    g.ConnectedComponent();
    cout << endl;
    cout << "c. ";
    g.PrintWayEuler_cycle();
    cout << endl;
    cout << "d. ";
    g.Dijkstra();
    cout << endl;

    system("pause");
}