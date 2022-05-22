#include "OrgChart.hpp"

using namespace std;

namespace ariel{
    OrgChart::OrgChart(){
        this->root = nullptr;
    }

    OrgChart::OrgChart(Node *root){
        this->root = root;
    }

    OrgChart& OrgChart::add_root(const std::string &name){
        if(this->root == nullptr){
            this->root = new Node(name);
        }

        this->root->name = name;
        return *this;
        
    }

    Node * OrgChart::find(const string &check, Node* current){
        if(current == nullptr){
            return current;
        }

        if(current->name == check){
            return current;
        }

        for(Node *nd : current->childrens){
            Node *ch = find(check, nd);
            if(ch != nullptr){
                return ch;
            }
        }
        return nullptr;
    }

    OrgChart& OrgChart::add_sub(const string &first, const string &second){
        Node *parent = find(first, this->root);
        if (parent == nullptr)
        {
            throw std::invalid_argument("First value is not in the chart");
        }
        parent->addChild(second);
        return *this;
    }

}