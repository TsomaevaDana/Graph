#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>


using namespace std;






/*double laplace(double x) {
    return 0.5 * erf(x / sqrt(2.0));
}

double plot_ver(double x)
{
    double a = 1.0 / (a * sqrt(2.0 * M_PI));
    double b = exp (-((x - m) * (x - m)) / (2.0 * a * a));
    double c = exp (-((x + m) * (x + m)) / (2.0 * a * a));

    return a*(b+c);
}

double rasp_f(int x)
{
    return laplace(((x-m)/a)) + laplace(((x+m)/a));
}
*/

//стандартное нормальное распределение
int mu=0;
int om=1;

mt19937 gen(time(0));

normal_distribution<double> d(mu, om);

//отраженное норм распределение

vector<int> make_random(int n,double a,double m)
{  
    vector<int> r;
    for(int i =0; i<n;i++)
    {
        double u = d(gen);
        r.push_back(round(abs(m+a*u)));
    }

    //for (int d : r) cout << d << " ";
    //cout<<endl;
    return r;
}

 int summ(vector<int> d)
    {
        int r =0;
        for(int i = 0; i < d.size(); i++)
        {
            r+= d[i];
        }
        return r;
    }

    void print_matrix(vector<vector<int>>a)
    {
        int n = a.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(a[i][j]==0 && i!=j)  cout<< " " << "-" << " ";
                else cout<< " " << a[i][j] << " ";
            }
            cout<<endl;
        }
    }

    vector<vector<int>> add_matrix(vector<vector<int>>a,vector<vector<int>>b)
    {
        int n = a.size();
        vector<vector<int>> r = a;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                r[i][j] = a[i][j] + b[i][j];
            }
        }
        return r;
    }
  
  

    vector<int> sorter(vector<int> a) 
    {
        vector<int> d =a;
        int n = d.size();
        bool wasswp;
        for (int i = 0; i < n-1; i++) {
            wasswp = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (d[j] < d[j + 1]) {
                    swap(d[j], d[j + 1]);
                    wasswp = true;
                }
            }
            if (!wasswp) break;
        }

        return d;
    }

    

bool check_degrees (vector<int> d)
    {
        int n =d.size();
        if(summ(d) != 2 * (n-1)) return 0;
        vector<int> sort_d = sorter(d);

        if(sort_d[n-1] > (n-1)) return 0;

        for(int i = 0; i < n-1 ; i++)
        {
            if(sort_d[i] == 0) return 0;
            if(sort_d[i]<sort_d[i+1]) return 0;
        }
        if(sort_d[n-1] == 0) return 0;
        
        return 1;
    }


bool check_two(vector<int> d)
{
    int n =d.size();
    if(summ(d) % 2 !=0) return 0;
    vector<int> sort_d = sorter(d);

    for(int i =0;i<d.size();i++)
    {
        if(sort_d[i]==0) return 0;
    }
    
    for(int i =0;i<d.size();i++)
    {
        int s =sort_d[i];
        if(s >= d.size()-i) return 0;
        sort_d[i]=0;
        if(s == 0) continue;
        for(int j =i+1;j<d.size();j++)
        {
            s-= 1;
            sort_d[j]-=1;
            if(s<=0) break;
        }
        if(s>0) return 0;
    }
    int s = 0;
    for(int i =0;i<d.size();i++)
    {
        s+=sort_d[i];
        
    }
    if(s%2!=0)return 0;
    return 1;

}


    vector<vector<int>> shibl(vector<vector<int>> a, vector<vector<int>> b, int m = 0)
    {

        vector<vector<int>> result(a.size(), vector<int>(a[0].size(), 0));
        int mode = 0;
        if(m==1) mode = 1000000;
        for(int i =0; i<a[0].size();i++)
        {

            for(int j = 0; j <a[0].size(); j ++)
            {
                int r =0;
                int mult=mode;
                
                for(int k = 0 ; k < a[0].size() ; k++)
                {
                    //cout<<mult<<endl;
                    int res = a[i][k]+b[k][j];
                    if(a[i][k] == 0|| b[k][j]==0) res = 0;
                    //if(k==0 ) mult=res;
                    else  
                    {
                        if(m==0)mult = max(mult, res);
                        else mult = min(mult, res);
                    }
                }

                if(mult != mode) result[i][j]=mult;
            }
        }
        return result;
    }


    vector<vector<int>> mat_mul(vector<vector<int>> a, vector<vector<int>> b)
    {

        vector<vector<int>> result(a.size(), vector<int>(a[0].size(), 0));
        int mult = 0;
        for(int i =0; i<a[0].size();i++)
        {

            for(int j = 0; j <a[0].size(); j ++)
            {
                int r =0;
                
                for(int k = 0 ; k < a[0].size() ; k++)
                {
                    //cout<<mult<<endl;
                     r += a[i][k]*b[k][j];
                }

                    result[i][j]= r;
            }
        }
        return result;
    }

//ДОБАВИТЬ СЛОЖЕНИЕ!!!!!!!!!!!!!!!!!!!!!!!!



struct node
{
    int degree;
    int id;

    node(int i, int d)
    {
        degree = d;
        id = i;
    }
};

struct edge
{
    int fst_id; // может заменить на индексы в массиве векршин???
    int snd_id;
    int weight;
    int orientation = 0; //-1 left 1 right

    edge(int f, int s, int w, int o = 0)
    {
        fst_id = f;
        snd_id = s;
        weight = w;
        orientation = o;

    }
};

vector<node> sorter_node(vector<node> a) 
    {
        vector<node> d =a;
        int n = d.size();
        bool wasswp;
        for (int i = 0; i < n-1; i++) {
            wasswp = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (d[j].degree < d[j + 1].degree) {
                    swap(d[j], d[j + 1]);
                    wasswp = true;
                }
            }
            if (!wasswp) break;
        }

        return d;
    }
class Graph
{
    vector<node> v;

    vector<edge> e;

    vector<vector<int>> matrix;
    vector<vector<int>> ed;

    bool orien =0;

    int n ;

    int m = 1;
    int o =4;

    public:
    
    Graph(int n1) { n = n1;}

    vector<vector<int>> get_m()
    {
        return matrix;
    }
    bool acicle_check ()
    {
        return (v.size() - e.size()) == 1;
    }

    void add_node(int i,int d)
    {
        
        v.push_back(node(i,d));
    }

    void add_edge(int f, int s, int w, int o = 0)
    {
        e.push_back(edge(f, s, w, o ));
    }

   
    void make_nodes()
    {    
        o=n/2;
         
        vector<int> degrees = make_random(n,o,m);
        while(!check_degrees(degrees)) {degrees= make_random(n,o,m);}
        for (int d : degrees) cout << d << " ";
        cout << endl;
    
        
        for(int i = 0; i < n; i++)
        {
            //cin>> d;
            add_node(i,degrees[i]);
        }

        //cout<<"done\n";
    }

    void make_nodes_ori()
    {   
        m=n/2;
        o=n/3;
        v.clear();
         
        vector<int> degrees = make_random(n,o,m);
        while(!check_two(degrees)) {degrees= make_random(n,o,m);}
        for (int d : degrees) cout << d << " ";
        cout << endl;
    
        
        for(int i = 0; i < n; i++)
        {
            //cin>> d;
            add_node(i,degrees[i]);
        }

        //cout<<"done\n";
    }

    bool make_matrix()
    {
        matrix.resize(n, vector<int>(n, 0));
        vector<node> v_help = sorter_node(v);
        vector<node>  temp ;
        int save;
        for (int i = 0; i < n; i++) 
        {
            if (v_help[i].degree == 0) continue;
            
            int deg = v_help[i].degree;
            
            int dop=2;
            //if(i>1) dop = temp[i].degree;

            for (int j = i+1; j < n && deg > 0; j++) {
                if (v_help[j].degree > 0) {
                    bool been =0;
                    for(int k =0; k < temp.size();k++)
                    {
                        if(v_help[j].id == temp[k].id) been =1;
                    }
                    if(been) continue;
                    int u = v_help[i].id;
                    int v = v_help[j].id;
                    matrix[u][v] = 1;
                    matrix[v][u] = 1;
                    
                    v_help[i].degree--;
                    v_help[j].degree--;
                    deg--;
                    dop=j;
                    temp.push_back(v_help[j]);
                }
            }
        }
        ed=matrix;
        //print_matrix(matrix);
        return 1;
    }

    void make_w()
    {   
        int count =0;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if(matrix[i][j]==1) count++;
            }
        }

    }


    bool make_matrix_ori()
    {
        orien = 1;
        matrix.resize(n, vector<int>(n, 0));
        for(int i =0;i<n;i++)
        {
            for(int j =0;j<n;j++)
            {
                matrix[i][j]=0;
            }
        }
        vector<node> v_help = sorter_node(v);
        vector<node>  temp ;

        for(int i =0;i<n;i++)
        {
            int s =v_help[i].degree;
            v_help[i].degree=0;
            if(s == 0) continue;
            for(int j =i+1;j<n;j++)
            {
                s-= 1;
                matrix[v_help[i].id][v_help[j].id] = 1;
                v_help[j].degree-=1;
                if(s<=0) break;
            }
        }
        //print_matrix(matrix);
        ed=matrix;
        return 1;
    }

   int find_exst(int v) {
        vector<vector<int>> dist = ed;
        vector<int> save(n, 0);
        v = v - 1;
        
        for (int i = 0; i < n; i++) {
            if (dist[v][i] > 0) {
                save[i] = dist[v][i];
            }
        }
        save[v] = 0; 

        for (int step = 2; step <= n-1; step++) {
            dist = shibl(dist, ed, 1);
            for (int i = 0; i < n; i++) {
                if (dist[v][i] != 0) {
                    if (save[i] == 0 || dist[v][i] < save[i]) {
                        save[i] = dist[v][i];
                    }
                }
            }
        }
        
        int max_dist = 0;
        bool any_reachable = false;
        for (int i = 0; i < n; i++) {
            if (i != v) {
                if (save[i] != 0) {
                    any_reachable = true;
                    max_dist = max(max_dist, save[i]);
                }
            }
        }
        if (!any_reachable) return 0;
        return max_dist;
    }

    bool check_matrix()
    {
    
         for (int i = 0; i < n-1; i++)
        {
            bool has_p=0;
            for (int j = i; j < n; j++)
            {
                if(i != j)
                {
                    int a = simplePaths(i+1,j+1);
                    int b = simplePaths(j+1,i+1);
                    if( a !=0 && b !=0) return 0;
                    if(a !=0 || b !=0) has_p = 1;
                }
                
            }
            if(has_p==0)return 0;
        }

        return 1;

    }

    bool check_matrix_fw()
    {

        vector<vector<int>> lenght;
        vector<vector<int>> paths;
        //int cnt = work->simplePaths_e(u, v);
        floid_w_alg(lenght,paths);
    
         for (int i = 0; i < n-1; i++)
        {
            bool has_p=0;
            for (int j = i; j < n; j++)
            {
                if(i != j)
                {
                    if( paths[i][j] !=0 && paths[j][i] !=0) return 0;
                    if( paths[i][j] !=0 || paths[j][i] !=0) has_p = 1;
                }
                
            }
            if(has_p==0)return 0;
        }

        return 1;

    }

    vector<int> find_all_exs()
    {
        vector<int> res;
        for(int i =0;i<n;i++)
        {
            res.push_back(find_exst(i+1));
        }
        return res;
    }


    vector<int> generate_o_n(int n1)
    {
        vector<int> r;
        for (int i = 0; i < n1; i++)
        {
            r.push_back(round(abs(d(gen))));
        }
        return r;
    }

 int simplePaths_e(int start, int& it_count, vector<vector<int>>& visited)
{
    start -= 1;
    it_count = 0;
    vector<int> path;
    vector<int> wait;
    
    DFS_edge(start, visited, path, it_count);
    int a = 0;
    //cout << "size: " << path.size() << endl;
    int co =0 ;
    if(path.size() == 0)
    {
        cout<< "C данной вершины не выходит ребер\n";
        return co;
    }
    //wait.push_back(path[0]);
    for (int i = 0; i < path.size() - 1; i+=2) {
        if(i>1) 
        {
            if(path[i] != path[i-2]){
                if(wait.size()!=0 && count(wait.begin(), wait.end(), path[i])) 
                {
                    for(int k =wait.size()-1; k>=0;k--)
                    {
                        
                        a--;
                        wait.pop_back();
                        if( path[i] == wait[k]) 
                        {
                            break;
                        }
                    }
                }
                else if (path[i] == start) a =0;
                else
                {
                    a+=1;
                    wait.push_back(path[i-2]);
                }
                
            }
        }
        for(int j =0; j<a; j++) cout<<"    ";
        cout << "ребро: " << path[i] + 1 << "-" << path[i + 1] + 1<<endl;
        co ++;

        
        
    }
    
    return co;
}

 int simplePaths(int start, int end) 
 {
    start-=1;
    end-=1;
    vector<bool> visited(n, false);
    int count = 0;
    DFS(start, end, visited, count);
    return count;
}

void DFS(int current, int target, vector<bool>& visited, int& count) 
{
    if (current == target) {
        count++;
        return;
    }
    visited[current] = true;
    for (int neighbor = 0; neighbor < n; neighbor++) {
        if (matrix[current][neighbor] != 0 && !visited[neighbor]) {   
            DFS(neighbor, target, visited, count);
        }
    }
    visited[current] = false;
}

vector<int> DFS_edge(int current, vector<vector<int>>& visited, vector<int>& path, int& it_count)
{
    for (int neighbor = 0; neighbor < n; neighbor++) {
        it_count++;
        if (current != neighbor && matrix[current][neighbor] != 0 && !visited[current][neighbor]) {
            visited[current][neighbor] = 1;
            if (!orien) visited[neighbor][current] = 1;
            
            path.push_back(current);
            path.push_back(neighbor);
            
            DFS_edge(neighbor, visited, path, it_count);

        }
    }
    return path;
}

vector<int> generate_weights(int n, int type) {
    vector<int> degrees ;
    bool c =1;
    do {
        c =1;
        degrees= make_random(n,o,m);
        for(int i : degrees) {if (i==0) c=0;}
    }while(c==0);

    if (type == 1) 
    {
        // Только положительные
       return degrees;
    } 
    else if (type == 2) 
    {
        // Только отрицательные
        for(int i =0;i<n;i++)
        {
            degrees[i] = -degrees[i];
        }
    }
    else 
    {  
        // Смешанные
        for(int i =0;i<n;i++)
        {
            int z = rand()%2;
            if(z==1) {degrees[i] = -degrees[i];}
            else {}
        }
        
    }
    return degrees;
}


/*

*/
void update_matrix(int mode,vector<vector<int>>& m)
{
    
    int count=0;
    for(int i =0;i<n;i++)
    {
        for(int j =0;j<n;j++)
        {
            if(m[i][j]==1) count++;
        }
    }
    vector<int> w = generate_weights(count,mode);
    count =0;
    int f =0;
    
    for(int i =0;i<n;i++)
    {
        if(orien == 0) f = i;
        for(int j =f;j<n;j++)
        {
            if(m[i][j]==1) 
            {
                m[i][j] = w[count];
                if(orien == 0)m[j][i] = w[count];
                count++;
            }
        }
    }

}

void update_matrix(int mode)
{
    int count=0;
    for(int i =0;i<n;i++)
    {
        for(int j =0;j<n;j++)
        {
            if(matrix[i][j]==1) count++;
        }
    }
    vector<int> w = generate_weights(count,mode);
    count =0;
    int f =0;
    
    for(int i =0;i<n;i++)
    {
        if(orien == 0) f = i;
        for(int j =f;j<n;j++)
        {
            if(matrix[i][j]==1) 
            {
                matrix[i][j] = w[count];
                if(orien == 0)matrix[j][i] = w[count];
                count++;
            }
        }
    }

}


//понять количесвто итераций 1000

int floid_w_alg(vector<vector<int>>& lenght, vector<vector<int>>& paths)
{
    vector<vector<int>> path_l = matrix;
    vector<vector<int>> path(n, vector<int>(n, 0));
    int iter_count=0;
    for(int i =0;i<n;i++)
    {
        //iter_count+=1;
        for(int j =0;j<n;j++)
        {
            if(matrix[i][j]!=0)path[i][j]=j+1;
            //iter_count+=1;
        }
    }
    cout<<"проверка алгоритма \n";

    
    for(int i =0;i<n;i++)
    {
        //cout<<i<<"-i\n";
         //iter_count+=1;
        for(int j =0;j<n;j++)
        {
            //iter_count+=1;
            //cout<<i<<"-j"<<matrix[i][j]<<"-mat "<<path_l[i][j]<<" "<<path_l[i][j]<<"\n";
            for( int k =0; k<n; k++)
            {
                iter_count+=1;
                if(i != j && i != k && path_l[j][i] != 0 && path_l[i][k] != 0)
                {
                    if((path_l[j][k] == 0 && k != j) || path_l[j][k] > path_l[j][i] + path_l[i][k])
                    {
                        path[j][k] = path[j][i];
                        path_l[j][k] = path_l[j][i] + path_l[i][k];
                    }
                }
            }
            //cout<<i<<"2  -j"<<matrix[i][j]<<"-mat "<<path_l[i][j]<<" "<<path_l[i][j]<<"\n";
        }
        for(int j =0;j<n;j++)
        {
            //iter_count+=1;
            if(path[i][j]<0) return 0;
        }
    }

    lenght = path_l;
    paths = path;
    return iter_count;

}   





};


bool find_path_fw(int a, int b, vector<vector<int>>& paths,vector<int>& path)
{
    if(a==b)return 1;
    if(paths[a-1][b-1]==0)return 0;
    path.push_back(paths[a-1][b-1]);
    return find_path_fw(paths[a-1][b-1],b,paths,path);

} 


int floid_w_alg_n(vector<vector<int>>& lenght, vector<vector<int>>& paths,vector<vector<int>> m)
{
    vector<vector<int>> path_l = m;
    int n = m.size();
    vector<vector<int>> path(n, vector<int>(n, 0));
    int iter_count=0;
    for(int i =0;i<n;i++)
    {
        //iter_count+=1;
        //cout<<i<<endl;
        for(int j =0;j<n;j++)
        {
            if(m[i][j]!=0)path[i][j]=j+1;
            //iter_count+=1;
        }
    }
    //cout<<"проверка алгоритма2 \n";

    
    for(int i =0;i<n;i++)
    {
        //cout<<i<<"-i\n";
         //iter_count+=1;
        for(int j =0;j<n;j++)
        {
            //iter_count+=1;
            //cout<<i<<"-j"<<matrix[i][j]<<"-mat "<<path_l[i][j]<<" "<<path_l[i][j]<<"\n";
            for( int k =0; k<n; k++)
            {
                iter_count+=1;
                if(i != j && i != k && path_l[j][i] != 0 && path_l[i][k] != 0)
                {
                    if((path_l[j][k] == 0 && k != j) || path_l[j][k] > path_l[j][i] + path_l[i][k])
                    {
                        path[j][k] = path[j][i];
                        path_l[j][k] = path_l[j][i] + path_l[i][k];
                    }
                }
            }
            //cout<<i<<"2  -j"<<matrix[i][j]<<"-mat "<<path_l[i][j]<<" "<<path_l[i][j]<<"\n";
        }
        for(int j =0;j<n;j++)
        {
            //iter_count+=1;
            if(path[i][j]<0) return 0;
        }
    }

    lenght = path_l;
    paths = path;
    return iter_count;

}   



void l3_3(int s, int is, vector<vector<int>> ca, vector<vector<int>> co, int tf)
{
    vector<vector<int>> b_co = co;
    while(b_co.size()!=ca.size()){
        b_co.push_back(vector<int>(b_co.size() + 1, 0));
        for(int i = 0; i < b_co.size(); i++) {
        
            if(ca[i][ca.size()-1]!=0) b_co[i].push_back(10000);
            else b_co[i].push_back(0);
        }
    }

    int f =0;
    int ic=0;
    vector<int> path;
    vector<vector<int>> b_co1=b_co;
    int sum_co=0;
    while(f != tf)
    {
        vector<vector<int>> lenght;
        vector<vector<int>> paths;
        path.clear();
        //int cnt = work->simplePaths_e(u, v);
        int it_c9 =floid_w_alg_n(lenght,paths,b_co);
        if(it_c9 ==0)
        {
            cout<<"Есть отрицательные пути!\n";
            break;
        }
        bool a = find_path_fw(is,s,paths,path);

     


        cout<<"\nFIRST!!\n";
        print_matrix(ca);
        cout<<endl;
        print_matrix(b_co);
        
         cout<<is;
    for(int i:path) cout<<"->"<<i;
    cout<<endl;

        int min_f=10000000;
        path.insert(path.begin(),is);
        for(int i =0;i<path.size()-1;i++)
        {
            if(ca[path[i]-1][path[i+1]-1] < min_f) min_f = ca[path[i]-1][path[i+1]-1];
            //cout<<ca[path[i]-1][path[i+1]-1]<<endl;
        }
        if(min_f > tf -f) min_f =  tf -f;
        f+=min_f;

        for(int i = 0; i < path.size()-1; i++) 
        {
            sum_co += co[path[i]-1][path[i+1]-1] * min_f;  
            cout << "Ребро " << path[i] << "->" << path[i+1] << ": +" << min_f << " ед.(цена ребра: " << co[path[i]-1][path[i+1]-1] << ")\n";
        }

        //cout<<"SECOND!! "<<min_f  <<"   f:"<< f <<" tf "<< tf;

        for(int i =0;i<path.size()-1;i++)
        {
            ca[path[i]-1][path[i+1]-1] -= min_f;
            ca[path[i+1]-1][path[i]-1] += min_f;
            if(ca[path[i]-1][path[i+1]-1]==0)b_co[path[i]-1][path[i+1]-1] =0;
            if(b_co[path[i+1]-1][path[i]-1]!= 10000) b_co[path[i+1]-1][path[i]-1] = -b_co[path[i]-1][path[i+1]-1];
        }

        cout<<"THIRD!!\n";
        print_matrix(ca);
        cout<<endl;
        print_matrix(b_co);
        ic+=1;
        //if(ic ==5) break;
    }
    for(int i:path) cout<<i<<"->";
    cout<<endl;

    
    /*for(int i =0;i<path.size()-1;i++)
    {
        if(b_co[path[i]-1][path[i+1]-1]!=10000)sum_co += b_co1[path[i]-1][path[i+1]-1];
    }*/

    cout<<"цена = "<<sum_co<<endl;



}


int input_check(int a, int b)
{
    int choice = a-1;
    int itr_c = 0;
    while(choice < a || choice > b)
    {
        if(itr_c>0) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Неверно! Выберете от "<< a<<" до " <<  b <<"! Введите снова\n";
        }
        cin>>choice;
        itr_c+=1;
    }

    return choice;
}


vector<vector<int>> FF_alg(int s, int t, vector<vector<int>> c, int n) 
{
    vector<vector<int>> F(n, vector<int>(n, 0));
    
    M:

    vector<int> S(n, 0);
    vector<int> N(n, 0);
    vector<int> sign(n, 0);
    vector<int> p_node(n, -1);
    vector<int> delta(n, 0);
    
    S[s] = 1;
    sign[s] = 1;
    p_node[s] = -1;
    delta[s] = 100000;
    
    int a;
    do 
    {
        a = 0;
        for (int v = 0; v < n; v++) 
        {
            if (S[v] ==1 && N[v]==0) 
            {
                for (int u = 0; u < n; u++) {
                    if (S[u] == 0 && F[v][u]<c[v][u]) 
                    {
                        S[u] = 1;
                        sign[u] = 1;
                        p_node[u] = v;
                        delta[u] = min(delta[v], c[v][u] - F[v][u]);
                        a = 1;
                    }
                }
                for (int u = 0; u < n; u++) 
                {
                    if (S[u] == 0 && F[u][v]> 0) 
                    {
                        S[u] = 1;
                        sign[u] = -1;
                        p_node[u] = v;
                        delta[u] = min(delta[v], F[u][v]);
                        a = 1;
                    }
                }
                N[v] = 1;
            }
        }

        if (S[t] !=0) 
        {
            int d = delta[t];
            int x = t;
            while (x != s) 
            {
                if (sign[x] == 1) 
                {
                    F[p_node[x]][x] += d;
                } 
                else 
                {
                    F[x][p_node[x]] -= d;
                }
                x = p_node[x];
            }
            goto M; 
        }
        
    } while (a != 0); 
    
    return F;
}








  

int main()
{
    srand(time(0));
    Graph g(0); 
    Graph g1(0);
    Graph* work=nullptr;
    bool graph_created1 = false;
    bool graph_created2 = false;
    bool is_oriented = false; 

    int it_c8=0;
    int it_c9=0;

    vector<vector<int>> ed_matr;

    vector<vector<int>> cost;
    vector<vector<int>> capacity;
    vector<vector<int>> big_capacity;
    int targetFlow;

    int m_stock;
    int m_istock;

    while (true) {
        
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Создать граф (ввести кол-во вершин, тип)\n";
        cout << "2. Посчитать эксцентриситеты, центр и диаметральные вершины\n";
        cout << "3. Сгенерировать весовую матрицу (выбрать тип весов)\n";
        cout << "4. Вывести матрицу.\n";
        cout << "5. Применить метод Шимбелла\n";
        cout << "6. Найти количество простых путей между двумя вершинами\n";
        cout << "7. Найти количество путей между двумя вершинами\n";
        cout << "=================================2  Лаба=========================================\n";
        cout << "8. Обход ребер в глубину.\n";
        cout << "9. Алгоритм Флойда-Уоршалла.\n";
        cout << "10. Количесвто итераций\n";
        cout << "=================================3  Лаба=========================================\n";
        cout << "11. Обновление матрицы\n";
        cout << "12. Поиск максимального потока\n";
        cout << "13. Поиск самого дешевого маршрута\n";
        cout << "14. Выход\n";
        cout << "Выбор: ";

        int choice = input_check(1, 14); 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                int n_vertices;
                cout << "Введите количество вершин (>=2): ";
                cin >> n_vertices;
                while (n_vertices < 2) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Неверно! Введите >=2: ";
                    cin >> n_vertices;
                }

                int orient;
                cout << "Тип графа: 1 - неориентированный, 2 - ориентированный: ";
                cin >> orient;
                while (orient != 1 && orient != 2) {
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Неверно! Введите 1 или 2: ";
                    cin >> orient;
                }
                is_oriented = (orient == 2);

                g = Graph(n_vertices);
                
                if(is_oriented) 
                {   do{
                        g.make_nodes_ori();
                        g.make_matrix_ori();
                    }while(!g.check_matrix_fw());  
                }
                else 
                {
                     g.make_nodes();
                    g.make_matrix();
                }

                graph_created1 = true;
                cout << "Граф успешно создан.\n";
                print_matrix(g.get_m()); 
                ed_matr = g.get_m();
                work = &g;
                break;
            }

            case 2: {
                 if (!graph_created1 && !graph_created2 ) {
                    cout << "Сначала создайте граф (пункт 1,4).\n";
                    break;
                }
                vector<int> ecc = work->find_all_exs();
                cout << "Эксцентриситеты вершин:\n";
                for (int i = 0; i < ecc.size(); ++i)
                    cout << "Вершина " << i+1 << ": " << ecc[i] << "\n";

                int min_ecc = 10000000;
                for(int i =0; i<ecc.size();i++)
                {
                    if(ecc[i]!=0 && ecc[i]<min_ecc) min_ecc=ecc[i];
                }
                cout << "Центр графа: ";
                for (int i = 0; i < ecc.size(); ++i)
                    if (ecc[i] == min_ecc) cout << i+1 << " ";
                cout << "\n";

                int max_ecc = *max_element(ecc.begin(), ecc.end());
                cout << "Диаметральные вершины: ";
                for (int i = 0; i < ecc.size(); ++i)
                    if (ecc[i] == max_ecc) cout << i+1 << " ";
                cout << "\n";
                break;
            }

            case 3: {
                
                int weight_type;
                cout << "Тип весов: 1 - только положительные, 2 - только отрицательные, 3 - смешанные: ";
                cin >> weight_type;
                while (weight_type < 1 || weight_type > 3) {
                    cout << "Неверно! Введите 1, 2 или 3: ";
                    cin >> weight_type;
                }
                work->update_matrix(weight_type);
                cout << "Веса присвоены. Матрица весов:\n";
                print_matrix(work->get_m());
                graph_created2=1;
                break;


            }

            case 4:
            {
                print_matrix(work->get_m());
                break;
            }

            case 5: {
                 if (!graph_created1 && !graph_created2 ) {
                    cout << "Сначала создайте граф (пункт 1,4).\n";
                    break;
                }
                
                int steps = work->get_m().size() - 1; 
                cout << "Напишите количество ребер в пути (от 0 до " << work->get_m().size() - 1 <<"): \n";
                cin >> steps;
                while (steps <0 || steps > work->get_m().size() - 1) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Неверно! Введите число (от 0 до " << work->get_m().size() - 1 <<"): \n";
                    cin >> steps;
                }
                vector<vector<int>> min_dist = work->get_m();
                vector<vector<int>> max_dist = work->get_m();

                for (int k = 2; k <= steps; ++k) {
                    min_dist = shibl(min_dist, work->get_m(), 1); // минимум
                    max_dist = shibl(max_dist, work->get_m(), 0); // максимум
                }

                if(steps==0)
                {
                    cout << "\nМинимальные расстояния (Шимбелл):\n";
                    print_matrix(vector<vector<int>>( work->get_m().size(), vector<int>( work->get_m().size(), 0)));
                    cout << "\nМаксимальные расстояния (Шимбелл):\n";
                    print_matrix(vector<vector<int>>( work->get_m().size(), vector<int>( work->get_m().size(), 0)));
                    break;
                }

                cout << "\nМинимальные расстояния (Шимбелл):\n";
                print_matrix(min_dist);
                cout << "\nМаксимальные расстояния (Шимбелл):\n";
                print_matrix(max_dist);
                break;
            }

            case 6: {
                if (!graph_created1 && !graph_created2 ) {
                    cout << "Сначала создайте граф (пункт 1,4).\n";
                    break;
                }
                int u, v;
                cout << "Введите начальную вершину (1.." << work->get_m().size() << "): ";
                cin >> u;
                cout << "Введите конечную вершину: ";
                cin >> v;
                if (u < 1 || u > work->get_m().size() || v < 1 || v > work->get_m().size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Неверный номер вершины.\n";
                    break;
                }
                int cnt = work->simplePaths(u, v);
                if (cnt == 0)
                    cout << "Маршрутов нет.\n";
                else
                    cout << "Количество простых маршрутов: " << cnt << "\n";
                break;
            }

            case 7: {
                if (!graph_created1 && !graph_created2 ) {
                    cout << "Сначала создайте граф (пункт 1,4).\n";
                    break;
                }
                int u, v;
                cout << "Введите начальную вершину (1.." << work->get_m().size() << "): ";
                cin >> u;
                cout << "Введите конечную вершину: ";
                cin >> v;
                if (u < 1 || u > work->get_m().size() || v < 1 || v > work->get_m().size()) {
                    cout << "Неверный номер вершины.\n";
                    break;
                }

                /*int steps ; 
                cout << "Напишите количество ребер в пути (от 0 до " << work->get_m().size() - 1 <<"): \n";
                cin >> steps;
                while (steps <0 || steps >work->get_m().size() - 1) {
                    cout << "Неверно! Введите число (от 0 до " << work->get_m().size() - 1 <<"): \n";
                    cin >> steps;
                }
                */
                vector<vector<int>> mul = ed_matr;
                vector<vector<int>> res = ed_matr;

                  for (int k = 2; k <= work->get_m().size() - 1; ++k) {
                    mul = mat_mul(mul, ed_matr);
                    res = add_matrix(res,mul);
                     cout<<endl;
                }

                for(int i=0;i<work->get_m().size();i++)
                {
                    res[i][i]=1;
                }

               

                //cout<<"Матрица:\n"

                cout<<"Количество путей:\n";
                cout<<res[u-1][v-1]<<endl;
                break;
            }

            case 8: {//поправить тут еще не путь искать а просто ребра
                if (!graph_created1 && !graph_created2 ) {
                    cout << "Сначала создайте граф (пункт 1,4).\n";
                    break;
                }
                int u;
                cout << "Введите начальную вершину (1.." << work->get_m().size() << "): ";
                cin >> u;
                if (u < 1 || u > work->get_m().size() ) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Неверный номер вершины.\n";
                    break;
                }
                vector<vector<int>> visited( work->get_m().size(), vector<int>(work->get_m().size(),0));
                int cnt = work->simplePaths_e(u, it_c8,visited);
                if (cnt == 0)
                    cout << "Маршрутов нет.\n";
                else
                    cout << "Количество простых маршрутов: " << cnt << "\n";
                

                cout<<endl;
                break;
            }

            case 9: {
                if (!graph_created1 && !graph_created2 ) {
                    cout << "Сначала создайте граф (пункт 1,4).\n";
                    break;
                }
                //bool floid_w_alg(, vector<vector<bool>>& paths)

                vector<vector<int>> lenght;
                vector<vector<int>> paths;
                vector<int> path;
                //int cnt = work->simplePaths_e(u, v);
                it_c9 =work->floid_w_alg(lenght,paths);
                if(it_c9 ==0)
                {
                    cout<<"Есть отрицательные пути!\n";
                    break;
                }
                cout<<"Матрица:\n";
                print_matrix(work->get_m());
                cout<<endl;
                cout<<"Матрица длин путей:\n";
                print_matrix(lenght);
                cout<<endl;
                cout<<"Матрица путей:\n";
                print_matrix(paths);

                int u, v;
                cout << "Введите начальную вершину (1.." << work->get_m().size() << "): ";
                cin >> u;
                cout << "Введите конечную вершину: ";
                cin >> v;
                if (u < 1 || u > work->get_m().size() || v < 1 || v > work->get_m().size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Неверный номер вершины.\n";
                    break;
                }

                bool a = find_path_fw(u,v,paths,path);
                if(a==0)
                {cout<< "Нет путей\n";
                    break;
                }

                cout<<u;
                for(int i:path) cout<<"->"<<i;
                cout<<endl;

                break;
            }
            case 10:
                {
                    cout<<"Количество итераций для п.8: "<<it_c8<<endl;
                    cout<<"Количество итераций для п.9: "<<it_c9<<endl;
                    break;
                }

            case 11:
            {
                if(!is_oriented)
                {
                    cout<<"Граф не ориентированный, сгенерируйте ориентированный в п.1.\n";
                    break;
                }
                cost = ed_matr;
                capacity = ed_matr;
                /*int weight_type;
                cout << "Тип весов: 1 - только положительные, 2 - только отрицательные, 3 - смешанные: ";
                cin >> weight_type;
                while (weight_type < 1 || weight_type > 3) {
                    cout << "Неверно! Введите 1, 2 или 3: ";
                    cin >> weight_type;
                }*/
                work->update_matrix(1,cost);
                work->update_matrix(1,capacity);
                cout << "Все значения присвоены. Матрица пропускной способности:\n";
                for(int i=0;i<capacity.size();i++)
                {
                    for(int j=0; j < capacity.size(); j++)
                    {
                        cout<<capacity[i][j]<<"    ";
                    }
                    cout<<endl;
                }
                cout << "Матрица стоимсти:\n";
                for(int i=0;i<cost.size();i++)
                {
                    for(int j=0; j < cost.size(); j++)
                    {
                        cout<<cost[i][j]<<"    ";
                    }
                    cout<<endl;
                }

                vector<int> stock;
                vector<int> istock;

                for(int i=0;i<cost.size();i++)
                {
                    bool has_is = 0;
                    bool has_s = 0;
                    for(int j=0; j < cost.size(); j++)
                    {
                        if(capacity[j][i]!=0) has_is = 1;
                        if(capacity[i][j]!=0) has_s = 1;
                    }
                    if(has_is ==0) istock.push_back(i+1);
                    if(has_s ==0) stock.push_back(i+1);
                }

                cout << "Истоки [";
                for (int i = 0; i < istock.size(); i++) {
                    cout << istock[i];
                    if (i != istock.size() - 1) cout << ", ";
                }
                cout << "]";
                cout << "Cтоки [";
                for (int i = 0; i < stock.size(); i++) {
                    cout << stock[i];
                    if (i != stock.size() - 1) cout << ", ";
                }
                cout << "]\n";

                big_capacity = capacity;

                

                if(istock.size() > 1)
                {
                    big_capacity.push_back(vector<int>(big_capacity.size() + 1, 0));
                    int cou = 0;
                    for(int i = 0; i < big_capacity.size(); i++) {
                        if(istock[cou]-1 == i)
                        {
                            big_capacity[i].push_back(summ(capacity[istock[cou]-1]));
                            cou++;
                        }
                        else big_capacity[i].push_back(0);
                        
                    }
                    m_istock = big_capacity.size() ;
                }
                else m_istock = istock[0];
                if(stock.size() > 1)
                {
                    big_capacity.push_back(vector<int>(big_capacity.size() + 1, 0));
                    int cou = 0;
                    for(int i = 0; i < big_capacity.size(); i++) {
                        if(stock[cou]-1 == i)
                        {
                            int su = 0;

                            for(int j=0; j < cost.size(); j++)
                            {
                                su+= capacity[j][i];
                            }
                            big_capacity[i].push_back(su);
                            cou++;
                        }
                        else big_capacity[i].push_back(0);
                        
                    }
                    m_stock = big_capacity.size() ;
                }
                else m_stock = stock[0];
                print_matrix(big_capacity);
                cout<<"main istock = " << m_istock<<endl;
                cout<<"main stock = " << m_stock<<endl;
                break;
            }
            case 12: 
            {
                if (big_capacity.empty()) {
                    cout << "Сначала выполните пункт 11 для генерации capacity\n";
                    break;
                }
                
                
                cout << "Исток: " << m_istock  << " Сток: " << m_stock  << endl;

                vector<vector<int>> result = FF_alg(m_istock-1, m_stock-1, big_capacity, big_capacity.size());

                print_matrix(result);

                int maxF = 0;
                for (int i = 0; i < big_capacity.size(); i++) {
                    maxF += result[i][m_stock-1];
                }
                
                cout << "Максимальный поток: " << maxF << endl;
                
                targetFlow = (2 * maxF) / 3;
                
                break;
            }
            case 13:
            {
                cout << "Целевой поток (2/3): " << targetFlow << endl;
                l3_3(m_stock,m_istock, big_capacity, cost, targetFlow);
                break;
                
            }

            case 14:
                cout << "Выход.\n";
                return 0;
        }
    }
    return 0;
}
