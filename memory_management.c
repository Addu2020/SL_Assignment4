#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    bool MandS;//for MandSing the nodes to use MandS and sweep mechanism
    int refer_count;//reference count mechanism
    struct node *adj_1;
    struct node *adj_2;
    struct node *adj_3;
    //Maximum three links are shown in the diagram
    
}Node;

Node *ptr_array[8];

//function to display reference count and freed size
void displayNode(int i)
{
	printf("value=%d\t reference_count=%d freed_size=%d\n",ptr_array[i]->data,ptr_array[i]->refer_count,sizeof(Node));
}

//it modifies the linked list based on the specified nodes
void setEdge(int ob,int dest_1,int dest_2,int dest_3)
{
	if(dest_1!=-1)                          // -1 means empty node and then it will get connected
	{
		ptr_array[ob]->adj_1=ptr_array[dest_1];
		ptr_array[dest_1]->refer_count+=1;
	}
	if(dest_2!=-1)
	{
		ptr_array[ob]->adj_2=ptr_array[dest_2];
		ptr_array[dest_2]->refer_count+=1;
	}
	if(dest_3!=-1)
	{
		ptr_array[ob]->adj_3=ptr_array[dest_3];
		ptr_array[dest_3]->refer_count+=1;
	}
}

//it displays all the nodes
void displayAllNodes(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d:refer_count=%d\n",root->data,root->refer_count);
	}
	if(root==NULL)
	{
		return;
	}
	displayAllNodes(root->adj_1);
	displayAllNodes(root->adj_2);
	displayAllNodes(root->adj_3);
}

//it prints the adjacency list
void adjacencyList()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(ptr_array[i]!=NULL)
		{
			printf("Value=%d: ",ptr_array[i]->data);
			if(ptr_array[i]->adj_1!=NULL)
			{
				printf("%d ->",ptr_array[i]->adj_1->data);
			}
			if(ptr_array[i]->adj_2!=NULL)
			{
				printf("%d ->",ptr_array[i]->adj_2->data);
			}
			if(ptr_array[i]->adj_3!=NULL)
			{
				printf("%d ->",ptr_array[i]->adj_3->data);
			}
			printf("NULL\n");
		}
	}
}

//if root is present then return 1 else return 0
int rootIsPresent(Node* root_1,Node* temp)
{
	if(root_1==NULL)
	{
		return 0;
	}
	if(root_1->data==temp->data)
	{
		return 1;
	}
	
	if(rootIsPresent(root_1->adj_1,temp))
	{
		return 1;
	}
	
	if(rootIsPresent(root_1->adj_2,temp))
	{
		return 1;
	}
	if(rootIsPresent(root_1->adj_3,temp))
	{
		return 1;
	}
    return 0;
}

//prints adjacency matrix
void adjacencyMatrix()
{
	int adm[8][8];
	int i,j,k;
	
	for(i=0;i<8;i++)		//initialising all indices values to 0
	{
		for(j=0;j<8;j++)
		{
			adm[i][j]=0;
		}	
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			
		if(ptr_array[j]!=NULL&&ptr_array[i]!=NULL)
		{
			
			if(ptr_array[i]->adj_1!=NULL)
			{
				if(ptr_array[i]->adj_1->data==ptr_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(ptr_array[i]->adj_2!=NULL)
			{
				if(ptr_array[i]->adj_2->data==ptr_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(ptr_array[i]->adj_3!=NULL)
			{
				if(ptr_array[i]->adj_3->data==ptr_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
		}
		
		}
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",adm[i][j]);
		}
		printf("\n");
	}
}

//it is recursive function that marks all the nodes (true) that are accessed from the root
void markMethod(Node* root)
{
	if(root!=NULL)
	{
		root->MandS=true;
	}
	if(root==NULL)
	{
		return;
	}
	markMethod(root->adj_1);
	markMethod(root->adj_2);
	markMethod(root->adj_3);
}

//it turns all the false nodes to null
void sweepMethod()
{
	int i;
	for(i=0;i<8;i++)
	{
		if(ptr_array[i]->MandS==false)
		{
			if(ptr_array[i]->adj_1!=NULL)
			{
				ptr_array[i]->adj_1->refer_count-=1;
			}
			if(ptr_array[i]->adj_2!=NULL)
			{
				ptr_array[i]->adj_2->refer_count-=1;
			}
			if(ptr_array[i]->adj_3!=NULL)
			{
				ptr_array[i]->adj_3->refer_count-=1;
			}
			printf("Garbage:");
			displayNode(i);
			free(ptr_array[i]);
			ptr_array[i]=NULL;
		}
	}
}

int main()
{
	//Node number  		   0,1,2,3,4,5,6,7	
	//value

	int val[]={1,2,3,5,7,8,9,10};

	int i;
	
	for( i=0;i<8;i++)
	{
		Node* newNode =(Node*)malloc(sizeof(Node));
		newNode->data=val[i];
		newNode->adj_1=NULL;
		newNode->adj_2=NULL;
		newNode->adj_3=NULL;
		newNode->refer_count=0;
		newNode->MandS=false;		
		ptr_array[i]=newNode;
	}
	
	Node*root_1=ptr_array[3];
	ptr_array[3]->refer_count+=1;
	Node*root_2=ptr_array[0];
	ptr_array[0]->refer_count+=1;
	
//  accessing the array by using index
	setEdge(0,1,6,7);
	setEdge(2,5,7,-1);
	setEdge(3,0,-1,-1);
	setEdge(4,0,5,-1);
	setEdge(5,6,-1,-1);
	
	printf("\nAll nodes through Root-1:\n");
	displayAllNodes(root_1);
		
	printf("\nAll nodes through Root-2:\n");
	displayAllNodes(root_2);
	
	printf("\n\nAdjacency list :\n"); //displaying Adjacency list of the nodes with corresponding value or vertex
	adjacencyList();
	
	printf("\n\nAdjacency matrix:\n"); //displaying Adjacency Matrix of the nodes rather than root 1 and root 2
	adjacencyMatrix();
	
	printf("\nCalling the MandS and sweep garbage collector\n");
	markMethod(root_1);
	sweepMethod();
	
	printf("\n\nAdjacency list after removal of garbage:\n");
	adjacencyList();
	
	printf("\n\nAdjacency matrix after removal of garbage:\n");
	adjacencyMatrix();
	
    return 0;
}