#include <ml/types.h>
#include <new>

// A linked list.
template <class T>
struct mlList {
	struct Node {
		Node* pNext;
		T item;
	};

    ~mlList() {
        // TODO: delete all nodes
    }

	void pushBack(const T& value) {
		Node* pNode = new Node();
        pNode->item = value;
        pNode->pNext = nil(Node*);

        Node* iter = pHead;
        while(iter) {
            iter = iter->pNext;
        }

        iter->pNext = pNode;
	}

    u32 Size() const {
        Node* iter = pHead;
        u32 count = 0;
        while(iter) {
            count++;
            iter = iter->pNext;
        }

        return count;
    }

    void forEach(bool(*pcbCallback)(T* item, void* ctx), void* ctx) {
        Node* iter = pHead;
        while(iter) {
            if(!pcbCallback(&iter->item, ctx))
                break;
            iter = iter->pNext;
        }
    }

	T& operator[](u32 index) {
        Node* iter = pHead;
        u32 count = 0;
        while(iter) {
            if(count++ == index)
                return iter->item;

            iter = iter->pNext;
        }

        while(true);
	}
private:
    Node* pHead;
};