#include <stdio.h>
#include <stdlib.h>


struct node {
 int key;
 struct node* left;
 struct node* right;
 struct node *p;
};

typedef struct node* Node;

/* Create a new node */
Node newNode(int key) {
 Node node = (Node) malloc(sizeof(struct node));
 node->key = key;
 node->left = NULL;
 node->right = NULL;
 node->p=NULL;
 return(node);
}

/* Insert a new node into a BST */
void insert(Node* root, Node z) {
 Node x,y;
 y=NULL;
 x=*root;
 while (x!=NULL) {
    y=x;
    if (x->key < z->key)
                x=x->right;
    else
                x=x->left;
    }
 z->p=y;
 if (y==NULL) {
        *root=z;
        }
        else {
        if (z->key<=y->key)
            y->left=z;
        else
            y->right=z;
        }

}


void inorder(Node root) {
    if(root!=NULL){
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
void preorder(Node root) {
    if(root!=NULL){
        printf("%d ", root->key);
        inorder(root->left);
        inorder(root->right);
    }
}
void postorder(Node root) {
    if(root!=NULL){
        inorder(root->left);
        inorder(root->right);
        printf("%d ", root->key);
    }
}
int height(Node root) {

    Node x=root;
    int height_max=-1;
    while(x!=NULL){
        height_max++;
        if(x->left==NULL && x->right==NULL){
            break;
        }
        else if(x->left!=NULL && x->right!=NULL){
            int left_height=height(x->left);
            int right_height=height(x->right);
            if(left_height>right_height){
                height_max=height_max+left_height;
                break;
            }
            else{
                height_max=height_max+right_height;
                break;
            }
        }
        if(x->left!=NULL){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    return height_max;
}


int search(Node root, int key) {

   Node x=root;
   while(x!=NULL){
       if(key==x->key){
           return 1;
       }
       else if(key<x->key){
           x=x->left;
       }
       else
       {
           x=x->right;
       }
   }
    return 0;
}
int isPerfectlyBalanced(Node root){
    Node x=root;
    if(root==NULL){
        return 1;
    }
        int left_height= height(x->left);
        int right_height= height(x->right);
        if((abs(left_height-right_height)==1) && isPerfectlyBalanced(x->left) && isPerfectlyBalanced(x->right)){
            return 1;
    }
    return 0;
}
int searchClosest(Node root, int k){
    Node x=root;
    int dif=abs(x->key-k);
    int min=dif;
    Node y=x;
    if(root->key==k){
        return root->key;
    }
    while(x!=NULL){
        if(x->key==k){
            return x->key;
        }
        if(k<x->key){
            if(abs(x->key-k)<min){
                min=x->key-k;
                y=x;
            }
            x=x->left;
        }
        else{
            if(abs(x->key-k)<min){
                min=x->key-k;
                y=x;
            }
            x=x->right;
        }
    }
    return y->key;
}
void inorderTraversal(Node root, Node* array, int* index) { // I have  2 inorder traversal functions because this one stores the nodes in an array, while the other one simply traverses the tree
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, array, index);
    array[*index] = root;
    (*index)++;
    inorderTraversal(root->right, array, index);
}
int CheckExistTwoNodesWithSum(Node root, int s) {
    Node* array = (Node*)malloc(sizeof(Node) * 100);
    int index = 0;
    inorderTraversal(root, array, &index);
    int left = 0, right = index - 1;
    while (left < right) {
        int sum = array[left]->key + array[right]->key;
        if (sum == s) {
            return 1;
        } else if (sum < s) {
            left++;
        } else {
            right--;
        }
    }
    return 0;
}
void printPathswithSum(Node root, int sum,int s,int array[],int k){
    if(root==NULL){
        return;
    }
        Node x=root;
        s=s+x->key;
        array[k]=x->key;
        k++;
        if(x->left==NULL && x->right==NULL && s==sum){
            for(int i=0;i<k;i++){
                printf("%d ",array[i]);
            }
            printf("\n");
    }
    printPathswithSum(x->left,sum,s,array,k);
    printPathswithSum(x->right,sum,s,array,k);
}
/*void Print_Levels(Node root){
    Node x=root;
    while(x!=NULL){
        printf("%d ",x->key);
        Print_Levels(x->left);
        Print_Levels(x->right);
    }
}*/
int main()
{
    Node tree=NULL;

    insert(&tree,newNode(8));
    insert(&tree,newNode(2));
    insert(&tree,newNode(15));
    insert(&tree,newNode(1));
    insert(&tree,newNode(5));
    insert(&tree,newNode(10));
    insert(&tree,newNode(20));
    insert(&tree,newNode(4));
    insert(&tree,newNode(7));
    insert(&tree,newNode(18));
    insert(&tree,newNode(22));
    insert(&tree,newNode(3));

    printf("This is the inorder walk:\n");
    inorder(tree);
    printf("\n");
    printf("This is the preorder walk:\n");
    preorder(tree);
    printf("\n");
    printf("This is the postorder walk:\n");
    postorder(tree);
    printf("\n");
    int h= height(tree);
    printf("Height:%d",h);
    printf("\n");
    int found = search(tree, 11);
    printf("The searched number:%d", found);
    printf("\n");
    printf("The tree is perfectly balanced:%d",isPerfectlyBalanced(tree));
    printf("\n");
    printf("The closest number:%d", searchClosest(tree,11));
    printf("\n");
    printf("The checked sum:%d", CheckExistTwoNodesWithSum(tree,12));
    printf("\nThe sum is:");
    int array[100];
   printPathswithSum(tree,22,0,array,0);
   printf("\n The print levels:");
   // Print_Levels(tree);

}
