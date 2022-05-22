// asked for help from ilan sirisky.

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include "Node.hpp"

namespace ariel{
    class OrgChart{
        private:
            Node *root;
            // https://stackoverflow.com/questions/20735708/how-to-get-an-element-in-n-ary-trees
            Node * find(const std::string &check, Node* current);

        public:
            OrgChart();
            OrgChart(Node* root);
            OrgChart &add_root(const std::string &name);
            OrgChart &add_sub(const std::string &first, const std::string &second);

            class Iterator{
                public:
                    enum Mode{
                        LEVELORDER = 0,
                        PREORDER,
                        REVERSE
                    };

                private:
                    Node *last;
                    Node *currentLocation;
                    Mode type;
                    std::queue<ariel::Node *> Queue;
                    std::stack<ariel::Node *> Stack;

                    void createReverseOrder(Node * root){
                        Queue.push(root);
                        while(!Queue.empty()){
                            Node *temp = Queue.front();
                            Stack.push(temp);
                            Queue.pop();
                            
                            for (auto it = temp->childrens.rbegin(); it != temp->childrens.rend(); ++it){
                                Queue.push(*it);
                            }
                            std::cout<< Stack.top()->name<<std::endl;
                        }
                    }

                    void createPreOrder(Node *nd){
                        if(nd == nullptr){
                            return;
                        }

                        Queue.push(nd);
                        for (ariel::Node *node : nd->childrens){
                            this->createPreOrder(node);
                        }
                    }

                public:

                    Iterator(Node *root, Mode md) : currentLocation(root), last(nullptr), type(md){
                        if(root != nullptr){ 
                            switch (this->type)
                            {
                            case Mode::REVERSE:
                                createReverseOrder(root);
                                this->currentLocation = Stack.top();
                                std::cout<<"CHECK ->" << this->currentLocation->name << std::endl;
                                Stack.pop();
                                break;
                            
                            case Mode::PREORDER:
                                createPreOrder(root);
                                Queue.pop();
                                break;
                            
                            default:
                                for (ariel::Node *node : root->childrens){
                                    Queue.push(node);
                                }
                                break;
                            }
                        }
                    }

                    Iterator &operator++(){
                        switch (this->type)
                        {
                        case Mode::REVERSE:
                            if(!Stack.empty()){
                                this->currentLocation = Stack.top();
                                Stack.pop();
                            }
                            else{
                                this->currentLocation = nullptr;
                            }
                            break;
                        
                        case Mode::PREORDER:
                            if(!Queue.empty()){
                                this->currentLocation = Queue.front();
                                Queue.pop();
                            }
                            else{
                                this->currentLocation = nullptr;
                            }
                            break;
                        
                        default:
                            if(!Queue.empty()){
                                this->currentLocation = Queue.front();
                                Queue.pop();
                                for (ariel::Node *node : this->currentLocation->childrens){
                                    Queue.push(node);
                                }
                            }
                            else{
                                this->currentLocation = nullptr;
                            }
                            break;
                        }
                        return *this;
                    }

                    std::string &operator*() const
                    {
                        return this->currentLocation->name;
                    }

                    std::string *operator->() const
                    {
                        return &(this->currentLocation->name);
                    }

                    bool operator==(const Iterator &iter) const
                    {
                        return (this->currentLocation == iter.currentLocation);
                    }

                    bool operator!=(const Iterator &iter) const
                    {
                        return (this->currentLocation != iter.currentLocation);
                    }
            };

                       Iterator begin_level_order(){
                if(this->root == nullptr){
                    throw "Runtime Error!";
                }
                return Iterator(this->root, Iterator::Mode::LEVELORDER);
            }
            Iterator end_level_order(){
                if(this->root == nullptr){
                    throw "Runtime Error!";
                }
                return Iterator(nullptr, Iterator::Mode::LEVELORDER);
            }

            Iterator begin_reverse_order(){
                if(this->root == nullptr){
                    throw "Runtime Error!";
                }
                return Iterator(this->root, Iterator::Mode::REVERSE);
            }
            Iterator reverse_order(){
                if(this->root == nullptr){
                    throw "Runtime Error!";
                }
                return Iterator(nullptr, Iterator::Mode::REVERSE);
            }

            Iterator begin_preorder(){
                if(this->root == nullptr){
                    throw "Runtime Error!";
                }
                return Iterator(this->root, Iterator::Mode::PREORDER);
            }
            Iterator end_preorder(){
                if(this->root == nullptr){
                    throw "Runtime Error!";
                }
                return Iterator(nullptr, Iterator::Mode::PREORDER);
            }

            friend std::ostream &operator<<(std::ostream &out, OrgChart &root){
                out << "test";
                return out;
            }

            Iterator begin(){
                return this->begin_level_order();
            }
            Iterator end(){
                return this->end_level_order();
            }

    };
}