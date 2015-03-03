#include<algorithm>
#include<vector>
#include<iostream>
#include<stdio.h>
#include<string>
#include<math.h>
#include<stdlib.h>
#include<stack>
using namespace std;
int p=0;
int dfa_states;
#define BLANK ' '
#define TAB '\t'
#define MAX 500

vector <int> a[100][5];
vector<int> dfa_initial;
vector<int> dfa_final;

int DTable[100][3],num=0;
int state = 0,initial,Final;

void push(long int symbol);
long int pop();
string infix_to_postfix();
int priority(char symbol);
int isEmpty();
int white_space(char);
char infix[MAX], postfix[MAX];
long int Stack[MAX];
int top;


struct state_return{
int start;
int accept;
};


int count=0;
// Function to convert Infix expression to postfix
string InfixToPostfix(string expression);
// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(char operator1, char operator2);
// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);
// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
bool IsOperand(char C);
string infix_modifier(string exp)
{
    for(int i=0;i<exp.size();i++)
    {
        if(exp[i]=='a' ||exp[i]=='b' )
        {
            if(exp[i+1]=='('|| exp[i+1]=='a'||exp[i+1]=='b')
            {
                exp.insert(i+1,"x");
            }
        }
        else if(exp[i]==')'||exp[i]=='*')
        {
           if(exp[i+1]=='a' ||exp[i+1]=='b'||exp[i+1]=='(' )
           {
                exp.insert(i+1,"x");
           }
        }
    }
    return exp;
}

// Function to evaluate Postfix expression and return output
string InfixToPostfix(string exp)
{
    string expression = infix_modifier(exp);
    stack<char> S;
    string postfix = ""; // Initialize postfix as empty string.
    const int size = expression.length();
    for(int i = 0;i<size;i++)
    {
        if(expression[i] == ' ' || expression[i] == ',') continue;
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if(IsOperator(expression[i]))
        {//	count =0;
            if(expression[i]=='*')
            {
                postfix+= '*';
                continue;
            }
            while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(),expression[i]))
            {
                postfix+= S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
        // Else if character is an operand
        else if(IsOperand(expression[i]))
        {
            postfix +=expression[i];
        }
        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }
        else if(expression[i] == ')')
        {
            while(!S.empty() && S.top() != '(')
            {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }
    while(!S.empty())
    {
        postfix += S.top();
        S.pop();
    }
    return postfix;
}
// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand(char C)
{
    // if(C >= '0' && C <= '9') return true;
    if(C >= 'a' && C <= 'b') return true;
    // if(C >= 'A' && C <= 'Z') return true;
    return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
// if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
    if(C == '+' || C == 'x' || C == '*' || C == '|')
        return true;
    return false;
}

// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op)
{
    if(op == '$') return true;
        return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
    int weight = -1;
    switch(op)
    {
        case '|':
        weight = 1;
        case 'x':
        weight = 2;
        case '*':
        weight = 3;
        break;
    }
    return weight;
}
// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);
    // If operators have equal precedence, return true if they are left associative.
    // return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    if(op1Weight == op2Weight)
    {
    if(IsRightAssociative(op1)) return false;
    else return true;
    }
    return op1Weight > op2Weight ? true: false;
}

void trans(int s,int c,int t)
{
    if(!a[s][c].size())
    {
        a[s][c].push_back(t);
        return;
    }
    for(int i=0;i<a[s][c].size();i++)
    {
        if(a[s][c][i]==t)
        {
            return;
        }
        a[s][c].push_back(t);
        return;
    }
}


struct
state_return cleane_closure(char ch)
{
    int st1=state;state++;
    int st2=state;state++;
    int st3=state;state++;
    int st4=state;state++;

    trans(st1,0,st2);trans(st1,0,st4);
    if(ch=='E') trans(st2,0,st3);
    else if(ch=='a') trans(st2,1,st3);
    else if(ch=='b') trans(st2,2,st3);
    trans(st3,0,st2);trans(st3,0,st4);
    state_return st;
    st.start = st1;st.accept = st4;
    return st;
}

struct
state_return single_character(char ch)
{
    int st1 = state;state++;
    int st2 = state;state++;
    if(ch=='E') trans(st1,0,st2);
    else if(ch=='a') trans(st1,1,st2);
    else if(ch=='b') trans(st1,2,st2);
    state_return st;
    st.start = st1;st.accept = st2;
    return st;
}

void
connect(int Final_1,int initial_2)
{
    trans(Final_1,0,initial_2);
    return;
}

stack<state_return> S;

void nfa(string postfix)
{
    int already=0,st1,st2,st3,st4;
    for(int i=0;i<postfix.length();i++)
    {
        if(postfix[i]=='a' || postfix[i]=='b' || postfix[i]=='E')
        {
            state_return st = single_character(postfix[i]);
            S.push(st);
        }
        else if(postfix[i]=='|')
        {
            state_return s1 = S.top();S.pop();
            state_return s2 = S.top();S.pop();
            int in = state;state++;
            int fin = state;state++;
            trans(in,0,s1.start);trans(in,0,s2.start);
            trans(s1.accept,0,fin);trans(s2.accept,0,fin);
            state_return s;
            s.start = in;
            s.accept = fin;
            S.push(s);
        }
        else if(postfix[i]=='x')
        {
            state_return s1 = S.top();S.pop();
            state_return s2 = S.top();S.pop();
            trans(s2.accept,0,s1.start);
            state_return s;
            s.start = s2.start;
            s.accept = s1.accept;
            S.push(s);
        }
        else if(postfix[i]=='*')
        {
            state_return s1 = S.top();S.pop();
            int in = state;state++;
            int fin = state;state++;
            trans(in,0,s1.start);trans(s1.accept,0,fin);trans(s1.accept,0,s1.start);trans(in,0,fin);
            state_return s;
            s.start = in;
            s.accept = fin;
            S.push(s);
        }
    }
    state_return s = S.top();S.pop();
    initial = s.start;
    Final = s.accept;
}


void transition_table_nfa()
{
    cout<<"Initial State Is: "<<initial<<endl;
    cout<<"Final State Is: "<<Final<<endl;;
    for(int i=0;i<state;i++)
    {
        cout<<"Transitions for state "<<i<<" are:"<<endl;
        cout<<"On input 'E': {";
        for(int j=0;j<a[i][0].size();j++)
            cout<<a[i][0][j]<<", ";
        cout<<"}"<<endl;
        cout<<"On input 'a': {";
        for(int j=0;j<a[i][1].size();j++)
            cout<<a[i][1][j]<<", ";
        cout<<"}"<<endl;
        cout<<"On input 'b': {";
        for(int j=0;j<a[i][2].size();j++)
            cout<<a[i][2][j]<<", ";
        cout<<"}"<<endl;
    }
}


vector<int> epsilon_closure(int s)
{
    vector<int> v1;
    v1.push_back(s);
    stack<int> St;
    St.push(s);
    bool visited[state+2];
    for(int i=0;i<state;i++)
        visited[i] = false;
    visited[s] = true;
    int temp = St.top();
    while(true)
    {
        int i=0;
        while(i<a[temp][0].size())
        {
            if(!visited[a[temp][0][i]])
            {
                St.push(a[temp][0][i]);
                v1.push_back(a[temp][0][i]);
                visited[a[temp][0][i]] = true;
                i=0;
                temp = St.top();
                continue;
            }
            i+=1;
        }
        St.pop();
        if(St.size()) temp = St.top();
        if(!St.size()) break;
    }
    return v1;
}


void print_epsilon_closure(int s)
{
    vector<int> v2 = epsilon_closure(s);
    for(int i=0;i<v2.size();i++)
        cout<<v2[i]<<" ";
    return;
}


vector<int> epsilon_move_set(vector<int> v,char ch)
{
    vector<int> S;
    int n;
    bool visited[state];
    for(int i=0;i<state;i++)
        visited[i] = false;
    if(ch=='a') n = 1;
    else if(ch=='b') n = 2;
    for(int i=0;i<v.size();i++)
    {
        if(a[v[i]][n].size())
        {
            if(!visited[a[v[i]][n][0]])
            {
                vector<int> ep = epsilon_closure(a[v[i]][n][0]);
                for(int j=0;j<ep.size();j++)
                {
                    if(!visited[ep[j]])
                        S.push_back(ep[j]);
                    visited[ep[j]] = true;
                }
                visited[a[v[i]][n][0]] = true;
            }
        }
    }
    return S;
}

bool compare(vector<int> J,vector<int> K)
{
    if(J.size()!=K.size())
        return false;
    sort(J.begin(), J.begin()+J.size());
    sort(K.begin(), K.begin()+K.size());
    for(int i=0;i<J.size();i++)
    {
        if(J[i]!=K[i])
            return false;
    }
    return true;
}

void nfa_to_dfa()
{
    for(int i=0;i<100;i++)
    {
        for(int j=1;j<=2;j++)
            DTable[i][j] = -1;
    }
    cout<<"Initial State in NFA was: "<<initial<<endl;
    vector <vector <int> > V;
    V.push_back(epsilon_closure(initial));
    cout<<"epsilon closure of start state :";
    for(int i=0;i<V[0].size();i++)
        cout<<V[0][i]<<" ";
    for(int i=0;i<V[0].size();i++)
    {
        if(V[0][i]==initial)
            dfa_initial.push_back(0);
        if(V[0][i]==Final)
            dfa_final.push_back(0);
    }
    num++;
    int a1=0,a2=0;
    for(int i=0;i<num;i++)
    {
        a1=0;a2=0;
        vector<int> B = epsilon_move_set(V[i],'a');
        cout<<endl;
        for(int I=0;I<B.size();I++)
            cout<<B[I]<<" ";
        vector<int> C = epsilon_move_set(V[i],'b');
        cout<<endl;
        for(int I=0;I<C.size();I++)
            cout<<C[I]<<" ";
        for(int j=0;j<num;j++)
        {
            if(compare(B,V[j]) && B.size()!=0)
            {
                a1 = 1;
                DTable[i][1] = j;
            }
            if(compare(C,V[j]) && C.size()!=0)
            {
                a2 = 1;
                DTable[i][2] = j;
            }
        }
        if(!a1 && B.size()!=0)
        {
            V.push_back(B);
            for(int j=0;j<V[num].size();j++)
            {
                if(V[num][j]==initial)
                    dfa_initial.push_back(num);
                if(V[num][j]==Final)
                    dfa_final.push_back(num);
            }
            DTable[i][1] = num;
            num++;
        }
        if(!a2 && C.size()!=0)
        {
            V.push_back(C);
            for(int j=0;j<V[num].size();j++)
            {
                if(V[num][j]==initial)
                    dfa_initial.push_back(num);
                if(V[num][j]==Final)
                    dfa_final.push_back(num);
            }
            DTable[i][2] = num;num++;
        }
    }
    return;
}


void transition_table_dfa()
{
    cout<<endl<<endl<<"Transition Table for corresponding DFA is as follows:"<<endl;
    cout<<"Initial State for DFA Is: ";
    for(int i=0;i<dfa_initial.size();i++)
        cout<<dfa_initial[i]<<" ";
    cout<<endl<<"Final State for DFA Is: ";
    for(int i=0;i<dfa_final.size();i++)
        cout<<dfa_final[i]<<" ";
    cout<<endl;
    for(int i=0;i<num;i++)
    {
        cout<<"Transitions for state "<<i<<" are:"<<endl;
        cout<<"On input 'a': {";
        if(DTable[i][1]!=-1)
            cout<<DTable[i][1]<<", ";
        cout<<"}"<<endl;
        cout<<"On input 'b': {";
        if(DTable[i][2]!=-1)
            cout<<DTable[i][2]<<", ";
        cout<<"}"<<endl;
    }
}


bool check_point_in_vector(vector<int> v,int i)
{
    for(int j=0;j<v.size();j++)
    {
        if(v[j]==i)
            return true;
    }
    return false;
}

void minimize_dfa()
{
    vector <vector <int> > D;
    vector<int> v1,v2;
    v1.push_back(Final);
    for(int i=0;i<num;i++)
    {
        if(i!=Final)
            v2.push_back(i);
    }
    D.push_back(v1);
    D.push_back(v2);
    dfa_states = 2;
    for(int i=0;i<dfa_states;i++)
    {
        int found = 1,a1;
        if(D[i].size()>1)
        {
            for(int j=0;j<D[i].size();j++)
            {
                if(!check_point_in_vector(D[i],DTable[D[i][j]][1]) || !check_point_in_vector(D[i],DTable[D[i][j]][2]))
                {
                    found = 0;
                    a1 = j;
                }
                if(!found)
                {
                    D[i].erase(D[i].begin()+j);
                    D[dfa_states].push_back(D[i][a1]);
                    dfa_states++;
                }
            }
        }
    }
    for(int i=0;i<dfa_states;i++)
    {
        if(D[i].size()>1)
        {
            int state_for_a = DTable[D[i][0]][1];
            int state_for_b = DTable[D[i][0]][2];
            for(int j=1;j<D[i].size();j++)
            {
                DTable[D[i][j]][1] = state_for_a;
                DTable[D[i][j]][2] = state_for_b;
            }
        }
    }
}


bool simulation(string input,vector<int> ini,vector<int> fin)
{
    if(input=="E")
        return false;
    int pst_state = ini[0],val;
    for(int i=0;i<input.size();i++)
    {
        if(input[i]=='a')
            val=1;
        else
            val=2;

        if(DTable[pst_state][val]==-1)
            return false;
        pst_state = DTable[pst_state][val];
    }
    for(int i=0;i<fin.size();i++)
    {
        if(fin[i]==pst_state)
            return true;
    }
    return false;
}




/*****************************************Main Function Implementation******************************/

int main()
{
    string re;
    cout<<"Enter RE: "<<endl;
    cin>>re;
    string reg = InfixToPostfix(re);
    cout<<"Postfix representation is: "<<reg<<endl;
    nfa(reg);
    transition_table_nfa();
    cout<<endl;
    nfa_to_dfa();
    transition_table_dfa();
    string inp;
    cin>>inp;
    if(simulation(inp,dfa_initial,dfa_final))
        cout<<"Accepted"<<endl;
    else
        cout<<"Not Accepted"<<endl;
    return 0;
}
