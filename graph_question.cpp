#include<iostream>
#include<string>
#include<queue>
#include<math.h>
#define INFINITE 65536
using namespace std;

class Orienteering
{
    public:
    void main();
    int connect[101][101];

    string DecToBin(int number)
    {
        if ( number == 0 ) return "0";
        if ( number == 1 ) return "1";

        if ( number % 2 == 0 )
            return DecToBin(number / 2) + "0";
        else
            return DecToBin(number / 2) + "1";
    }

    int point(int x_coordinate,int y_coordinate,int width)
    {
        return ((x_coordinate-1)*width + y_coordinate);
    }

    void add_edge(int source,int destination)
    {
        connect[source][destination] = 1;
        return;
    }

};

void Orienteering::main()
{
    int check_points = 0,start_state,final_state;
    int width,height,non_empty_states = 0;
    bool ischeckpoint[10001]={0},visited[10001]={0};
    cin>>width>>height;
    int size = width*height;size++;
    int b[size],non_empty[size];
    string A[height+1];
    for(int i=1;i<=height;i++)
        cin>>A[i];
    for(int i=1;i<=height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(A[i][j]!='#')
            {
                if(A[i][j]=='S' || A[i][j]=='G' || A[i][j]=='@')
                {
                    non_empty[non_empty_states] = point(i,j+1,width);
                    non_empty_states++;
                    b[check_points]=point(i,j+1,width);
                    ischeckpoint[point(i,j+1,width)] = true;
                    check_points++;
                    if(A[i][j]=='S')
                        start_state = point(i,j+1,width);
                    else if(A[i][j]=='G')
                        final_state = point(i,j+1,width);
                }
                else
                {
                    non_empty[non_empty_states] = point(i,j+1,width);
                    non_empty_states++;
                    ischeckpoint[point(i,j+1,width)] = false;
                }
                if(j>0 && A[i][j-1]!='#'){
                    add_edge(point(i,j+1,width) , point(i,j,width));
                    cout<<point(i,j+1,width)<<","<<point(i,j,width)<<" connected"<<endl;}
                if(j<(width-1) && A[i][j+1]!='#'){
                    add_edge(point(i,j+1,width) , point(i,j+2,width));
                    cout<<point(i,j+1,width)<<","<<point(i,j+2,width)<<" connected"<<endl;}
                if(i>1 && A[i-1][j]!='#'){
                    add_edge(point(i,j+1,width) , point(i-1,j+1,width));
                    cout<<point(i,j+1,width)<<","<<point(i-1,j+1,width)<<" connected"<<endl;}
                if(i<height && A[i+1][j]!='#'){
                    add_edge(point(i,j+1,width) , point(i+1,j+1,width));
                    cout<<point(i,j+1,width)<<","<<point(i+1,j+1,width)<<" connected"<<endl;}
            }
        }
    }

    int bfs,distance[size][size],TSP[size][size];
    for(int i=0;i<check_points;i++)
    {
        for(int j=0;j<non_empty_states;j++)
            visited[non_empty[j]] = false;
/*        for(int k=1;k<=height;k++)
        {
            for(int j=0;j<width;j++)
            {
                if(A[k][j]!='#')
                    visited[point(k,j+1,width)] = false;
            }
        }*/
        queue<int> Q;
        Q.push(b[i]);Q.push(-1);
        visited[b[i]] = true;
        bfs = 0;
        distance[b[i]][b[i]] = bfs;
        TSP[b[i]][b[i]] = 0;
        while(Q.size()>1)
        {
            if(Q.front()==-1)
            {
                cout<<"bfs="<<bfs<<endl;
                bfs++;
                Q.pop();
                Q.push(-1);
            }
            else if(Q.front()!=-1)
            {
                cout<<"Q.front is: "<<Q.front()<<endl;
                if(ischeckpoint[Q.front()]  && Q.front()!=b[i])
                        TSP[b[i]][Q.front()] = bfs;
                if(Q.front()>width && connect[Q.front()][Q.front()-width]==1 && !visited[Q.front()-width])
                {
                    visited[Q.front()-width] = true;
                    Q.push(Q.front()-width);
                    distance[b[i]][Q.front()-width] = bfs;
                }
                if(Q.front()<=(width*(height-1)) && connect[Q.front()][Q.front()+width]==1 && !visited[Q.front()+width])
                {
                    visited[Q.front()+width] = true;
                    Q.push(Q.front()+width);
                    distance[b[i]][Q.front()+width] = bfs;
                }
                if(Q.front()%width!=1 && connect[Q.front()][Q.front()-1]==1 && !visited[Q.front()-1])
                {
                    visited[Q.front()-1] = true;
                    Q.push(Q.front()-1);
                    distance[b[i]][Q.front()-1] = bfs;
                }
                if(Q.front()%width!=0 && connect[Q.front()][Q.front()+1]==1 && !visited[Q.front()+1])
                {
                    visited[Q.front()+1] = true;
                    Q.push(Q.front()+1);
                    distance[b[i]][Q.front()+1] = bfs;
                }
                Q.pop();
            }
        }
    }

    for(int i=0;i<check_points;i++)
    {
        cout<<endl<<"Shortest distance from point "<<b[i]<<"are :"<<endl;
        for(int j=0;j<check_points;j++)
            cout<<b[j]<<": "<<TSP[b[i]][b[j]]<<" ";
        cout<<endl;
    }
    cout<<"checkpoints  = "<<check_points<<endl;
    int temp;
    for(int i=0;i<check_points;i++)
    {
        if(b[i]==start_state)
        {
            temp = b[i];
            b[i] = b[0];
            b[0] = temp;
        }
        if(b[i]==final_state)
        {
            temp = b[i];
            b[i] = b[check_points-1];
            b[check_points-1] = temp;
        }
    }

    cout<<"CHECKPOINTS ARE: ";
    for(int i=0;i<check_points;i++)
        cout<<b[i]<<" ";
    cout<<endl;
    int bitmask = 1,min,max_bitmask = pow(2,check_points)-1;
    string binary;
    vector<int> v;
    int opt_dist[max_bitmask+10][check_points+1];
    while(bitmask <= max_bitmask)
    {
        binary = DecToBin(bitmask);
        cout<<"binary= "<<binary<<endl;
        v.clear();
        for(int i=binary.length()-1;i>=0;i--)
        {
            if(binary[i]=='1')
                v.push_back(binary.length()-i-1);
        }
        opt_dist[bitmask][0] = INFINITE;
        opt_dist[1][0] = 0;
        for(int i=1;i<v.size();i++)
        {
            min = INFINITE;
            for(int j=0;(v[j]!=v[i] && j<v.size());j++)
            {
                cout<<"TSP is: "<<TSP[b[v[j]]][b[v[i]]]<<endl;
                cout<<"opt_dist IS: "<<opt_dist[bitmask-(int)pow(2,v[i])][v[j]]<<endl;
                temp = opt_dist[bitmask-(int)pow(2,v[i])][v[j]] + TSP[b[v[j]]][b[v[i]]];
                if(temp<min)
                    min = temp;
            }
            opt_dist[bitmask][v[i]] = min;
            cout<<"bitmask = "<<bitmask<<" destin = "<<v[i]<<" so output is: "<<min<<endl;
        }
        bitmask+=2;
    }
    if(opt_dist[max_bitmask][check_points-1]==INFINITE || opt_dist[max_bitmask][check_points-1]==0)
        cout<<"-1"<<endl;
    else
        cout<<opt_dist[max_bitmask][check_points-1]<<endl;
    return;
}

int main(int argc, char* argv[])
{
    Orienteering o;
    o.main();
    return 0;
}
