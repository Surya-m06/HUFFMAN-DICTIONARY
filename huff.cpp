#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    float P_x;
    string code = "";
    struct Node* forward;
    struct Node* backward_left;
    struct Node* backward_right;
    Node(int Data, float PX) { 
        data = Data;
        P_x = PX;
        forward = NULL;
        backward_left = NULL;
        backward_right = NULL;
    }
};
bool compare(struct Node* A, struct Node* B) {
    return A->P_x > B->P_x; 
}
void Traversal(struct Node* root, string Code = "") {
    if (root == NULL) { return;}
    if (root->backward_left == NULL && root->backward_right == NULL) {
        root->code = Code;
        cout << "Symbol: " << root->data << " -> " << Code << endl;  
    }
    Traversal(root->backward_left, Code + "0");
    Traversal(root->backward_right, Code + "1");
}
int main() {
    int Symbols[5] = {3, 1, 2, 4, 5};
    float PX[5] = {0.4, 0.2, 0.2, 0.1, 0.1};
    vector<Node*> node;
    int Size = sizeof(Symbols) / sizeof(Symbols[0]);
    for (int i = 0; i < Size; i++) {
        node.push_back(new Node(Symbols[i], PX[i]));
    }
    while (node.size() > 1) {
        sort(node.begin(), node.end(), compare); 
        for (int i = 0; i < node.size(); i++) {
            cout<<node[i]->P_x<<"("<<node[i]->data<<") ";
        }cout<<endl;
        struct Node* right = node.back();
        node.erase(node.end());
        struct Node* left = node.back();
        node.erase(node.end());
        struct Node* NewNode = new Node(0, left->P_x + right->P_x);
        NewNode->backward_left = left;
        NewNode->backward_right = right;
        left->forward = NewNode;
        right->forward = NewNode;
        node.push_back(NewNode);
    }
    Traversal(node[0]);
    return 0;
}
