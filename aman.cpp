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
    string DecToBin(int number);
    int point(int x_coordinate,int y_coordinate,int width);
    void add_edge(int source,int destination);
};

string Orienteering::DecToBin(int number)               /*******Decimal to binary conversion************/
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return DecToBin(number / 2) + "0";
    else
        return DecToBin(number / 2) + "1";
}


void Orienteering::add_edge(int source,int destination)   /*******connect two vertices in graph********/
{
    connect[source][destination] = 1;
    return;
}

int Orienteering::point(int x_coordinate,int y_coordinate,int width)   /*******return point for cartesian point********/
{
    return ((x_coordinate-1)*width + y_coordinate);
}

void Orienteering::main()                               /**********main funcion starts here!!***********/
{
    int check_points = 0,start_state,final_state;
    int width,height,non_empty_states = 0;
    bool visited[10001]={0},ischeckpoint[10001]={0};
    cin>>width>>height;                             //standard input
    int size = width*height;size++;
    int* b = new int[size];
    int* non_empty = new int[size];

//    int b[size],non_empty[size];
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
                    ischeckpoint[point(i,j+1,width)] = true;        //marks point as checkpoint('S' || 'G' || '@')
                    check_points++;
                    if(A[i][j]=='S')
                        start_state = point(i,j+1,width);           //start point 'S'
                    else if(A[i][j]=='G')
                        final_state = point(i,j+1,width);           //final(goal) point 'G'
                }
                else                                                //blank point or wall (#)
                {
                    non_empty[non_empty_states] = point(i,j+1,width);
                    non_empty_states++;
                    ischeckpoint[point(i,j+1,width)] = false;
                }
                if(j>0 && A[i][j-1]!='#'){
                    add_edge(point(i,j+1,width) , point(i,j,width));        //connection with left neighbour is established
     //               cout<<point(i,j+1,width)<<","<<point(i,j,width)<<" connected"<<endl;
                }
                if(j<(width-1) && A[i][j+1]!='#'){                          //connection with right neighbour is established
                    add_edge(point(i,j+1,width) , point(i,j+2,width));
     //               cout<<point(i,j+1,width)<<","<<point(i,j+2,width)<<" connected"<<endl;
                }
                if(i>1 && A[i-1][j]!='#'){                                  //connection with upper neighbour is established
                    add_edge(point(i,j+1,width) , point(i-1,j+1,width));
     //               cout<<point(i,j+1,width)<<","<<point(i-1,j+1,width)<<" connected"<<endl;
                }
                if(i<height && A[i+1][j]!='#'){                             //connection with bottom neighbour is established
                    add_edge(point(i,j+1,width) , point(i+1,j+1,width));
     //               cout<<point(i,j+1,width)<<","<<point(i+1,j+1,width)<<" connected"<<endl;
                }
            }
        }
    }

    int** distance = new int*[size];
    for(int i = 0; i < size; ++i)
        distance[i] = new int[size];
    int** TSP = new int*[size];
    for(int i = 0; i < size; ++i)
        TSP[i] = new int[size];
    int bfs;//,distance[size][size],TSP[size][size];
    for(int i=0;i<check_points;i++)
    {
        for(int j=0;j<check_points;j++)
            TSP[b[i]][b[j]] = INFINITE;
    }
    for(int i=0;i<check_points;i++)
    {
        for(int j=0;j<non_empty_states;j++)
            visited[non_empty[j]] = false;                  //initialize every checkpoint as unvisited(required to construct complete graph of checkpoints)
        queue<int> Q;                                       //BFS starts here so we are using queue data structure
        Q.push(b[i]);Q.push(-1);                            // -1 used as dummy variable which increases depth by 1 from source vertex
        visited[b[i]] = true;
        bfs = 0;                                            //initialize depth from source vertex as 0
        distance[b[i]][b[i]] = bfs;
        TSP[b[i]][b[i]] = 0;                                //TSP array is used to store shortest distance b/w any 2 checkpoints
        while(Q.size()>1)
        {
            if(Q.front()==-1)                               // -1 used as dummy variable which increases depth by 1 from source vertex
            {
                //cout<<"bfs="<<bfs<<endl;
                bfs++;                                      //depth increased by 1;
                Q.pop();                                    //-1 popped and pushed
                Q.push(-1);
            }
            else if(Q.front()!=-1)
            {
   //             cout<<"Q.front is: "<<Q.front()<<endl;
                if(ischeckpoint[Q.front()]  && Q.front()!=b[i])     //TSP array is used to store shortest distance b/w any 2 checkpoints
                        TSP[b[i]][Q.front()] = bfs;
                if(Q.front()>width && connect[Q.front()][Q.front()-width]==1 && !visited[Q.front()-width])
                {                                                   //connects with top neighbour non empty state
                    visited[Q.front()-width] = true;
                    Q.push(Q.front()-width);                        //mark visited so that again when visited not pushed into queue
                    distance[b[i]][Q.front()-width] = bfs;
                }
                if(Q.front()<=(width*(height-1)) && connect[Q.front()][Q.front()+width]==1 && !visited[Q.front()+width])
                {                                                   //connects with bottom neighbour non empty state
                    visited[Q.front()+width] = true;
                    Q.push(Q.front()+width);                        //mark visited so that again when visited not pushed into queue
                    distance[b[i]][Q.front()+width] = bfs;
                }
                if(Q.front()%width!=1 && connect[Q.front()][Q.front()-1]==1 && !visited[Q.front()-1])
                {                                                   //connects with left neighbour non empty state
                    visited[Q.front()-1] = true;
                    Q.push(Q.front()-1);                            //mark visited so that again when visited not pushed into queue
                    distance[b[i]][Q.front()-1] = bfs;
                }
                if(Q.front()%width!=0 && connect[Q.front()][Q.front()+1]==1 && !visited[Q.front()+1])
                {                                                   //connects with right neighbour non empty state
                    visited[Q.front()+1] = true;
                    Q.push(Q.front()+1);                            //mark visited so that again when visited not pushed into queue
                    distance[b[i]][Q.front()+1] = bfs;
                }
                Q.pop();                                            //popped bcoz no more neighbours present
            }
        }
    }
    delete[] distance;
    /*
    for(int i=0;i<check_points;i++)
    {
        cout<<endl<<"Shortest distance from point "<<b[i]<<"are :"<<endl;
        for(int j=0;j<check_points;j++)
            cout<<b[j]<<": "<<TSP[b[i]][b[j]]<<" ";
        cout<<endl;
    }
    */
    //cout<<"checkpoints  = "<<check_points<<endl;
    int temp;                                                       //this newer graph is an complete graph so redefining points is necessary
    for(int i=0;i<check_points;i++)                                //redefines points in newer reduced graph consisting of check_points only
    {
        if(b[i]==start_state)
        {
            temp = b[i];
            b[i] = b[0];                                            //initial state is put on 0th index
            b[0] = temp;
        }
        if(b[i]==final_state)
        {
            temp = b[i];                                            //initial state is put on (check_points-1)th index
            b[i] = b[check_points-1];
            b[check_points-1] = temp;
        }
    }

    /*
    cout<<"CHECKPOINTS ARE: ";
    for(int i=0;i<check_points;i++)
        cout<<b[i]<<" ";
    cout<<endl;
    */
//    cout<<"DJAVDJAVDJAVJDVAJDBJ "<<TSP[b[1]][b[2]]<<endl;
    delete[] non_empty;
    int bitmask = 1;                                                //bitmask used for subset of all points indicates which all states present in subset
    int min;
    long long int max_bitmask = pow(2,check_points)-1;                    //here dynamic programming algorithm is used
    string binary;                                                  //bit masking is used
    vector<int> v;
    int opt_dist[max_bitmask+10][check_points+1];                   //opt_dist array used for memorizing subset(1st cell) on transition till state k(2nd cell)
    while(bitmask <= max_bitmask)                                   //max_bitmask indicates that subset contains all check_points states
    {
        binary = DecToBin(bitmask);                                 //binary number tells that '1' means corresponding state present else absent
    //    cout<<"binary= "<<binary<<endl;
        v.clear();
        for(int i=binary.length()-1;i>=0;i--)
        {
            if(binary[i]=='1')
                v.push_back(binary.length()-i-1);                   //subset construction only those points pusshed into vector v
        }
        opt_dist[bitmask][0] = INFINITE;                            //ending on initial state costs infinite units
        opt_dist[1][0] = 0;                                         //state 0 to state 0 costs 0 units
        for(int i=1;i<v.size();i++)
        {
            min = INFINITE;
            for(int j=0;j<v.size();j++)             //for all subsets S ⊆ {0,1,2,...,check_points-1} and containing 0:
            {
                if(j==i) continue;
    //            cout<<"TSP is: "<<TSP[b[v[j]]][b[v[i]]]<<endl;
    //            cout<<"opt_dist IS: "<<opt_dist[bitmask-(int)pow(2,v[i])][v[j]]<<endl;
                temp = opt_dist[bitmask-(int)pow(2,v[i])][v[j]] + TSP[b[v[j]]][b[v[i]]];   //dp recurrence used and memoizing subsets move to state k
                if(temp<min)
                    min = temp;
            }
            opt_dist[bitmask][v[i]] = min;                              //subset corresponding to bitmask move to v[i] and min distance is memorized
   //         cout<<"bitmask = "<<bitmask<<" destin = "<<v[i]<<" so output is: "<<min<<endl;
        }
        bitmask+=2;
    }
    if(opt_dist[max_bitmask][check_points-1]==INFINITE || opt_dist[max_bitmask][check_points-1]==0)     //no such path exists
        cout<<"-1"<<endl;
    else                                                                            //outputs shortest distance from 'S' to 'G' to standard output
        cout<<opt_dist[max_bitmask][check_points-1]<<endl;
    return;
}


//main function starts here!!!
int main(int argc, char* argv[])
{
    Orienteering o;
    o.main();
    return 0;
}

