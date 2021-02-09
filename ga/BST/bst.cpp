#include<iostream>
using namespace std;

//The definition of a tree chunk
//it has two pointers, one to the left and one to the right

class TreeChunk {
public:
    int value;
    TreeChunk *left;
    TreeChunk *right;

    //constructor
    TreeChunk() {
        value = 0;
        left = right = NULL;
    }
};

class BST {
public:
    TreeChunk *root;

    BST() {
        root = NULL;
    }

    void searchBST(int key) {
        if(root == NULL){
            cout << "Nothing to see here.  Empty tree" << endl;
            return;
        }
        TreeChunk *temp = root; //copy of root pointer, can drive this around
        //end game: you won't find it and you'll fall off the tree
        while(temp != NULL){
            //scenario 1: you found it
            if(temp->value == key) {
                cout << "Found the value" << endl;
                return;
            }
            else if(temp->value < key){ //the node we're on is smaller than the key, go right
                temp = temp->right;
            }
            else {
                //temp->value > key
                temp = temp->left;
            }
        }
        if(temp == NULL) {
            //you fell off the tree, meaning this value does not exist
            cout << "Could not find the value" << endl;
        }

    }

    void addNode(int val){
        //every new value is a LEAF node
        //step1: Begin a search for that value
        //step2: If you find it, don't add it
        //step3: If you don't find it (i.e. you fall off the tree), that's where you add this new value

        //a) get the pointers, set them to root
        TreeChunk *chase, *follow;
        chase = follow = root;

        //b) get a brand new TreeChunk from the heap, and prepare for addition
        TreeChunk *temp = new TreeChunk;
        temp->value = val;

        if(root == NULL){
            //tree is empty, set the new value as root
            root = temp;
        }
        else {
            //chase is the faster pointer, and follow shadows chase
            while(chase != NULL) {
                if(chase->value == val) {
                    //duplicate! We won't add this
                    cout << "Duplicate, not adding this" << endl;
                    return;
                }
                else if(chase->value < val) {
                    follow = chase;
                    chase = chase->right;
                }
                else {
                    //this is when chase->value > key
                    follow = chase;
                    chase = chase->left;
                }
            }
            if(chase == NULL) {
                //do I add this new value to the left or to the right?
                //follow has the address of the parent of the new node to be
                if(follow->value > val)
                    follow->left = temp;
                else
                    follow->right = temp;
            }
        }
    }

    void deleteNode(int val, TreeChunk *start){
        //Step1: Find the value
        //Use two pionters (chase and follow)
        //'chase' points to the node you want to delete, follow points to the parent
        TreeChunk *chase, *follow;
        chase = follow = start;

        if(start == NULL) {
            cout << "Empty tree, nothing to delete" << endl;
        }
        else {
            while((chase->value != val) && (chase != NULL)) {
                if(chase->value < val) {
                    follow = chase;
                    chase = chase->right;
                }
                else {
                    follow = chase;
                    chase = chase->left;
                }
            }
            //you'll now figure out if the value exists in this tree
            if(chase == NULL) {
                //you fell off the tree, meaning this value does not exist
                cout << "Value not found" << endl;
                return;
            }
            //if you get past that if-statement, this value was found
            //---------------------------------------------------------
            //Step2: Figure out if it's case 1, 2, or 3
            //---------------------------------------------------------
            
            //CASE 1:
            //if both the left and right pointers are null, then it's case 1, no children
            if(chase->left == NULL && chase->right == NULL) {
                if(follow->value < chase->value) {
                    //chase is to the right, because its value is more than follow's
                    follow->right = NULL;
                    cout << "Found it, about to delete: " << chase->value << endl;
                    delete chase;
                }
                else {
                    follow->left = NULL;
                    cout << "Found it, about to delete: " << chase->value << endl;
                    delete chase;
                }
            }
            //CASE 2:
            //One of the left or right pointers is null
            else if((chase->left != NULL && chase->right == NULL) || (chase->left == NULL && chase->right != NULL)) {
                //1. Where is chase with respect to follow?
                //2. Where is the lone child with respect to chase?
                if(follow->value > chase->value) {
                    //chase is to the left
                    if(chase->left == NULL) {
                        //the child is to the right
                        //1. chase is to the left of follow
                        //2. chase lone child is to the right
                        follow->left = chase->right;
                        delete chase;
                    }
                    else {
                        //the child is to the left
                        follow->left = chase->left;
                        delete chase;
                    }
                }
                else {
                    //chase is to the right
                    if(chase->left == NULL) {
                        //lone child is to the right
                        follow->right = chase->right;
                        delete chase;
                    }
                    else {
                        //lone child to the left
                        follow->right = chase->left;
                        delete chase;
                    }
                }
            }
            //CASE 3:
            //your goal is to reduce case 3 to case 1
            else {
                int replacement = minValRST(chase->right);
                deleteNode(replacement, chase);
                chase->value = replacement;
                //chase->value = replacement;
                //set chase->value = replacement
                //at this point, this tree is not a BST momentarily
                //deleteNode(replacement, chase->right);
            }
        }
    }

    //helper function to find the minimum value of the right subtree for use in case 3
    int minValRST(TreeChunk *start) {
        TreeChunk *temp = start;
        while(temp->left != NULL) {
            temp = temp->left;
        }
        return temp->value;
    }

    //1. In-Order traversal -- left, root, right
    void inOrder(TreeChunk *start) {
        if(start == NULL)
            return;
        else {
            //visit left
            inOrder(start->left);
            //visit root
            cout << start->value << endl;
            //visit right
            inOrder(start->right);
        }
    }
    //2. Pre-Order -- root, left, right
    void preOrder(TreeChunk *start) {
        if(start == NULL)
            return;
        else {
            cout << start->value << endl;
            preOrder(start->left);
            preOrder(start->right);
        }
    }
    //3. Post-Order -- left, right, root
    void postOrder(TreeChunk *start) {
        if(start == NULL)
            return;
        else {
            postOrder(start->left);
            postOrder(start->right);
            cout << start->value << endl;
        }
    }
};

//The functions of a tree are all dependent on the height of the tree.
//The maximum benefits of the tree are reached when the height is log base 2 of the number of elements in the tree.
int main() {
    BST myTree;
    int choice, value;

    while(1) {
        cout << "1 to add" << endl;
        cout << "2 to search" << endl;
        cout << "3 to delete" << endl;
        cout << "4 to view in-order" << endl;
        cout << "5 to view post-order" << endl;
        cout << "6 to view pre-order" << endl;
        cin >> choice;
        switch(choice) {
            case 1: 
                cout << "What?" << endl;
                cin >> value;
                myTree.addNode(value);
                break;
            case 2:
                cout << "What?" << endl;
                cin >> value;
                myTree.searchBST(value);
                break;
            case 3:
                cout << "What?" << endl;
                cin >> value;
                myTree.deleteNode(value, myTree.root);
                break;
            case 4:
                myTree.inOrder(myTree.root);
                break;
            case 5:
                myTree.postOrder(myTree.root);
                break;
            case 6:
                myTree.preOrder(myTree.root);
                break;
        }
    }
    return 1;
}