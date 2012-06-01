#include<stdio.h>
#include<malloc.h>

struct node
	{
	 int info;
	 struct node* lchild;
	 struct node* rchild;
	};
struct node *root=NULL;
int max=0;
int delete(int);
int insert(int );
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);
int depth(struct node*,int);
int common(int,int);
int main()
{
 int c,item,con,d,del,n1,n2;
 do{
	printf("\nMENU !\n1.Insert\n2.Inorder Traversal\n3.Find Depth\n4.Delete\n5.Common root\n6.Preorder Traversal\n7.Postorder Traversal\n8.Quit\n");
	scanf("%d",&c);
	switch(c)
	{
		case 1: printf("Enter the item to insert ");
			scanf("%d",&item);
			insert(item);
			break;
		case 2: printf("\nInorder traversal is : ");
			inorder(root);
			break;
		case 3: d=depth(root,0);
			printf("\nDepth of the tree is %d",d);
			break;
		case 4: printf("\nEnter the item to be deleted\n");
			scanf("%d",&del); 
			delete(del);
			break;
		case 5: printf("\nEnter the two node values \n");
			scanf("%d",&n1);
			scanf("%d",&n2);
			common(n1,n2);
			break;
		case 6: printf("\nPreorder traversal is : ");
			preorder(root);
			break;
		case 7: printf("\nPostorder traversal is : ");
			postorder(root);
			break;
		case 8: exit(0);
		default:
			printf("\nWrong choice entered ! \n");
			break;
	}
	printf("\nContinue ?\n1.Yes\n2.No\n");
	scanf("%d",&con);
 }while(con==1);

return 0;
}

int insert(int item)
{
struct node* temp=malloc(sizeof(struct node));
struct node* ptr;
struct node* par;
temp->info=item;
temp->lchild=NULL;
temp->rchild=NULL;

if(root==NULL)		
	{
	root=temp;
	return 0;
	}
else if(item<root->info)	ptr=root->lchild;
else if(item>root->info)	ptr=root->rchild;
	else			{ printf("\nItem already present \n"); return 0; }
par=root;
while(ptr!=NULL)
	{
	if(item<ptr->info)
		{par=ptr;
		 ptr=ptr->lchild;
		 }
	else if(item>ptr->info)
		{
		par=ptr;
		ptr=ptr->rchild;
		}
	else	{ printf("\nItem already present \n"); return 0; }
	}
if(item<par->info)	par->lchild=temp;
else			par->rchild=temp;
}


void inorder(struct node* ptr)
{
 if(ptr!=NULL)
 	{ 
 	 inorder(ptr->lchild);
 	 printf("%d ",ptr->info);
 	 inorder(ptr->rchild);
	}
}

int depth(struct node* ptr,int k)
{
 if(ptr!=NULL)
	{
	k=k+1;
	depth(ptr->lchild,k);
	depth(ptr->rchild,k);
	if(max<k)
		max=k;
	k=k-1;
	}
return max;
}

int delete(int item)
{
 int flag=0;
 if(root==NULL)		{ printf("\nTree empty!\n"); return 0; }

 else {
 	struct node* ptr;
 	struct node* par;
 	struct node* ptrsave;
 	struct node* parsave;
 	struct node* succ;
 	struct node* succpar;
 	par=root;
 	if(item<root->info)	ptr=root->lchild;
 	else
 	  if(item>root->info)	ptr=root->rchild;
 	else			{ptr=root; par=NULL;}
 	
 	if(ptr!=root)
 	{
	 	while(ptr!=NULL)
	 	{
	 	 if(item==ptr->info)	{ flag=1; break; }
	 	 if(item<ptr->info)
	 	 		{
	 	 		 par=ptr;
	 	 		 ptr=ptr->lchild;
	 	 		}
	 	 else
	 	 		{
	 	 		par=ptr;
	 	 		ptr=ptr->rchild;
	 	 		}
	 	 	
	 	}
	 
 	  if(flag!=1)	{ printf("Item not present in tree!\n"); return 0; }
 	
 	}
 	if((ptr->lchild==NULL)&&(ptr->rchild==NULL))
 	{
 		if(par==NULL)		root=NULL;
 		else if(ptr==par->lchild)	par->lchild=NULL;
 		else				par->rchild=NULL;
 		return 0;
 	}
 	else
 	if(((ptr->lchild==NULL)&&(ptr->rchild!=NULL))||((ptr->lchild!=NULL)&&(ptr->rchild==NULL)))
 	{	
 		if(ptr->lchild==NULL)
 		{	
 			if(par==NULL)			root=ptr->rchild;
 			else
 			if(ptr==par->lchild)		par->lchild=ptr->rchild;
 			else				par->rchild=ptr->rchild;
 		}
 		else
 		{	
 			if(par==NULL)			root=ptr->lchild;
 			else
 			if(ptr==par->lchild)		par->lchild=ptr->lchild;
 			else				par->rchild=ptr->lchild;
 		}
 		return 0;
 	}
 	else
 	{
 	  ptrsave=ptr;
 	  if(par==NULL)
 	  {
	 	  par=ptr;
	 	  parsave=NULL;
 	  }
 	  else
 	  {
 	  parsave=par;
 	  par=ptr;
 	  }
 	  ptr=ptr->rchild;
 	  while(ptr->lchild!=NULL)
	 	  {
	 	  	par=ptr;
	 	  	ptr=ptr->lchild;
	 	  }
 	  succ=ptr;
 	  succpar=par;
 	  if(succ->lchild==NULL&&succ->rchild==NULL)
	 	  {
	 		if(succ==succpar->lchild)	succpar->lchild=NULL;
	 		else				succpar->rchild=NULL;
	 	  }
 	  else
	 	  {
	 	  	if(succ==succpar->lchild)		succpar->lchild=ptr->rchild;
	 	  	else					succpar->rchild=ptr->rchild;
	 	  }
 	  
 	  if(parsave==NULL)			root=succ;
 	  else if(ptrsave==parsave->lchild)	parsave->lchild=succ;
 	  else					parsave->rchild=succ;
 	  
 	  succ->lchild=ptrsave->lchild;
 	  succ->rchild=ptrsave->rchild;
 	 }
 	}
 return 0;
 }
 	  
 	  
int common(int a,int b)
{
 struct node* ptr;
 ptr=root;
 if(ptr==NULL)		{ printf("\nTree empty!"); return 0; }
 while(ptr!=NULL)
 {
   if((ptr->info>a&&ptr->info<b)||(ptr->info<a&&ptr->info>b))
   	{
   	 printf("\nCommon root is %d\n",ptr->info);
   	 return 0;
   	}
   else
   if(ptr->info>a&&ptr->info>b)
   	{
   	 if(ptr->lchild->info==a||ptr->lchild->info==b)		{ printf("\nCommon root is %d\n",ptr->info);  return 0; }
   	 else	ptr=ptr->lchild;
   	}
   else
   if(ptr->info>a&&ptr->info>b)
   	{
   	 if(ptr->rchild->info==a||ptr->rchild->info==b)		{ printf("\nCommon root is %d\n",ptr->info);  return 0; }
   	 else	ptr=ptr->rchild;
   	}	  
 	  
   else			{ printf("\nNo common root\n"); return 0; }
  }
}	  
 	  
void preorder(struct node* ptr)
{
 if(ptr!=NULL)
 	{ 
 	 printf("%d ",ptr->info);
 	 preorder(ptr->lchild);
 	 preorder(ptr->rchild);
	}
} 		
 		
void postorder(struct node* ptr)
{
 if(ptr!=NULL)
 	{ 
 	 postorder(ptr->lchild);
 	 postorder(ptr->rchild);
 	 printf("%d ",ptr->info);
	}
} 		
 		
 		
 		
 
 
 
 
 
 
 
 
