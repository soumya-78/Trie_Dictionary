#include <bits/stdc++.h>
#include <string.h>
using namespace std;
class LRUCache
{
private:
    struct Node
    {
        string key;
        string value;
        Node *prev;
        Node *next;
        Node(string k, string v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<string, Node *> cache;
    Node *head;
    Node *tail;

    void moveToHead(Node *node)
    {
        // Remove the node from its current position
        node->prev->next = node->next;
        node->next->prev = node->prev;

        // Move the node to the head position
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int cap) : capacity(cap)
    {
        head = new Node("", ""); // Dummy head node
        tail = new Node("", ""); // Dummy tail node
        head->next = tail;
        tail->prev = head;
    }

    string get(string key)
    {
        if (cache.find(key) != cache.end())
        {
            Node *node = cache[key];
            moveToHead(node);
            return node->value;
        }
        return "";
    }

    void put(string key, string value)
    {
        if (cache.find(key) != cache.end())
        {
            Node *node = cache[key];
            node->value = value;
            moveToHead(node);
        }
        else
        {
            if (cache.size() >= capacity)
            {
                Node *lastNode = tail->prev;
                cache.erase(lastNode->key);
                lastNode->prev->next = tail;
                tail->prev = lastNode->prev;
                delete lastNode;
            }
            Node *newNode = new Node(key, value);
            cache[key] = newNode;
            newNode->prev = head;
            newNode->next = head->next;
            head->next->prev = newNode;
            head->next = newNode;
        }
    }

    void printCache()
    {
        if (head->next == tail)
        {
            cout << "No searches have been done yet\n";
            return;
        }
        cout << "Most recently used words: \n";
        for (Node *curr = head->next; curr != tail; curr = curr->next)
        {
            cout << "(" << curr->key << "," << curr->value << ") \n";
        }
    }
};
