#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
#include <QRectF>
#include <QPainter>

using namespace std;

template <class T>
class arrList {
private:
    QRectF* unit;
    T* aList;
    int maxSize;
    int curLen;
    int pos;
public:
    arrList(const int size,int x,int y){
        maxSize=size;
        aList=new T[size];
        unit=new QRectF[size];
        for(int i=0;i<size;i++)
            unit[i].setRect(x*(i+1),y,20,20);
        curLen=pos=0;
    }
    ~arrList(){
        delete [] aList;
        delete [] unit;
    }
    void clear(){
        int x,y;
        x=unit[0].x();
        y=unit[0].y();
        delete [] aList;
        delete [] unit;
        curLen=pos=0;
        aList=new T[maxSize];
        unit=new QRectF[maxSize];
        for(int i=0;i<maxSize;i++)
            unit[i].setRect(x*(i+1),y,20,20);
    }
    int length(){return curLen;}
    bool append(const T value){
        if(curLen<maxSize){
            aList[curLen]=value;
            curLen++;
            return true;
        }
        return false;
    }
    bool insert(const int p,const T value){
        if(curLen>=maxSize) return false;
        if(p<0||p>curLen) return false;
        else{
            for(int i=curLen;i>p;i--){
                aList[i]=aList[i-1];
            }
            aList[p]=value;
            curLen++;
            return true;
        }

    }
    bool delete_(const int p){
        if(curLen<=0) return false;
        if(p<0||p>curLen-1) return false;
        for(int i=p;i<curLen-1;i++){
            aList[i]=aList[i+1];
        }
        curLen--;
        return true;
    }
    bool setValue(const int p,const T value){
        if(curLen<=0) return false;
        if(p<0||p>curLen-1) return false;
        aList[p]=value;
        return true;
    }
    bool getValue(const int p,const T& value){
        if(curLen<=0) return false;
        if(p<0||p>curLen-1) return false;
        value=aList[p];
        return true;
    }
    bool getPos(int& p,const T value){
        for(int i=0;i<curLen;i++){
            if(value==aList[i]){
                pos=i;
                return true;
            }
        }
        return false;
    }
    //显示顺序表的图形化形式
    void draw_arrList(QPainter &p){
        int i;
        for(i=0;i<curLen;i++){
            p.drawRect(unit[i]);
            p.drawText(unit[i],Qt::AlignCenter,aList[i],nullptr);
        }
    }
};



template <class T>
class Link{
private:
    T value;
    Link<T>* next;
public:
    Link(const T info,const Link<T>* next=NULL){
        value=info;
        this->next=next;
    }
    Link(const Link<T>* next=NULL){
        this->next=next;
    }
};

template <class T>
class linkList{
private:
    Link<T>* head,tail;
    Link<T>* getPos(const int p){
        int count=0;
        if(p==-1) return head;
        Link<T>* a=new Link<T>(head->next);
        while(a!=NULL&&count<p){
            a=a->next;
            count++;
        }
        return a;
    }
public:
    linkList(int size){
        head=tail=new Link<T>();
    }
    ~linkList(){
        Link<T>* tmp;
        while(head!=NULL){
            tmp=head;
            head=head->next;
            delete tmp;
        }
    }
    void clear(){
        Link<T>* tmp;
        while(head!=NULL){
            tmp=head;
            head=head->next;
            delete tmp;
        }
        head=tail=new Link<T>();
    }
    int length(){
        Link<T>* tmp;
        int len=0;
        tmp=head->next;
        while(tmp!=NULL){
            tmp=tmp->next;
            len++;
        }
        return len;
    }
    bool append(const T value){
        Link<T>* tmp=new Link<T>(value);
        if(tail!=NULL){
            tail->next=tmp;
            tail=tmp;
        }
        else{
            head->next=tmp;
            tail=tmp;
        }
        return true;
    }
    bool insert(const int p,const T value){
        Link<T>* a,b;
        if((a=getPos(p-1))==NULL) return false;
        b=new Link<T>(value,a->next);
        a->next=b;
        if(a==tail)
            tail=b;
        return true;
    }
    bool delete_(const int p){
        Link<T>* a,b;
        if((a=getPos(p-1))==NULL||a==tail) return false;
        b=a->next;
        if(b==tail){
            tail=a;
            a->next=NULL;
            delete a;
        }
        else if(b!=NULL){
            a->next=b->next;
            delete b;
        }
        return true;
    }
    bool getValue(const int p,T& value){
        int count=0;
        Link<T>* tmp=head->next;
        if(getPos(p-1)==NULL||getPos(p-1)==tail) return false;
        while(tmp->next!=NULL&&count<p){
            tmp=tmp->next;
            count++;
        }
        value=tmp->value;
        return true;
    }
    bool getValue_pos(int &p,const T value){
        int count=0;
        Link<T>* tmp=head->next;
        while(tmp!=NULL&&tmp->value!=value){
            tmp=tmp->next;
            count++;
        }
        if(tmp==NULL) return false;
        p=count;
        return true;
    }
    bool isEmpty(){
        if(head->next==NULL) return false;
        return true;
    }
};

template <class T>
class linkStack {
private:
    Link<T>* top;
    int size;
public:
    linkStack(int size){
        this->size=0;
        top=NULL;
    }
    ~linkStack(){clear();};
    void clear(){
        while(top!=NULL){
            Link<T>* tmp=top;
            top=top->next;
            delete tmp;
        }
        size=0;
    }
    bool push(const T value){
        top=new Link<T>(value,top);
        size++;
        return true;
    }
    bool pop(const T& item){
        if(size==0) return false;
        item=top->value;
        Link<T>* tmp=top->next;
        delete top;
        top=tmp;
        size--;
        return true;
    }
    bool get_top(const T& item){
        if(size==0) return false;
        item=top->value;
        return true;
    }
    bool isEmpty(){
        if(size==0&&top==NULL) return true;
    }
};

template <class T>
class arrQueue {
private:
    int front;
    int rear;
    T* qu;
public:
    int mSize;
    arrQueue() { qu = NULL; }
    arrQueue(int size) {
        mSize = size + 1;
        qu = new T[mSize];
        front = rear = 0;
    }
    ~arrQueue() {
        delete[] qu;
    }
    bool enqueue(const T item) {
        if ((rear + 1) % mSize == front)
            return false;
        qu[rear] = item;
        rear = (rear + 1) % mSize;
        return true;
    }
    bool dequeue(T& item) {
        if (front == rear) return false;
        item = qu[front];
        front = (front + 1) % mSize;
        return true;
    }
    bool isempty() {
        if (front == rear) return true;
        return false;
    }
    void Delete(int s, T& tmp) {
        T* q = new T[s];
        T tmp1;
        for (int i = 0; i < s - 1; i++) {
            dequeue(tmp1);
            enqueue(tmp1);
        }
        dequeue(tmp);
    }
};

template <class T>
class arrStack {
private:
    int mSize;
    int top;
    T* st;
public:
    arrStack(int size) {
        top = -1;
        mSize = size;
        st = new T[size];
    }
    arrStack() { top = -1; st = NULL; }
    ~arrStack() { delete[]st; }
    bool push(const T item) {
        if (top == mSize - 1)
            return false;
        st[++top] = item;
        return true;
    }
    bool pop(T& item) {
        if (top == -1)
            return false;
        item = st[top--];
        return true;
    }
    bool Top(T& item) {
        if (top == -1)
            return false;
        item = st[top];
        return true;
    }
    bool empty() {
        if (top == -1)
            return true;
        return false;
    }
};

template <class T>
void visit(T n) { if (n != '#')cout << n; }
class Graph; void Visit(Graph g, int n);

template <class T>
class BinaryTreeNode;

template <class T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;
public:
    BinaryTree() : root(NULL) {}
    ~BinaryTree() { DeleteBinaryTree(root); }
    BinaryTreeNode<T>* Root() { return root; }
    bool isEmpty() const;
    BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
    void CreateTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree);
    void preorder(BinaryTreeNode<T>* root);
    void inorder(BinaryTreeNode<T>* root);
    void postorder(BinaryTreeNode<T>* root);
    void levelorder(BinaryTreeNode<T>* root);
    void DeleteBinaryTree(BinaryTreeNode<T>* root);
    void Create(T BT[]);
    int high(BinaryTreeNode<T>* root);
};

template <class T>
class BinaryTreeNode {
    friend class BinaryTree<T>;
private:
    T info;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
public:
    BinaryTreeNode() : left(NULL), right(NULL) {}
    BinaryTreeNode(const T& ele) : info(ele), left(NULL), right(NULL) {}
    BinaryTreeNode(const T& ele, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) {
        info = ele; left = l; right = r;
    }
    T value() const { return info; }
    void setvalue(const T& item) { info = item; }
    BinaryTreeNode<T>* leftchild() const { return left; }
    BinaryTreeNode<T>* rightchild() const { return right; }
};

template <class T>
bool BinaryTree<T>::isEmpty() const {
    return (root != NULL ? false : true);
}
template <class T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current) {
    arrStack<BinaryTreeNode<T>*> aStack;
    BinaryTreeNode<T>* pointer = root;
    if (root != NULL && current != NULL) {
        while (!aStack.empty()) {
            if (pointer != NULL) {
                if (current == pointer->leftchild() || current == pointer->rightchild())
                    return pointer;
                aStack.push(pointer);
                pointer = pointer->leftchild();
            }
            else {
                aStack.pop(pointer);
                pointer = pointer->rightchild();
            }
        }
    }
}
template <class T>
void BinaryTree<T>::CreateTree(const T& info, BinaryTree<T>& lefttree, BinaryTree<T>& righttree) {
    root = new BinaryTreeNode<T>(info, lefttree.root, righttree.root);
    lefttree.root = righttree.root = NULL;
}
template <class T>
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* root) {
    if (root != NULL) {
        DeleteBinaryTree(root->left);
        DeleteBinaryTree(root->right);
        delete root;
    }
}
template <class T>
void BinaryTree<T>::preorder(BinaryTreeNode<T>* root) {
    /*	if(root!=NULL) {
            visit(root->value());
            preorder(root->leftchild());
            preorder(root->rightchild());
        }
    */
    arrStack<BinaryTreeNode<T>*> aStack(105);
    BinaryTreeNode<T>* pointer = root;
    aStack.push(NULL);
    while (pointer != NULL) {
        visit(pointer->value());
        if (pointer->rightchild() != NULL)
            aStack.push(pointer->rightchild());
        if (pointer->leftchild() != NULL)
            pointer = pointer->leftchild();
        else {
            aStack.pop(pointer);
        }
    }
}
template <class T>
void BinaryTree<T>::inorder(BinaryTreeNode<T>* root) {
    /*	if(root!=NULL) {
            inorder(root->leftchild());
            visit(root->value());
            inorder(root->rightchild());
        }
    */
    arrStack<BinaryTreeNode<T>*> aStack(105);
    BinaryTreeNode<T>* pointer = root;
    while (!aStack.empty() || pointer != NULL) {
        if (pointer != NULL) {
            aStack.push(pointer);
            pointer = pointer->leftchild();
        }
        else {
            aStack.pop(pointer);
            visit(pointer->value());
            pointer = pointer->rightchild();
        }
    }

}
enum Tags { Left, Right };
template <class T>
class StackElement {
public:
    BinaryTreeNode<T>* pointer;
    enum Tags tag;
};
template <class T>
void BinaryTree<T>::postorder(BinaryTreeNode<T>* root) {
    /*	if(root!=NULL) {
            postorder(root->leftchild());
            postorder(root->rightchild());
            visit(root->value());
        }
    */
    StackElement<T> element;
    arrStack<StackElement<T> > aStack(105);
    BinaryTreeNode<T>* pointer = root;
    while (!aStack.empty() || pointer != NULL) {
        while (pointer != NULL) {
            element.pointer = pointer;
            element.tag = Left;
            aStack.push(element);
            pointer = pointer->leftchild();
        }
        aStack.pop(element);
        pointer = element.pointer;
        if (element.tag == Left) {
            element.tag = Right;
            aStack.push(element);
            pointer = pointer->rightchild();
        }
        else {
            visit(pointer->value());
            pointer = NULL;
        }
    }
}

template <class T>
void BinaryTree<T>::levelorder(BinaryTreeNode<T>* root) {
    arrQueue<BinaryTreeNode<T>*> aQueue;
    BinaryTreeNode<T>* pointer = root;
    if (pointer != NULL)
        aQueue.enqueue(pointer);
    while (!aQueue.isempty()) {
        aQueue.dequeue(pointer);
        visit(pointer->value());
        if (pointer->leftchild() != NULL)
            aQueue.enqueue(pointer->leftchild());
        if (pointer->rightchild() != NULL)
            aQueue.enqueue(pointer->rightchild());
    }
}

template <class T>
void BinaryTree<T>::Create(T BT[]) {
    BinaryTreeNode<T>* pointer1 = new BinaryTreeNode<T>();
    BinaryTreeNode<T>* pointer2 = new BinaryTreeNode<T>();
    BinaryTreeNode<T>* tempointer = new BinaryTreeNode<T>(BT[0], pointer1, pointer2);
    root = tempointer;
    arrStack<BinaryTreeNode<T>*> aStack(105);
    aStack.push(tempointer->rightchild());
    tempointer = pointer1;
    int i = 1;
    if (BT[0] != '#') {
        while (!aStack.empty() || i < strlen(BT)) {
            tempointer->setvalue(BT[i]);
            if (BT[i] != '#') {
                BinaryTreeNode<T>* pointer2 = new BinaryTreeNode<T>();
                tempointer->right = pointer2;
                aStack.push(pointer2);
                pointer1 = new BinaryTreeNode<T>();
                tempointer->left = pointer1;
                tempointer = pointer1;
            }
            else {
                aStack.pop(tempointer);
            }
            i++;
        }
    }
}
template <class T>
int BinaryTree<T>::high(BinaryTreeNode<T>* root) {
    if (root == NULL || root->value() == '#') return -1;
    else {
        int l = high(root->leftchild());
        int r = high(root->rightchild());
        return l >= r ? l + 1 : r + 1;
    }
}

template <class T>
class MinHeap {
private:
    T* heapArray;
    int CurrentSize;
    int MaxSize;
    void swap(int pos_x, int pos_y) {
        T temp = heapArray[pos_y];
        heapArray[pos_y] = heapArray[pos_x];
        heapArray[pos_x] = temp;
    }
    void BuildHeap() {
        for (int i = CurrentSize / 2 - 1; i >= 0; i--)
            Siftdown(i);
    }
public:
    MinHeap(int n) {
        if (n < 0)
            return;
        CurrentSize = 0;
        MaxSize = n;
        heapArray = new T[MaxSize];
        BuildHeap();
    }
    virtual ~MinHeap() { delete[]heapArray; }
    bool isEmpty() { return CurrentSize == 0 ? true : false; }
    bool isLeaf(int pos) const { return (pos >= CurrentSize / 2) && (pos < CurrentSize); }
    int Leftchild(int pos) const { return 2 * pos + 1; }
    int Rightchild(int pos) const { return 2 * pos + 2; }
    int Parent(int pos) const { return (pos - 1) / 2; }
    bool Remove(int pos, T& node) {
        if (pos < 0 || pos >= CurrentSize)
            return false;
        node = heapArray[pos];
        heapArray[pos] = heapArray[--CurrentSize];
        if (heapArray[Parent(pos)] > heapArray[pos])
            Siftup(pos);
        else Siftdown(pos);
        return true;
    }
    bool Insert(const T& newNode) {
        if (CurrentSize == MaxSize)
            return false;
        heapArray[CurrentSize++] = newNode;
        Siftup(CurrentSize - 1);
        return true;
    }
    T& RemoveMin() {
        if (CurrentSize == 0) {
            cout << "Can't Delete";
            //		exit(1);
        }
        else {
            swap(0, --CurrentSize);
            if (CurrentSize > 1)
                Siftdown(0);
            return heapArray[CurrentSize];
        }
    }
    void Siftup(int pos) {
        T temp = heapArray[pos];
        while (pos > 0 && heapArray[Parent(pos)] > temp) {
            heapArray[pos] = heapArray[Parent(pos)];
            pos = Parent(pos);
        }
        heapArray[pos] = temp;
    }
    void Siftdown(int pos) {
        int i = pos;
        int j = Leftchild(i);
        T temp = heapArray[i];
        while (j < CurrentSize) {
            if ((j < CurrentSize - 1) && (heapArray[j] > heapArray[j + 1]))
                j++;
            if (temp > heapArray[j]) {
                heapArray[i] = heapArray[j];
                i = j;
                j = Leftchild(j);
            }
            else break;
        }
        heapArray[i] = temp;
    }
};

template <class T>
class HuffmanTreeNode :public BinaryTreeNode<T> {
    HuffmanTreeNode<T>* parent;
};
template <class T>
class HuffmanTree {
private:
    HuffmanTreeNode<T>* root;
    void MergeTree(HuffmanTreeNode<T>& ht1, HuffmanTreeNode<T>& ht2, HuffmanTreeNode<T>* parent);
    void DeleteTree(HuffmanTreeNode<T>* root);
public:
    HuffmanTree(T weight[], int n) {
        MinHeap<HuffmanTreeNode<T> > heap(n);
        HuffmanTreeNode<T>* parent, firstchild, secondchild;
        HuffmanTreeNode<T>* NodeList = new HuffmanTreeNode<T>[n];
        for (int i = 0; i < n; i++) {
            NodeList[i].info = weight[i];
            NodeList[i].parent = NodeList[i].left = NodeList[i].right = NULL;
            heap.Insert(NodeList[i]);
        }
        for (int i = 0; i < n - 1; i++) {
            parent = new HuffmanTreeNode<T>;
            firstchild = heap.RemoveMin();
            secondchild = heap.RemoveMin();
            MergreTree(firstchild, secondchild, parent);
            heap.Insert(*parent);
            root = parent;
        }
        delete[]NodeList;
    }
    virtual ~HuffmanTree() { DeleteTree(root); }
};
/*
template <class T>
class ParTreeNode {
private:
    T value;
    ParTreeNode<T>* parent;
    int nCount;
public:
    ParTreeNode() { parent = NULL; }
    ParTreeNode(int n) { parent = new ParTreeNode<T>[n]; }
    virtual ~ParTreeNode() { delete parent; }
    T getvalue() { return value; }
    void setValue(const T& val) { value = val; }
    ParTreeNode<T>* getParent() { return parent; }
    void setParent(ParTreeNode<T>* par) { parent = par; }
    int getCount() { return nCount; }
    void setCount(const int count) { nCount = count; }
};
template <class T>
class ParTree {
public:
    ParTreeNode<T>* array;
    int Size;
    ParTreeNode<T>* Find(ParTreeNode<T>* node)const {
        ParTreeNode<T>* pointer = node;
        while (pointer->getParent() != NULL)
            pointer = pointer->getParent();
        return pointer;
    }
    ParTree(const int size) {
        array = new ParTreeNode<T>[size];
    }
    virtual ~ParTree() { delete[]array; }
    void Union(int i, int j) {
        ParTreeNode<T>* pointeri = Find(&array[i]);
        ParTreeNode<T>* pointerj = Find(&array[j]);
        if (pointeri != pointerj) {
            if (pointeri->getCount() >= pointerj->getCount()) {
                pointerj->setParent(pointeri);
                pointeri->setCount(pointeri->getCount() + pointerj->getCount());
            }
            else {
                pointeri->setParent(pointerj);
                pointerj->setCount(pointeri->getCount() + pointerj->getCount());
            }
        }
    }
    bool Different(int i, int j) {
        ParTreeNode<T>* pointeri = Find(&array[i]);
        ParTreeNode<T>* pointerj = Find(&array[j]);
        return pointeri != pointerj;
    }
};*/
#define UNVISITED -2
#define VISITED -3
#define INFINITY 9999
class Edge {
public:
    int from, to, weight;
    Edge() { from = -1; to = -1; weight = 0; }
    Edge(int f, int t, int w) { from = f; to = t; weight = w; }
    bool operator>(Edge& e) {
        if (weight > e.weight) return 1;
        else return 0;
    }
};
class Graphm {
public:
    int numVertex;
    int numEdge;
    int* Mark;
    int* Indegree;
    Graphm(int numVert) {
        numVertex = numVert;
        numEdge = 0;
        Indegree = new int[numVertex];
        Mark = new int[numVertex];
        for (int i = 0; i < numVertex; i++) {
            Mark[i] = UNVISITED;
            Indegree[i] = 0;
        }
    }
    ~Graphm() {
        delete[]Mark;
        delete[]Indegree;
    }
    int VerticesNum() {
        return numVertex;
    }
    bool IsEdge(Edge oneEdge) {
        if (oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.to >= 0)
            return true;
        else
            return false;
    }
};

class Graph :public Graphm {
private:
    int** matrix;
public:
    Graph(int numVertex) :Graphm(numVertex) {
        int i, j;
        matrix = (int**)new int* [numVertex];
        for (i = 0; i < numVertex; i++)
            matrix[i] = new int[numVertex];
        for (i = 0; i < numVertex; i++)
            for (j = 0; j < numVertex; j++)
                matrix[i][j] = 0;
    }
    ~Graph() {
        for (int i = 0; i < numVertex; i++)
            delete[]matrix[i];
        delete[]matrix;
    }
    Edge FirstEdge(int oneVertex) {
        Edge myEdge;
        myEdge.from = oneVertex;
        for (int i = 0; i < numVertex; i++) {
            if (matrix[oneVertex][i] != 0) {
                myEdge.to = i;
                myEdge.weight = matrix[oneVertex][i];
                break;
            }
        }
        return myEdge;
    }
    Edge NextEdge(Edge preEdge) {
        Edge myEdge;
        myEdge.from = preEdge.from;
        if (preEdge.to < numVertex) {
            for (int i = preEdge.to + 1; i < numVertex; i++) {
                if (matrix[preEdge.from][i] != 0) {
                    myEdge.to = i;
                    myEdge.weight = matrix[preEdge.from][i];
                    break;
                }
            }
        }
        return myEdge;
    }
    void setEdge(int from, int to, int weight) {
        if (matrix[from][to] <= 0) {
            numEdge++;
            Indegree[to]++;
        }
        matrix[from][to] = weight;
    }
    void delEdge(int from, int to) {
        if (matrix[from][to] != 0) {
            numEdge--;
            Indegree[to]--;
        }
        matrix[from][to] = 0;
    }
    int ToVertex(Edge e) {
        return e.to;
    }
    int FromVertex(Edge e) {
        return e.from;
    }
    int EdgesNum() {
        int e = 0;
        for (int i = 0; i < numVertex; i++)
            for (int j = 0; j < numVertex; j++)
                if (i < j) {
                    if (matrix[i][j] != 0)
                        e++;
                    if (matrix[i][j] != matrix[j][i])
                        e++;
                }
        return e;
    }
    int weight(Edge e) {
        return matrix[e.from][e.to];
    }
};

void DFS(Graph& G, int v) {
    G.Mark[v] = VISITED;
    Visit(G, v);
    for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e)) {
        if (G.Mark[G.ToVertex(e)] == UNVISITED)
            DFS(G, G.ToVertex(e));
    }
}

void BFS(Graph& G, int v) {
    arrQueue<int> Q;
    Visit(G, v);
    G.Mark[v];
    Q.enqueue(v);
    int u;
    while (!Q.isempty()) {
        Q.dequeue(u);
        for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e)) {
            if (G.Mark[G.ToVertex(e)] == UNVISITED) {
                Visit(G, G.ToVertex(e));
                G.Mark[G.ToVertex(e)] = VISITED;
                Q.enqueue(G.ToVertex(e));
            }
        }
    }
}

class Dist {
public:
    Dist() { index = 0; length = 0; pre = 0; }
    int index;
    int length;
    int pre;
    bool operator>(Dist& d) {
        if (length > d.length) return 1;
        else return 0;
    }

};

void Dijkstra(Graph& G, int s, Dist*& D) {
    D = new Dist[G.VerticesNum()];
    for (int i = 0; i < G.VerticesNum(); i++) {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = 9999;
        D[i].pre = s;
    }
    D[s].length = 0;
    MinHeap<Dist> H(G.EdgesNum());
    H.Insert(D[s]);
    for (int i = 0; i < G.VerticesNum(); i++) {
        bool FOUND = false;
        Dist d;
        while (!H.isEmpty()) {
            d = H.RemoveMin();
            if (G.Mark[d.index] == UNVISITED) {
                FOUND = true;
                break;
            }
        }
        if (!FOUND)
            break;
        int v = d.index;
        G.Mark[v] = VISITED;
        for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e)) {
            if (D[G.ToVertex(e)].length > (D[v].length + G.weight(e))) {
                D[G.ToVertex(e)].length = D[v].length + G.weight(e);
                D[G.ToVertex(e)].pre = v;
                H.Insert(D[G.ToVertex(e)]);
            }
        }
    }
}

void TopsortbyQueue(Graph& G) {
    for (int i = 0; i < G.VerticesNum(); i++)
        G.Mark[i] = UNVISITED;
    arrQueue<int> Q;
    int v;
    for (int i = 0; i < G.VerticesNum(); i++)
        if (G.Indegree[i] == 0)
            Q.enqueue(i);
    while (!Q.isempty()) {
        Q.dequeue(v);
        Visit(G, v);
        G.Mark[v] = VISITED;
        for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e)) {
            G.Indegree[G.ToVertex(e)]--;
            if (G.Indegree[G.ToVertex(e)] == 0)
                Q.enqueue(G.ToVertex(e));
        }
    }
    for (int i = 0; i < G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED) {
            cout << "此图有环";
            break;
        }
}

void Floyd(Graph& G, Dist**& D) {
    int i, j, v;
    D = new Dist * [G.VerticesNum()];
    for (i = 0; i < G.VerticesNum(); i++)
        D[i] = new Dist[G.VerticesNum()];
    for (i = 0; i < G.VerticesNum(); i++)
        for (j = 0; j < G.VerticesNum(); j++) {
            if (i == j) {
                D[i][j].length = 0;
                D[i][j].pre = i;
            }
            else {
                D[i][j].length = (int)INFINITY;
                D[i][j].pre = -1;
            }
        }
    for (v = 0; v < G.VerticesNum(); v++)
        for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e)) {
            D[v][G.ToVertex(e)].length = G.weight(e);
            D[v][G.ToVertex(e)].pre = v;
        }
    for (v = 0; v < G.VerticesNum(); v++)
        for (i = 0; i < G.VerticesNum(); i++)
            for (j = 0; j < G.VerticesNum(); j++)
                if (D[i][j].length > (D[i][v].length + D[v][j].length)) {
                    D[i][j].length = D[i][v].length + D[v][j].length;
                    D[i][j].pre = D[v][j].pre;
                }

}

void AddEdgetoMST(Edge e, Edge* MST, int n) {
    if (n < 0) return;
    MST[n] = e;
}
int minVertex(Graph& G, Dist*& D);
void Prim(Graph& G, int s, Edge*& MST) {
    int MSTtag = 0;
    MST = new Edge[G.VerticesNum() - 1];
    Dist* D = new Dist[G.VerticesNum()];
    for (int i = 0; i < G.VerticesNum(); i++) {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = (int)INFINITY;
        D[i].pre = s;
    }
    D[s].length = 0;
    G.Mark[s] = VISITED;
    int v = s;
    for (int i = 0; i < G.VerticesNum() - 1; i++) {
        if (D[v].length == INFINITY) return;
        for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e))
            if (G.Mark[G.ToVertex(e)] != VISITED && (D[G.ToVertex(e)].length > e.weight)) {
                D[G.ToVertex(e)].length = e.weight;
                D[G.ToVertex(e)].pre = v;
            }
        v = minVertex(G, D);
        G.Mark[v] = VISITED;
        Edge edge(D[v].pre, D[v].index, D[v].length);
        AddEdgetoMST(edge, MST, MSTtag++);
    }
}
int minVertex(Graph& G, Dist*& D) {
    int v, i;
    for (i = 0; i < G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED) {
            v = i;
            break;
        }
    for (i = 0; i < G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED && D[i].length < D[v].length)
            v = i;
    return v;
}

void Visit(Graph g, int n) {
    if (n != '#')cout << n;
}
/*
void Kruskal(Graph& G, Edge* MST) {
    ParTree<int> A(G.VerticesNum());
    MinHeap<Edge> H(G.EdgesNum());
    MST = new Edge[G.VerticesNum() - 1];
    int MSTtag = 0;
    bool heapEmpty;
    Edge e;
    for (int i = 0;i < G.VerticesNum();i++)
        for (Edge e = G.FirstEdge(i);G.IsEdge(e);e = G.NextEdge(e))
            if (G.FromVertex(e) < G.ToVertex(e))
                H.Insert(e);
    int EquNum = G.VerticesNum();
    while (EquNum > 1) {
        heapEmpty = H.isEmpty();
        if (!heapEmpty)
            Edge e = H.RemoveMin();
        if (heapEmpty || e.weight == INFINITY) {
            cout << "不存在最小生成树。" << endl;
            delete[]MST;
            MST = NULL;
            return;
        }
        int from = G.FromVertex(e);
        int to = G.ToVertex(e);
    if (A.Different(from, to)) {
            A.Union(from, to);
            AddEdgetoMST(e, MST, MSTtag++);
            EquNum--;
        }
    }
}
*/
/*int main() {
    int n, m, s;
    int from, to, weight;
    cin >> n >> m >> s;
    Graph g(n);
    Dist* d;
    arrStack<int> stack(n);
    for (int i = 0; i < m; i++) {
        cin >> from >> to >> weight;
        g.setEdge(from - 1, to - 1, weight);
    }
    Dijkstra(g, s - 1, d);
    for (int i = 0; i < n; i++) {
        if (d[i].index + 1 != s && d[i].length == 9999) { cout << d[i].index + 1 << ": " << 0 << "; " << endl;  continue; }
        else cout << d[i].index + 1 << ": " << ((d[i].length == 9999) ? 0 : d[i].length) << "; ";
        int j = i;
        while (d[j].pre + 1 != s) {
            stack.push(d[j].pre + 1);
            j = d[j].pre;
        }
        cout << d[j].pre + 1 << " ";
        while (!stack.empty()) {
            int num;
            stack.pop(num);
            cout << num << " ";
        }
        if (d[i].index + 1 != s)
            cout << d[i].index + 1 << endl;
        else
            cout << endl;
    }
    return 0;
}*/


#endif // STRUCT_H
