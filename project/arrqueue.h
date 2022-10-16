#ifndef ARRQUEUE_H
#define ARRQUEUE_H

class arrQueue {
private:
    int front;
    int rear;
    int* qu;
public:
    int mSize;
    arrQueue() {qu = NULL;}
    arrQueue(int size) {
        mSize = size + 1;
        qu = new int[mSize];
        front = rear = 0;
    }
    ~arrQueue() {
        delete[] qu;
    }
    bool enqueue(const int item) {
        if ((rear + 1) % mSize == front)
            return false;
        qu[rear] = item;
        rear = (rear + 1) % mSize;
        return true;
    }
    bool dequeue(int& item) {
        if (front == rear) return false;
        item = qu[front];
        front = (front + 1) % mSize;
        return true;
    }
    bool isempty() {
        if (front == rear) return true;
        return false;
    }
    void Delete(int s, int& tmp) {
        int *q = new int[s];
        int tmp1;
        for (int i = 0; i < s - 1; i++) {
            dequeue(tmp1);
            enqueue(tmp1);
        }
        dequeue(tmp);
    }
};

#endif // ARRQUEUE_H
