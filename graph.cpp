#include<iostream>
#include<vector>
class graph
{
private:
    std::vector<graph*> child;
    std::vector<int> distange;
    std::string name;
    std::string path;
    int *pathdistange=NULL;
    bool visit=false;
    graph* beforeNode=NULL;
public:
    
    graph(std::string name){
        this->name=name;
    }
    void pushchild(graph* node,int distange){
        this->child.push_back(node);
        this->distange.push_back(distange);
    }
    std::string getpath(){
        return this->path;
    }
    int* getpathdistange(){
        return this->pathdistange;
    }
    void shortestpath(graph* root){
        if (root->pathdistange==NULL)
        {
            root->path=root->name;
            root->pathdistange=new int(0);
        }
        for (int i = 0; i < root->child.size(); i++)
        {
            if(root->child.at(i)->pathdistange==NULL){
                root->child.at(i)->path=root->path+root->child.at(i)->name;
                root->child.at(i)->pathdistange=new int(*root->pathdistange+root->distange.at(i));
                shortestpath(root->child.at(i));
            }
            else if (*root->pathdistange+root->distange.at(i)<*root->child.at(i)->pathdistange)
            {
                root->child.at(i)->path.clear();
                root->child.at(i)->path=root->path+root->child.at(i)->name;
                delete root->child.at(i)->pathdistange;
                root->child.at(i)->pathdistange=new int(*root->pathdistange+root->distange.at(i));
                shortestpath(root->child.at(i));
            }
        }
    }
    void dephfirst(graph* root){
       if (!root->visit)
        {
            root->visit=true;
            std::cout<<"Start"<<root->name<<" ";
        }
        bool alltrue=true;
        for (int i = 0; i < root->child.size(); i++)
        {
            if(!root->child.at(i)->visit){
                root->child.at(i)->visit=true;
                root->child.at(i)->beforeNode=root;
                std::cout<<"  GoForward"<<root->child.at(i)->name;
                alltrue=false;
                dephfirst(root->child.at(i));
            }
        }
        if(alltrue)
            std::cout<<"  GoBack";
        if(root->beforeNode!=NULL)
            std::cout<<root->beforeNode->name;
    }
    ~graph(){
        delete pathdistange;
        child.erase(child.begin(),child.end());
        delete beforeNode;
    }
};
int main(int argc, char const *argv[])
{
    graph* m[10];
    int* matris[10][10]{
        {NULL        ,NULL        ,NULL        ,new int(95),NULL       ,NULL        ,NULL        ,NULL        ,NULL        ,new int(200)},

        {NULL        ,NULL        ,NULL        ,new int(80),new int(75),new int(110),NULL        ,NULL        ,NULL        ,new int(90) },

        {NULL        ,NULL        ,NULL        ,NULL       ,NULL       ,new int(160),new int(220),new int(230),NULL        ,new int(200)},
        
        {new int(95) ,new int(80) ,NULL        ,NULL       ,NULL       ,NULL        ,NULL        ,NULL        ,NULL        ,NULL        },
        
        {NULL        ,new int(75) ,NULL        ,NULL       ,NULL       ,NULL        ,NULL        ,NULL        ,NULL        ,NULL        },
        
        {NULL        ,new int(110),new int(160),NULL       ,NULL       ,NULL        ,NULL        ,NULL        ,new int(100),NULL        },
        
        {NULL        ,NULL        ,new int(220),NULL       ,NULL       ,NULL        ,NULL        ,new int(50) ,NULL        ,NULL        },
        
        {NULL        ,NULL        ,new int(230),NULL       ,NULL       ,NULL        ,new int(50) ,NULL        ,new int(125),NULL        },
        
        {NULL        ,NULL        ,NULL        ,NULL       ,NULL       ,new int(100),NULL        ,new int(125),NULL        ,NULL        },
        
        {new int(200),new int(90) ,new int(200),NULL       ,NULL       ,NULL        ,NULL        ,NULL        ,NULL        ,NULL        },
        
        };
    for (int i = 0; i < 10; i++)
    {
            m[i]=new graph("->"+std::to_string(i));
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (matris[i][j]!=NULL)
            {
                m[i]->pushchild(m[j],*matris[i][j]);
            }
        }
    }
    m[0]->dephfirst(m[5]);//visited and printed  all node
    m[0]->shortestpath(m[1]);//shortest path from one node to another node and distance required to go from one node to another node
    std::cout<<std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout<<m[i]->getpath();
        if(m[i]->getpathdistange()!=NULL)
        std::cout<<"  "<<*m[i]->getpathdistange();//print node path       
        std::cout<<std::endl;
    }
    return 0;
}
