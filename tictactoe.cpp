#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
//Change this value (ply) from 2 to 9 to change the level
#define ply 9
#define win 10
#define loose -10
#define max 1
#define min 2
 

class Node
{public:
      int a[3][3];
      int level;
      Node *next[9];
      int minmax;
      
      
             int Read_State(int);
             void Print_State();
             char Check_State(int);
             void Init_Matrix(Node**);
             int Is_Win(int);
             int Create_Tree(Node**,int);
             void Copy(int b[3][3],int c[3][3]);
             int Calc_Minmax(int);
             void Update_Values(Node*,int,int);
             Node* Next_State(Node*);
             int Is_Zero();
             void Flush(Node**);
};

int Node::Read_State(int x)
{
     cout<<"\n\nEnter ur choice (1-9) : ";
     int n;
     label:
     cin>>n;
     n--;
     if(n>8 || n<0)
     {
            cout<<"Invalid inpur...Re enter : ";
            goto label;
     }
     else if(a[n/3][n%3]!=0)
     {
            cout<<"Invalid inpur...Re enter : ";
            goto label;
     }
     if(x==max)
               a[n/3][n%3]=1;
     else
         a[n/3][n%3]=2;
     return n;
}
char Node::Check_State(int x)
{
     if(x==0)
             return ' ';
     else if(x==1)
          return 'X';
     else
         return 'O';
}

void Node::Init_Matrix(Node **root)
{
     for(int i=0;i<3;i++)
             for(int j=0;j<3;j++)
                     (*root)->a[i][j]=0;
     
     (*root)->level=0;
}     

void Node::Print_State()
{
     system("cls");
     cout<<"---------------------------------TIC TAC TOE------------------------------------\n\n";
     cout<<"  "<<Check_State(a[0][0])<<"  |  "<<Check_State(a[0][1])<<"  |  "<<Check_State(a[0][2])<<"  "<<"\t\t\t"<<"  1  |  2  |  3  \n"; 
     cout<<"-----------------"<<"\t\t\t"<<"-----------------\n";
     cout<<"  "<<Check_State(a[1][0])<<"  |  "<<Check_State(a[1][1])<<"  |  "<<Check_State(a[1][2])<<"  "<<"\t\t\t"<<"  4  |  5  |  6  \n"; 
     cout<<"-----------------"<<"\t\t\t"<<"-----------------\n";
     cout<<"  "<<Check_State(a[2][0])<<"  |  "<<Check_State(a[2][1])<<"  |  "<<Check_State(a[2][2])<<"  "<<"\t\t\t"<<"  7  |  8  |  9  \n";
}

void Node::Copy(int b[3][3],int c[3][3])
{
    for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                    b[i][j]=c[i][j];
}

int Node::Is_Win(int n)
{
    int flag[8]={1,1,1,1,1,1,1,1};
    for(int i=0;i<3;i++)
    {
            for(int j=0;j<3;j++)
            {
                    if(a[0][j]!=n)
                                  flag[0]=0;
                    if(a[1][j]!=n)
                                  flag[1]=0;
                    if(a[2][j]!=n)
                                  flag[2]=0;
                    if(a[i][0]!=n)
                                  flag[3]=0;
                    if(a[i][1]!=n)
                                  flag[4]=0;
                    if(a[i][2]!=n)
                                  flag[5]=0;
                    if((i==j) && (a[i][j]!=n))
                              flag[6]=0;
                    if((i+j==2) && (a[i][j]!=n))
                                  flag[7]=0;
            }
    }
    for(int i=0;i<8;i++)
            if(flag[i]==1)
                          return 1;
    return 0;
}

int Node::Create_Tree(Node **root,int n)
{

     if((*root)!=NULL)
{     if((*root)->level < ply)
     {
     for(int i=0;i<9;i++)
     {
             if((*root)->a[i/3][i%3]==0)
             {
                                        (*root)->next[i]=new Node;
                                        Copy((*root)->next[i]->a,(*root)->a);
                                        (*root)->next[i]->a[i/3][i%3]=n;
                                        (*root)->next[i]->level=(*root)->level+1;
                                        if((*root)->next[i]->level==ply || (*root)->next[i]->Is_Zero()==0)
                                        {
                                                                        if(n==max)
                                                                                  (*root)->next[i]->minmax=(*root)->next[i]->Calc_Minmax(max);
                                                                        else
                                                                            (*root)->next[i]->minmax=(*root)->next[i]->Calc_Minmax(max);
                                        }
                                        
                                        {
                                            if((*root)->level%2==0)
                                                      (*root)->minmax=loose;
                                            else
                                                (*root)->minmax=win;
                                        }
                             
                                        if(n==max)
                                                  (*root)->next[i]->Create_Tree(&((*root)->next[i]),min);
                                        else
                                            (*root)->next[i]->Create_Tree(&((*root)->next[i]),max);
             }
             else
                 (*root)->next[i]=NULL;
     }
     }
     else
     {

         for(int i=0;i<9;i++)
                 (*root)->next[i]=NULL;
     }
}
     return 1;
}
                                        
int Node::Calc_Minmax(int n)
{
      int max_count=0;
      int flag[8]={1,1,1,1,1,1,1,1},x=0;
    if(Is_Win(max)==1 )
    {
                    return win;
    }
     if(Is_Win(min)==1 )
         return loose;
    
    label:
    for(int i=0;i<3;i++)
    {
            for(int j=0;j<3;j++)
            {
                    if(a[0][j]!=n && a[0][j]!=0)
                                  flag[0]=0;
                    if(a[1][j]!=n && a[1][j]!=0)
                                  flag[1]=0;
                    if(a[2][j]!=n && a[2][j]!=0)
                                  flag[2]=0;
                    if(a[i][0]!=n && a[i][0]!=0)
                                  flag[3]=0;
                    if(a[i][1]!=n && a[i][1]!=0)
                                  flag[4]=0;
                    if(a[i][2]!=n && a[i][2]!=0)
                                  flag[5]=0;
                    if((i==j) && (a[i][j]!=n) && (a[i][j]!=0))
                              flag[6]=0;
                    if((i+j==2) && (a[i][j]!=n) && (a[i][j]!=0))
                                  flag[7]=0;
            }
    }
    if(x==1)
            goto label1;
    for(int i=0;i<8;i++)
    {        if(flag[i]==1)
                          max_count++;
                          flag[i]=1;
    }
    if(n==max)
              n=min;
    else
        n=max;
    x=1;
    goto label;
    label1:
    for(int i=0;i<8;i++)
    {        if(flag[i]==1)
                          max_count--;
                          flag[i]=1;
    }

    if(n==max)
    return -max_count;
    else
        return max_count;
}       
    
void Node::Update_Values(Node *root,int n,int depth)
{
     Node *temp=root;
     int flag=0,flag1=0;
     if(depth>0){
     if(root->level<(depth-1))
     {
                          for(int i=0;i<9;i++)
                          {
                                  if(root->next[i]!=NULL)
                                  {
                                                         if(root->level%2==0)
                                                         {          
                                                                    if(root->next[i]->Is_Win(max)==1 && root->Is_Win(min)!=1)
                                                                    {                                 root->next[i]->minmax=win;

                                                                    flag=i;}
                                                                    else
                                                                    (root)->next[i]->Update_Values(root->next[i],min,depth);
                                                         }
                                                         else
                                                         {
                                                             if(root->next[i]->Is_Win(min)==1 && root->Is_Win(max)!=1)
                                                             {                                        root->next[i]->minmax=loose;
                                                            flag1=i;
                                                            }
                                                             else
                                                             (root)->next[i]->Update_Values(root->next[i],max,depth);
                                                         }
                                  }
                          }
     }
     else
     {
         int x;
         if(root->level%2==1)
         {
                   for(int i=0;i<9;i++)
                   {
                           if(root->next[i]!=NULL)
                           {

                           
                            if(flag)
                            {        root->minmax=root->next[flag]->minmax ;
                            cout<<"apurva pathak"<<root->level<<"\n";
                            break;
                            }

                            else                
                           if(root->next[i]->minmax < root->minmax )
                                                  root->minmax=root->next[i]->minmax;
                                                  }
                           
                   }

         }
         else
         {
                   for(int i=0;i<9;i++)
                   {
                           if(root->next[i]!=NULL)
                           {

                                                  if(flag1)
                            {        root->minmax=root->next[flag1]->minmax ;
                            break;
                            }
                                                  if(root->next[i]->minmax > root->minmax)
                                                                           root->minmax=root->next[i]->minmax;
                           }
                   }
 
         }
     }
     if(root->level==0)
     //if(n==max)
       {        (root)->Update_Values(root,max,depth-1);

       }
     
         }    
}        
 
int Node::Is_Zero()
{
    for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                    if(a[i][j]==0)
                                  return 1;
    return 0;
}                           
Node* Node::Next_State(Node *root)
{
      for(int i=0;i<9;i++)
      {
              if((root)->next[i]!=NULL)
              {                        
                                       if((root)->minmax==win && root->next[i]->Is_Win(max)==1)
                                       {
                                                              Copy(this->a,root->next[i]->a);
                                                                                     this->minmax=root->next[i]->minmax;
                                                                                     this->level=0;
                                                                                     return (root)->next[i];}
                                      /* if(root->minmax==loose)
                                       {
                                                              if(root->minmax<root->next[i]->Calc_Minmax(max) && root->next[i]->Is_Win(min)!=1)
                                                              {
                                                                                                    Copy(this->a,root->next[i]->a);
                                                                                     this->minmax=root->next[i]->Calc_Minmax(max);
                                                                                     this->level=0;
                                                              }
                                                              } */                  
              }
      }
      for(int i=0;i<9;i++)
      {
              if((root)->next[i]!=NULL)
              {                 
                                        if((root)->minmax==(root)->next[i]->minmax)
                                        {                                            Copy(this->a,root->next[i]->a);
                                                                                     this->minmax=root->next[i]->minmax;
                                                                                     this->level=0;
                                                                                     return (root)->next[i];
                                        }
              }
              
      }

return root;
      
}       
void Node::Flush(Node** root)
{
     for(int i=0;i<9;i++)
     {
             if((*root)->next[i]!=NULL)
                                       (*root)->next[i]->Flush(&(*root)->next[i]);
     }
     delete(*root);
}             
     
int main()
{
    class Node *root,*temp;
    
    char ans;
    do{
         root=new Node;
    root->Init_Matrix(&root);
    system("cls");
    cout<<"Do u wanna go 1st (y/n) : ";
    label:
    fflush(stdin);
    cin>>ans;
    if(ans!='y' && ans !='Y' && ans !='n' && ans!='N')
    {            
                 cout<<"Invalid choice...Re enter : ";
                 goto label;
    }
    cout<<"\n\n\n\n\n\n\n\n\nThe Game Is About To Start  .  .  .\n\n\n\n\n\n\n\n\n\n\n\n\n";
    system("pause");
    root->Print_State();
    if(ans=='y' || ans=='Y')
                root->Read_State(min);
    do
    {

    temp=root;
    root->Print_State();
    root->level=0;
     root->Create_Tree(&root,max);
     root=new Node;
    temp->Update_Values(temp,max,ply);
    root->Next_State(temp);
    root->Print_State();
    cout<<"\n\nMy chances to win : "<<(root->minmax+10)*5<<"%\n";
    //cout<<root->minmax;
   if(root->Is_Win(max)!=1 && root->Is_Win(min)!=1 && root->Is_Zero()==1)
    root->Read_State(min);
    root->Print_State();
    temp->Flush(&temp);
    }while(root->Is_Win(max)!=1 && (root->Is_Win(min)!=1) && root->Is_Zero()==1);
    if(root->Is_Win(max)==1)
                            cout<<"\n\nU r a LOSER :-P :-D :-P";
    else if(root->Is_Win(min)==1) 
                               cout<<"\n\nU Won :-) :-)";
    else
        cout<<"\n\nMatch Drawn :-| :-|";
    cout<<"\n\n\nWanna rematch?? ;-) ;-) (y/n) : ";
    label1:
    fflush(stdin);
    cin>>ans;
    if(ans!='y' && ans !='Y' && ans !='n' && ans!='N')
    {            
                 cout<<"Invalid choice...Re enter : ";
                 goto label1;
    }
}while(ans=='y' || ans=='Y');
cout<<"\n\nHave a nice day :-)\n";

    getch();
    return 0;
}
     
     
