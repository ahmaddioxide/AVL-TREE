#include <iostream>
using namespace std;

class node
{

public:
    int data;
    node *right;
    node *left;
    node(/* args */);
    ~node();
};

node::node(/* args */)
{
    data = 0;
    right = NULL;
    left = NULL;
}

node::~node()
{
}

class AVLTree
{

public:
    node *root;
    AVLTree(/* args */);
    ~AVLTree();
    node *RecursiveInsertion(node *r, node *new_node);
    void inorderprint(node *root);
    void Print2D(node *root, int space);
    void display();
    int getBalancefactor(node *root);
    int calculateheight(node *r);
    node *RRotaion(node *y);
    node *LRotaion(node *x);
    int getmax(int l, int r);
    

    void Insert(int k);
};

int AVLTree::getmax(int l, int r)//!function to get maximum of two numbers
{
        if (l > r)
        {
            return l;
        }
        else
        {
            return r;
        }
}



int AVLTree::calculateheight(node *r)//! Recursive Function to calculate height of the tree
{
    int h = 0;
    if (r != NULL)
    {
        int lHeight = calculateheight(r->left);
        int rHeight = calculateheight(r->right);
        int maxHeight = getmax(lHeight, rHeight);
        h = maxHeight + 1;
    }
    return h;
}



int AVLTree::getBalancefactor(node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return ((calculateheight(root->left) - calculateheight(root->right)));
    }
}



node *AVLTree::RRotaion(node *y) //! For left left imbalance

//*         n1      ->y
//*         /
//*       n2        ->temp
//*      /  \       
//*    n3   NULL    ->temp2
{
    node *temp = y->left;
    node *temp2 = temp->right;
    //* Code of rotation

    temp->right = y; //* making n2 right which was NULL pointing to n1

    //*          n1
    //*         /
    //*       n2
    //*      /  \       
    //*    n3    n1
    //*         /
    //*       n2

    y->left = temp2; //* as n1 left continued to pint to n2 so we removed that link

    //*
    //*
    //*       n2
    //*      /  \        
    //*     n3  n1

    return temp; //* return address of n2
}

node *AVLTree::LRotaion(node *x) //! For right right imbalance
{

    //*          n1            ->x
    //*            \
    //*             n2         ->temp
    //*           /   \       
    //* temp2<- NULL   n3

    node *temp = x->right;
    node *temp2 = temp->left;

    //* code for rotation

    temp->left = x;

    //*          n1            ->x
    //*            \
    //*             n2         ->temp
    //*           /   \       
    //*         n1     n3
    //*        /  \
    //*    NULL     n2

    x->right = temp2;
    //*
    //*
    //*             n2         ->temp
    //*           /   \       
    //*         n1     n3
    //*        /  \
    //*            NULL

    return temp; //* return address of n2
}



node *AVLTree::RecursiveInsertion(node *r, node *new_node)
{
    if (r == NULL) //! if root node is empty then adding this node to root of tree
    {
        r = new_node;
        return r;
    }

    if (new_node->data < r->data) //! If new node's data is less then the data of root node then move to the left recursively until we find best place for it
    {
        r->left = RecursiveInsertion(r->left, new_node);
    }
    else if (new_node->data > r->data) //! If new node's data is grater then the data of root node then move to the' right recursively until we find best place for it
    {
        r->right = RecursiveInsertion(r->right, new_node);
    }
    else //! if new_node's data is already in tree then skip RecursiveInsertioniin coz in my algorithm duplication is not allowed
    {
        cout << "\n|Duplication is not allowed in my algorithm";
        return r;
    }
    //!return r;  uncomment this to get functionality of simple bst. no rotation will occur
                                                         //*SIMPLE BST ENDS HERE
                                            //* AVL MAIN FUNCTIONALITY STARTS FROM HERE*//

    int BalanceFactor;
    BalanceFactor = getBalancefactor(r);

    if (BalanceFactor > 1 && new_node->data < r->left->data) //! this is case of left left imbalance
    {

        //*         n1      
        //*         /
        //*       n2        
        //*      /       
        //*    n3   

        return RRotaion(r);

        //*       n2
        //*      /  \        
        //*     n3  n1

    }
    if (BalanceFactor < -1 && new_node->data > r->right->data) //! this is case of right right imbalance
    {
         //*          n1            
        //*            \
        //*             n2         
        //*               \       
        //*                n3
        return LRotaion(r);

        //*       n2
        //*      /  \        
        //*     n3  n1


    }
    if (BalanceFactor > 1 && new_node->data > r->left->data) //! this is case of left right imbalance
    {
        //*          n1            
        //*         /   
        //*       n2         
        //*         \       
        //*          n3

        r->left = LRotaion(r->left);

        //*         n1      
        //*         /
        //*       n2        
        //*      /       
        //*    n3 

        return RRotaion(r);

        //*       n2
        //*      /  \        
        //*     n3  n1

    }
    if (BalanceFactor < -1 && new_node->data < r->right->data) //! this is case of right left imbalance
    {
        //*          n1            
        //*           \ 
        //*            n2         
        //*           /    
        //*         n3

        r->right = RRotaion(r->right);

        //*          n1            
        //*            \
        //*             n2         
        //*               \       
        //*                n3

        return LRotaion(r);

        //*       n2
        //*      /  \        
        //*     n3  n1
    }

    return r;
}



void AVLTree::Print2D(node *root, int space = 5) //! Function to print the tree in 2D manner
{

    if (root == NULL)
    {
        return;
    }
    space += 5;
    Print2D(root->right, space);
    cout << "\n";
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << root->data;
    cout << "\n";
    Print2D(root->left, space);
}



void AVLTree::inorderprint(node *root) //! Function to print tree in inorder manner
{
    if (root == NULL)
    {
        return;
    }
    inorderprint(root->left);
    cout << root->data << " ";
    inorderprint(root->right);
}


void AVLTree::Insert(int k)

{
    node *new_node = new node;
    new_node->data = k;
    // node* temproot = new node;

    root = RecursiveInsertion(root, new_node);
}



void AVLTree::display() //! Function to display the tree
{
    inorderprint(root); //! Printing the tree in inorder
    cout << "\n\n";
    Print2D(root); //! printing the tree in 2D way for better understanding of the tree
}


AVLTree::AVLTree(/* args */)
{
    root = NULL;
}


AVLTree::~AVLTree()
{
}

int main()
{

    AVLTree t;
    t.Insert(50);
    t.Insert(40);
    t.Insert(60);
    t.Insert(30);
    t.Insert(10);
    t.Insert(9);
    t.display();

}