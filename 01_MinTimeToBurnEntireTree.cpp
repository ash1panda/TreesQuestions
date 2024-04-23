/*
Once we Burn a Node (its neighbour nodes are also burnt and it takes 1 second)
*/

/*
Input:      
          1
        /   \
      2      3
    /  \      \
   4    5      7
  /    / 
 8    10
Create Tree Input -  1 2 4 8 -1 -1 -1 5 10 -1 -1 -1 3 -1 7 -1 -1
Target Node = 10
Output: 5
*/
#include<iostream>
#include<map>
#include<queue>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    //Parameterised Constructor
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

Node* nodeToParentMapping(Node* root, int target, map<Node*, Node*>& nodeToParentmp) {
    Node* res = nullptr;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left) {
            nodeToParentmp[temp->left] = temp;
            q.push(temp->left);
        }
        if (temp->right) {
            nodeToParentmp[temp->right] = temp;
            q.push(temp->right);
        }

        if (temp->data == target) {
            res = temp;
        }
    }
    return res;
}

void burnTree(Node* root, map<Node*, Node*>& nodeToParentmp, int& ans) {
    queue<Node*> q;
    map<Node*, bool> visited;

    q.push(root);
    visited[root] = true;

    while (!q.empty()) {
        int size = q.size();
        bool flag = false;

        for (int i = 0; i < size; i++) {
            Node* temp = q.front();
            q.pop();

            if (temp->left && !visited[temp->left]) {
                q.push(temp->left);
                visited[temp->left] = true;
                flag = true;
            }
            if (temp->right && !visited[temp->right]) {
                q.push(temp->right);
                visited[temp->right] = true;
                flag = true;
            }
            if (nodeToParentmp[temp] && !visited[nodeToParentmp[temp]]) {
                q.push(nodeToParentmp[temp]);
                visited[nodeToParentmp[temp]] = true;
                flag = true;
            }
        }

        if (flag) {
            ans++;
        }
    }
}

Node* createTree() {
    int val;
    cout << "Enter the value of node: ";
    cin >> val;
    if (val == -1) {
        return NULL;
    }

    Node* root = new Node(val);

    cout << endl << "Entering Left Of Node " << val << " ";
    root->left = createTree();

    cout << endl << "Entering Right Of Node " << val << " ";
    root->right = createTree();

    return root;
}

int main() {
    Node* root = createTree();
    int target = 10;
    map<Node*, Node*> nodeToParentmp;
    Node* targetNode = nodeToParentMapping(root, target, nodeToParentmp);

    if (!targetNode) {
        cout << "Target node not found in the tree!";
        return 0;
    }

    int ans = 0;
    burnTree(targetNode, nodeToParentmp, ans);

    cout << endl << endl << "Time required to burn the entire tree: " << ans << " seconds.";

    

    return 0;
}
