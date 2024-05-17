#include <iostream>
#include <string> 
using namespace std;

struct Tree {
    int key; 
    string info; 
    Tree* left, * right;
} *root = NULL;

Tree* List(int key, string info) {
    Tree* t = new Tree;
    t->key = key;
    t->info = info;
    t->left = t->right = NULL;
    return t;
}


void Add_List(Tree*& root, int key, string info) {
    if (root == NULL) {
        root = List(key, info);
    }
    else if (key < root->key) {
        Add_List(root->left, key, info);
    }
    else if (key > root->key) {
        Add_List(root->right, key, info);
    }
    else {
        cout << "Duplicate Key!" << endl;
    }
}

Tree* Search(Tree* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key)
        return Search(root->right, key);
    return Search(root->left, key);
}
void Delete_Subtree(Tree*& root, int key) {
    if (root == nullptr) return;
    if (key < root->key) {
        Delete_Subtree(root->left, key);
    }
    else {
        Delete_Subtree(root->right, key);
        Delete_Subtree(root->left, INT_MIN); 
        delete root; 
        root = NULL; 
    }
}


Tree* Delete_Node(Tree* root, int key) {
    if (root == NULL) return root;

    if (key < root->key) { 
        root->left = Delete_Node(root->left, key);
    }
    else if (key > root->key) { 
        root->right = Delete_Node(root->right, key);
    }
    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Tree* temp = root->left;
            delete root;
            return temp;
        }
        Tree* temp = root->right;
        while (temp && temp->left != NULL) temp = temp->left;
        root->key = temp->key; 
        root->info = temp->info; 
        root->right = Delete_Node(root->right, temp->key);
    }
    return root;
}

void PrintPreOrder(Tree* root) {
    if (root == NULL) return;
    cout << root->key << ": " << root->info << endl;
    PrintPreOrder(root->left); 
    PrintPreOrder(root->right); 
}

void PrintPostOrder(Tree* root) {
    if (root == NULL) return;
    PrintPostOrder(root->left); 
    PrintPostOrder(root->right); 
    cout << root->key << ": " << root->info << endl; 
}

void PrintInOrder(Tree* root) {
    if (root == NULL) return;
    PrintInOrder(root->left); 
    cout << root->key << ": " << root->info << endl; 
    PrintInOrder(root->right); 
}

void Print_Tree_Inorder(Tree* root) {
    if (root != NULL) {
        Print_Tree_Inorder(root->left);
        cout << root->key << ": " << root->info << endl;
        Print_Tree_Inorder(root->right);
    }
}

int Count(Tree* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) 
    {
        return 0;
    }
    if (root->left == NULL || root->right == NULL) 
    {
        return 1 + Count(root->left) + Count(root->right);
    }
    else 
    {
        return Count(root->left) + Count(root->right);
    }
    
}

int main() {
    bool go = true;
    while (go) {
        cout << "МЕНЮ:" << endl;
        cout << "1. Добавление элемента" << endl;
        cout << "2. Найти информацию по заданному ключу" << endl;
        cout << "3. Удалить информацию с заданным ключом" << endl;
        cout << "4. Вывести прямым обходом" << endl;
        cout << "5. Вывести обратным обходом" << endl;
        cout << "6. Вывести в порядке возрастания ключа" << endl;
        cout << "7. Показать число узлов с 1 сыном" << endl;
        cout << "8. Выход" << endl;
        cout << "9. Удалить элемент и его поддерево" << endl;
        cout << "Выберите один из пунктов:" << endl;

        int choice, key;
        string info;
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Введите ключ (например, номер паспорта): ";
            cin >> key;
            cin.ignore();
            cout << "Введите информацию (ФИО): ";
            getline(cin, info); 
            Add_List(root, key, info);
            cout << "" << endl;
            break;
        }
        case 2: {
            cout << "Введите ключ для поиска: ";
            cin >> key;
            Tree* found = Search(root, key);
            if (found != nullptr) {
                cout << "Найдено: " << found->info << endl;
            }
            else {
                cout << "Ключ не найден." << endl;
            }
            cout << "" << endl;
            break;
        }
        case 3: {
            cout << "Введите ключ для удаления: ";
            cin >> key;
            root = Delete_Node(root, key);
            cout << "Элемент удален (если был найден)." << endl;
            cout << "" << endl;
            break;
        }
        case 4: {
            PrintPreOrder(root);
            cout << "" << endl;
            break;
        }
        case 5: {
            PrintPostOrder(root);
            cout << "" << endl;
            break;
        }
        case 6: {
            PrintInOrder(root);
            cout << "" << endl;
            break;
        }
        case 7: {
            int count = Count(root);
            cout << "Количество узлов с одним ребенком: " << count << endl;
            cout << "" << endl;
            break;
        }
        case 8: {
            go = false;
            break;
        }
        case 9:
            cout << "Введите ключ (например, номер паспорта): ";
            cin >> key;
            Delete_Subtree(root, key);
            break;
        default: {
            cout << "Некорректный ввод. Пожалуйста, попробуйте снова." << endl;
            cout << "" << endl;
            break;
        }
        }
    }
    return 0;
}