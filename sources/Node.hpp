#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace ariel{
    class Node{
        public:
            std::string name;
            std::vector<Node *> childrens;
            Node *parent;

            Node(std::string name) : name(name), parent(nullptr){}    
            Node(std::string name, Node* parent) : name(name), parent(parent){} 

            void addChild(std::string name){
                Node *temp = new Node(name, this);
                this->childrens.push_back(temp);
            }

    };
}