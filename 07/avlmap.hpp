#pragma once

#include <iostream>

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
> 

class Map {
    
    public:

    static class Map* root;

    Map *left, *right, *parent;
    int key, value, depth;


    const int find(int key) const
    {
        // храним корень

        Map* temp = root;

        // ищем пока не перепробуем все варианты или не найдем ключ

        while (temp != nullptr && temp->key != key) {
            
            // если искомый ключ меньше, идем налево

            if (key < temp->key) {
                temp = temp->left;
            }

            // соответственно, идем направо, если больше

            else {
                temp = temp->right;
            }
        }

        // нашли ключ

        if (temp != nullptr) {
            
            // вернули значение

            return temp->value;
        }

        // в противном случае вернем ноль как дефолтное значение

        return 0;
    }


    Map* create(int key)
    {
        Map* newnode = (Map*)malloc(sizeof(Map));
        
        newnode->key = key;
        newnode->value = 0;

        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->parent = nullptr;

        newnode->depth = 1;

        return newnode;
    }
    
    //...
    // Ротации 
    //...


    void balance(Map* node)
    {
        while (node != root) 
        {
            int d = node->depth;
            node = node->par;


            if ((node == root) && (get_depth(node->left) - get_depth(node->right)) > 1) 
            {
                // Есть дисбаланс по длине потомков

                if (get_depth(node->left->left)
                    > get_depth(node->left->right)) {
                    root = node->left;
                }
                else {
                    root = node->left->right;
                }
                helper(node);
                break;
            }
            else if (node == root
                     && get_depth(node->left)
                                - get_depth(node->right)
                            < -1) {
                if (get_depth(node->right->right)
                    > get_depth(node->right->left)) {
                    root = node->right;
                }
                else {
                    root = node->right->left;
                }
                helper(node);
                break;
            }
            helper(node);
        }
    }

    
    int get_depth(Map* node)
    {
        if (node == nullptr)
            return 0;
        return node->depth;
    }


    int increase_depth(Map* node)
    {
        int h = 0;
        if (node != NULL) {
            int l_depth = increase_depth(node->left);
            int r_depth = increase_depth(node->right);
            int max_depth = max(l_height, r_height);
            h = max_depth + 1;
        }
        return h;
    }


    Map* insert(int key)
    {
        Map* newnode = create(key);

        // Если корень пуст, создаем ноду

        if (root == nullptr) {
            root = newnode;
            return root;
        }

        Map *temp = root, *prev = nullptr;

        while (temp != nullptr) 
        {
            prev = temp;

            if (key < temp->key) {
                temp = temp->left;
            }
            else if (key > temp->key) {
                temp = temp->right;
            }
            else {
                free(newnode);

                // Если есть такой же ключ, то возвращаем ссылку на уже существующий

                return temp;
            }
        }

        // налаживаем связи 

        if (key < prev->key) {
            prev->left = newnode;
        }
        else {
            prev->right = newnode;
        }

        newnode->parent = prev;

        // Проверяем сбалансированность дерева

        balance(newnode);

        // возвращаем ссылку новый узел

        return newnode;
    }


    // Оператор присваивания (за счет возвращения по ссылке)

    int& operator[](int key) { return insert(key)->value; }

    // Константный оператор для получения значения по ключу

    const int operator[](int key) const
    {
        return search(key);
    }
};