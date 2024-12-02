#include <iostream>
using namespace std;

class BTreeNode{
	public:
		int * keys;
		int t;
		BTreeNode ** C;
		int n;
		bool leaf;
		
		BTreeNode(int t1 , bool leaf1){
			t = t1;
			leaf = leaf1;
			keys = new int[2 * t -1];
			C = new BTreeNode * [2*t];
			n=0;
		}
};

class BTree{
	public:
		BTreeNode * root;
		int t;
		BTree(int t1){
			root = NULL;
			t = t1;
		}
		
		void traverse(BTreeNode * node){
			for(int i=0; i <node->n ; i++){
				if(!node->leaf){
					traverse(node->C[i]);
				}
				cout<<" "<<node->keys[i];
			}
			if(!node -> leaf){
				traverse(node -> C[node->n]);
			}
		}
		
		void splitchild(BTreeNode *parent, int i, BTreeNode *y) {
		    BTreeNode *z = new BTreeNode(y->t, y->leaf);
		    z->n = t - 1;
		
		    for (int j = 0; j < t - 1; j++) {
		        z->keys[j] = y->keys[j + t];
		    }
		
		    if (!y->leaf) {
		        for (int j = 0; j < t; j++) {
		            z->C[j] = y->C[j + t];
		        }
		    }
		
		    y->n = t - 1;
		
		    for (int j = parent->n; j >= i + 1; j--) {
		        parent->C[j + 1] = parent->C[j];
		    }
		    parent->C[i + 1] = z;
		
		    for (int j = parent->n - 1; j >= i; j--) {
		        parent->keys[j + 1] = parent->keys[j];
		    }
		    parent->keys[i] = y->keys[t - 1]; 
		    parent->n++;
		}
		
		void insertNonFull(BTreeNode *node, int elem) {
		    int i = node->n - 1;
		    if (node->leaf) {
		        while (i >= 0 && node->keys[i] > elem) {
		            node->keys[i + 1] = node->keys[i];
		            i--;
		        }
		        node->keys[i + 1] = elem;
		        node->n++;
		    } else {
		        while (i >= 0 && node->keys[i] > elem) {
		            i--;
		        }
		        if (node->C[i + 1]->n == 2 * t - 1) {
		            splitchild(node, i + 1, node->C[i + 1]);
		            if (node->keys[i + 1] < elem) {
		                i++;
		            }
		        }
		        insertNonFull(node->C[i + 1], elem);
		    }
		}
		
		void insert(int elem){
			if(root == NULL){
				root = new BTreeNode(t , true);
				root->keys[0] = elem;
				root->n = 1;
			}
			else{
				if(root->n == 2 * t - 1){
					BTreeNode *s = new BTreeNode(t , false);
					s->C[0] = root;
					splitchild(s,0,root);
					int i = 0;
					if(s->keys[0] < elem){
						i++;
					}
					insertNonFull (s->C[i] , elem);
					root = s;
				}
				else{
					insertNonFull(root , elem);
				}
			}
		}
		
		void remove(int elem){
			if(!root){
				cout<<"Tree is empty"<<endl;
				return;
			}
			
			remove(root , elem);
			
			if(root->n==0){
				BTreeNode * tmp = root;
				if(root->leaf){
					root = NULL;
				}
				else{
					root = root->C[0];
				}
				delete tmp;
			}
		}
		
		int findkey(BTreeNode * node , int elem){
			int idx = 0;
			while(idx < node->n && node->keys[idx] < elem){
				idx++;
			}
			return idx;
		}
		
		void merge(BTreeNode *node, int idx) {
		    BTreeNode *child = node->C[idx];
		    BTreeNode *sibling = node->C[idx + 1];
		
		    child->keys[t - 1] = node->keys[idx];
		
		    for (int i = 0; i < sibling->n; i++) {
		        child->keys[i + t] = sibling->keys[i];
		    }
		    if (!child->leaf) {
		        for (int i = 0; i <= sibling->n; i++) {
		            child->C[i + t] = sibling->C[i];
		        }
		    }
		
		    for (int i = idx + 1; i < node->n; i++) {
		        node->keys[i - 1] = node->keys[i];
		    }
		
		    for (int i = idx + 2; i <= node->n; i++) {
		        node->C[i - 1] = node->C[i];
		    }
		
		    child->n += sibling->n + 1;
		    node->n--;
		
		    delete sibling;
		}
		
		void borrowFromPrev(BTreeNode *node, int idx) {
		    BTreeNode *child = node->C[idx];
		    BTreeNode *sibling = node->C[idx - 1];
		
		    for (int i = child->n - 1; i >= 0; --i) {
		        child->keys[i + 1] = child->keys[i];
		    }
		
		    if (!child->leaf) {
		        for (int i = child->n; i >= 0; --i) {
		            child->C[i + 1] = child->C[i];
		        }
		    }
		
		    child->keys[0] = node->keys[idx - 1];
		
		    if (!child->leaf) {
		        child->C[0] = sibling->C[sibling->n];
		    }
		
		    node->keys[idx - 1] = sibling->keys[sibling->n - 1];
		
		    child->n++;
		    sibling->n--;
		}
		
		void borrowFromNext(BTreeNode *node, int idx) {
		    BTreeNode *child = node->C[idx];
		    BTreeNode *sibling = node->C[idx + 1];
		
		    child->keys[child->n] = node->keys[idx];
		
		    if (!child->leaf) {
		        child->C[child->n + 1] = sibling->C[0];
		    }
		
		    node->keys[idx] = sibling->keys[0];
		
		    for (int i = 1; i < sibling->n; ++i) {
		        sibling->keys[i - 1] = sibling->keys[i];
		    }
		
		    if (!sibling->leaf) {
		        for (int i = 1; i <= sibling->n; ++i) {
		            sibling->C[i - 1] = sibling->C[i];
		        }
		    }
		
		    child->n++;
		    sibling->n--;
		}
		
		void fill(BTreeNode *node, int idx) {
		    if (idx != 0 && node->C[idx - 1]->n >= t) {
		        borrowFromPrev(node, idx);
		    } else if (idx != node->n && node->C[idx + 1]->n >= t) {
		        borrowFromNext(node, idx);
		    } else {
		        if (idx != node->n) {
		            merge(node, idx);
		        } else {
		            merge(node, idx - 1);
		        }
		    }
		}
		
		void removeFromLeaf(BTreeNode *node, int idx) {
		    for (int i = idx + 1; i < node->n; i++) {
		        node->keys[i - 1] = node->keys[i];
		    }
		    node->n--;
		}
		
		void removeFromNonLeaf(BTreeNode *node, int idx) {
		    int k = node->keys[idx];
		    if (node->C[idx]->n >= t) {
		        int pred = node->C[idx]->keys[node->C[idx]->n - 1];
		        node->keys[idx] = pred;
		        remove(node->C[idx], pred);
		    } else if (node->C[idx + 1]->n >= t) {
		        int succ = node->C[idx + 1]->keys[0];
		        node->keys[idx] = succ;
		        remove(node->C[idx + 1], succ);
		    } else {
		        merge(node, idx);
		        remove(node->C[idx], k);
		    }
		}
		
		void remove(BTreeNode * node , int elem){
			int idx = findkey(node , elem);
			if (idx < node->n && node->keys[idx] == elem) {
		        if (node->leaf) {
		            removeFromLeaf(node, idx);
		        } else {
		            removeFromNonLeaf(node, idx);
		        }
		    } 
			else {
		        if (node->leaf) {
		            cout << "The key " << elem << " does not exist in the tree.\n";
		            return;
		        }
		
		        bool flag = (idx == node->n);
		        if (node->C[idx]->n < t) {
		            fill(node, idx);
		        }
		        if (flag && idx > node->n) {
		            remove(node->C[idx - 1], elem);
		        } else {
		            remove(node->C[idx], elem);
		        }
		    }
		}
		
		
};

int main() {
    BTree t(5); 

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of tree constructed is:\n";
    t.traverse(t.root);
    cout << endl;

    t.remove(6);
    cout << "Traversal of tree after removal of 6:\n";
    t.traverse(t.root);
    cout << endl;

    t.remove(13);
    cout << "Traversal of tree after removal of 13:\n";
    t.traverse(t.root);
    cout << endl;

    t.remove(7);
    cout << "Traversal of tree after removal of 7:\n";
    t.traverse(t.root);
    cout << endl;

    t.remove(4);
    cout << "Traversal of tree after removal of 4:\n";
    t.traverse(t.root);
    cout << endl;

    t.remove(2);
    cout << "Traversal of tree after removal of 2:\n";
    t.traverse(t.root);
    cout << endl;

    t.remove(16);
    cout << "Traversal of tree after removal of 16:\n";
    t.traverse(t.root);
    cout << endl;

    return 0;
}
		
