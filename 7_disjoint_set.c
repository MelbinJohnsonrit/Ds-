#include<stdio.h>
#include<stdlib.h>

struct node{
   struct node *rep;
   struct node *next;
   int data;
}*heads[50],*tails[50];

static int countRoot=0;

void makeSet(int elements[], int size);
//void makeSet(int x)
void unionSets(int a,int b);
int search(int x);
struct node* find(int a){
    int i;
    struct node *tmp=(struct node *)malloc(sizeof(struct node));
    for(i=0;i<countRoot;i++){
    tmp=heads[i];
    while(tmp!=NULL){
        if(tmp->data==a)
            return tmp->rep;
            tmp=tmp->next;
        }
   }
   return NULL;
}

void main(){
    int choice,x,i,j,y,flag=0,numElements;
    int elements[numElements];
    int duplicateFlag = 0;
    do{
	printf("\n1.Make Set\n2.Display set representatives\n3.Union\n4.Find Set\n5.Display sets\n6.Exit\n");

	printf("Enter your choice :  ");
	scanf("%d",&choice);

	switch(choice){
	    case 1: 
                //multiple element insertion
                printf("\nEnter the number of elements in the new set: ");
                scanf("%d", &numElements);
                //int elements[numElements];
                printf("Enter the elements: ");
                for (int i = 0; i < numElements; i++) {
                        scanf("%d", &elements[i]);
			if (search(elements[i]) == 1) {
                                printf("\nElement %d already present in the disjoint set DS\n", elements[i]);
				i--;
				continue;
                        }
		}
		if (duplicateFlag == 0) {
                        makeSet(elements, numElements);
                } break;

	    case 2:
 		printf("\n");
		for(i=0;i<countRoot;i++){
		    printf("%d ",heads[i]->data);
		    printf("\n");
		    //break;
		}
		break;
	    case 3:
		printf("\nEnter first element : ");
		scanf("%d",&x);
		printf("\nEnter second element : ");
		scanf("%d",&y);
		unionSets(x,y);
		break;
	    case 4:
		printf("\nEnter the element");
		scanf("%d",&x);
		struct node *rep=(struct node *)malloc(sizeof(struct node));
		rep=find(x);
		if(rep==NULL)
		    printf("\nElement not present in the DS\n");
		else
		    printf("\nThe representative of %d is %d\n",x,rep->data);
		break;
	    case 5:
		for (i = 0; i <countRoot; i++) {
   		printf("Set %d: ", i + 1);
    		struct node *temp =heads[i];
   		printf("{ ");
    		while (temp != NULL) {
        	    printf("%d ", temp->data);
		    temp = temp->next;
    		}
		printf("}\n");
		}

		break;
	    case 6:
		exit(0);
	    default:
		printf("\nWrong choice\n");
		break;
	}
    }while(1);
}

void makeSet(int elements[], int size) {
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->rep = new;
    new->next = NULL;
    new->data = elements[0];
    heads[countRoot] = new;
    tails[countRoot] = new;

    struct node *current = new;

    for (int i = 1; i < size; i++) {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp->rep = new;  // All nodes point to the first node as their representative
        temp->next = NULL;
        temp->data = elements[i];
        current->next = temp;
        current = temp;
    }
    
    tails[countRoot++] = current;
}

void unionSets(int a,int b){
    int i,pos,flag=0,j;
    struct node *tail2=(struct node *)malloc(sizeof(struct node));
    struct node *rep1=find(a);
    struct node *rep2=find(b);
    if(rep1==NULL||rep2==NULL){
        printf("\nElement not present in the DS\n");
        return;
    }
    if(rep1!=rep2){
        for(j=0;j<countRoot;j++){
            if(heads[j]==rep2){
                pos=j;
                flag=1;
                countRoot-=1;
                tail2=tails[j];
                for(i=pos;i<countRoot;i++){
                    heads[i]=heads[i+1];
                    tails[i]=tails[i+1];
                }
            }
            if(flag==1)
            break;
        }
        for(j=0;j<countRoot;j++){
            if(heads[j]==rep1){
                tails[j]->next=rep2;
                tails[j]=tail2;
                break;
            }
        }
        while(rep2!=NULL){
            rep2->rep=rep1;
            rep2=rep2->next;
        }
    }
}

int search(int x){
    int i;
    struct node *tmp=(struct node *)malloc(sizeof(struct node));
    for(i=0;i<countRoot;i++){
        tmp=heads[i];
        if(heads[i]->data==x)
            return 1;
        while(tmp!=NULL){
            if(tmp->data==x)
                return 1;
            tmp=tmp->next;
        }
    }
    return 0;
}
