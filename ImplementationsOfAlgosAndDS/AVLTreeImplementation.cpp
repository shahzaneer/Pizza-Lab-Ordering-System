#include <iostream>
using namespace std;

// Structure for AVL Tree's Node

struct AVLNode
{

    int data;       // data for AVL node
    AVLNode *left;  // left child
    AVLNode *right; // right child
    int height;     // height of the Node

    // Constructor
    AVLNode(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

AVLNode *root = NULL; // Global pointer for the root of AVLTree

// isEmpty or not
int isEmpty(AVLNode *root)
{
    // Ger root NULL tou true werna False
    return root == NULL;
}

// Postorder Traversal in AVL Tree

void postorder(AVLNode *root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    //// else{
    ////     return;
    // it will aproach End of line
    // there are two ways of returning end of line + return statement
    // }
}

// Preorder Traversal in AVL Tree

void preorder(AVLNode *root)
{
    if (root)
    {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// inorder Traversal in AVL Tree
void inorder(AVLNode *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Height of AVL Tree

int height(AVLNode *root)
{
    if (!root)
        return 0;

    return max(height(root->left), height(root->right)) + 1;
}

// Balance Factor for Node

int balanceFactor(AVLNode *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}

// Maximum of two integers as a helper function for height
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Searching in AVL Tree
int search(AVLNode *root, int key)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (root->data == key)
    {
        return 1;
    }
    else if (root->data > key)
    {
        return search(root->right, key);
    }
    else if (root->data < key)
    {
        return search(root->left, key);
    }

    return 1;
}

// Finding Minimum Node of the AVL Tree

AVLNode *minAVLNode(AVLNode *root)
{
    // Minimum Node is Present in the most left Node of the Tree

    AVLNode *p = root;
    AVLNode *temp = NULL;

    while (p != NULL)
    {
        temp = p;
        p = p->left;
    }

    return temp;
}

// Finding Maximum Node of the AVL Tree

AVLNode *maxAVLNode(AVLNode *root)
{
    // Maximum Node is Present in the most Right Node  of the Tree

    AVLNode *p = root;
    AVLNode *temp = NULL;

    while (p != NULL)
    {
        temp = p;
        p = p->right;
    }

    return temp;
}

// finding minimum Value of AVL Tree

int minValueAVL(AVLNode *root)
{
    AVLNode *temp = minAVLNode(root);
    return temp->data;
}

// finding Maximum Value of AVL Tree

int maxValueAVL(AVLNode *root)
{
    AVLNode *temp = maxAVLNode(root);
    return temp->data;
}

// AVL Rotations
// Rotations k names insertion k names per diay gye hain unmay krna jo hai us basis per nhi diay gye!
// rotation ka code multiple childs ki condition ko maddenazar rkhte huay likhna hai

// LL Rotation
AVLNode *LLRotation(AVLNode *root)
// rotate wese right per krna hai!
{
    // saving the new root and the lost element in case of rotation
    AVLNode *x = root->left;
    AVLNode *temp = x->right;

    // Performing rotation
    x->right = root;
    root->left = temp;

    // updating the root
    root = x;
    // returning the root
    return x;
}

// RR Rotation
AVLNode *RRRotation(AVLNode *root)
{
    // rotate wese left per krna hai!

    // saving the new root and the lost element in case of rotation

    AVLNode *x = root->right;
    AVLNode *temp = x->left;

    // Performing rotation
    x->left = root;
    root->right = temp;

    // updating the root
    root = x;

    // returning the root
    return x;
}

// LR Rotation
AVLNode *LRRotation(AVLNode *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
AVLNode *RLRotation(AVLNode *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

//  INSERTION in AVL Tree

AVLNode *insertion(int value, AVLNode *root)
{

    AVLNode *newNode = new AVLNode(value); // dynamically declaring new Node and assigning value to it through Constructor

    // Insertion is just as the indertion in BST
    if (root == NULL)
    {
        root = newNode; // insertion Point
    }

    else if (root->data > value)
    {
        root->left = insertion(value, root->left);
    }
    else if (root->data < value)
    {
        root->right = insertion(value, root->right);
    }

    else
    {
        cout << "No duplicates Values are Allowed " << endl;
        return root;
    }

    // Now as the insertion is Done now to make the tree AVL (Balanced) we will perform Rotations
    int bf = balanceFactor(root);

    if (bf == 2)
    {
        // LL
        if (root->left->data > newNode->data)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->data < newNode->data)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        // RR
        if (root->right->data < newNode->data)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->data > newNode->data)
        {
            return RLRotation(root);
        }
    }

    return root; // in case there is no need of rotation
}

AVLNode *deleteNode(AVLNode *root, int key)
{
    //! intitial Deletion is same as of BST and then after deletion we will perform Balancing to keep AVLiness Alive!
    // firstly we have to search for the node which has to be deleted
    // then we will delete it accordingly
    // There are three main cases for the deletion
    // Node with 0 child -> simply delete the node
    // Node with 1 child -> make the Parent of node point to the child of node and delete node
    // Node with 2 childs-> findout the inorder predeccesor(The largest element in LST) or inorder successor (The smallest element oin the RST)
    // and copy the contents of to be deleted node and then delete the inorder predeccessor or inorder successor (which was used earlier)
    if (root == NULL)
    {
        return root;
    }
    else if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // It means that we have found our node to be deleted and now its the time to delete the node

        AVLNode *temp = NULL;
        // case 1: 0 child
        if (!root->left && !root->right)
        {
            delete root;
            root = NULL; // segmentation Fault (root dangling hogya tha aur tree lost! bht dhayan rkhna hai iska)
        }
        // case 2: 1 child
        else if (!root->left && root->right)
        {
            root = temp;
            root = root->right;
            delete temp;
        }
        else if (!root->right && root->left)
        {
            root = temp;
            root = root->left;
            delete temp;
        }
        else
        {
            temp = maxAVLNode(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data);
        }

        // Now start Balancing the root!

        int bf = balanceFactor(root);

        if (bf == 2)
        {
            // LL
            if (root->left->left)
            {
                return LLRotation(root);
            }

            // LR

            else
            {
                return LRRotation(root);
            }
        }
        else if (bf == -2)
        {
            // RR
            if (root->right->right)
            {
                return RRRotation(root);
            }

            // RL
            else
            {
                return RLRotation(root);
            }
        }
    }

    return root; // in case there is no need of rotation
}

int main()
{

    root = insertion(34, root);
    root = insertion(12, root);
    root = insertion(50, root);
    root = insertion(10, root);
    root = insertion(5, root);
    root = insertion(1, root);

    cout << "Inorder Traversal of AVL Tree is : " << endl;

    inorder(root);

    root = deleteNode(root, 1);

    cout << "Inorder Traversal of AVL Tree is : " << endl;
    inorder(root);

    return 0;
}