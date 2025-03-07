#include <iostream>
#include <map>
#include <memory>
#include <vector>

class JSON_Node;

using JSONObject = std::map<std::string, std::shared_ptr<JSON_Node>>;
using JSONList = std::vector<std::shared_ptr<JSON_Node>>;

class JSON_Node
{
    enum class TYPE{OBJECT, LIST, STRING, NUMBER, BOOLEAN, NULL_TYPE};

    union Values
    {
        JSONObject *object;
        JSONList *list;

        std::string *s;

        float fValue;
        bool bValue;

    }value;

    TYPE type;

    //---------------------------------

public:

    auto returnObject()
    {
        if(type == TYPE::OBJECT)
        {
            return *value.object;
        }

        throw std::logic_error("Wrong return\n");
    }

    auto returnList()
    {
        if(type == TYPE::LIST)
        {
            return *value.list;
        }

        throw std::logic_error("Wrong return\n");
    }

    auto returnString()
    {
        if(type == TYPE::STRING)
        {
            return *value.s;
        }

        throw std::logic_error("Wrong return\n");
    }

    auto returnFloat()
    {
        if(type == TYPE::NUMBER)
        {
            return value.fValue;
        }

        throw std::logic_error("Wrong return\n");
    }

    auto returnBool()
    {
        if(type == TYPE::BOOLEAN)
        {
            return value.bValue;
        }

        throw std::logic_error("Wrong return\n");
    }

    void setObject(JSONObject *object)
    {
        this-> value.object = object;
        type = TYPE::OBJECT;
    }

    void setList(JSONList *list)
    {
        this -> value.list = list;
        type = TYPE::LIST;
    }

    void setString(std::string *s)
    {
        this -> value.s = s;
        type = TYPE::STRING;
    }

    void setFloat(float fl)
    {
        value.fValue = fl;
        type = TYPE::NUMBER;
    }

    void setBool(bool bl)
    {
        value.bValue = bl;
        type = TYPE::BOOLEAN;
    }

    void setNull() {
        type=TYPE::NULL_TYPE;
    }
    std::string  JSON_Node::toString(int indentLevel) {
        std::string spaceStr=std::string(indentLevel*' ');
        std::string outputstring=" ";
        switch (type) {
            case TYPE::STRING:
                outputstring+=spaceStr +*value.s;
            break;

            case TYPE::NUMBER:
                outputstring+=spaceStr +std::to_string(value.fValue);
            break;

            case TYPE::BOOLEAN:
                outputstring+=spaceStr + (value.bValue? "true":"false");
            break;

            case TYPE::NULL_TYPE:
                outputstring+=spaceStr + "null";
            break;

            case TYPE::LIST:
                std::cout<<"[";
                int index=0;
            for (auto node: (*value.list)) {
                outputstring += node -> toString(indentLevel + 1);
                if(index<(*value.list).size() - 1) {
                    outputstring += spaceStr+ ",";
                }
                index++;
            }
            outputstring+=spaceStr+"]\n";
            break;
            case TYPE::OBJECT:
                outputstring +=  "{\n";
            for (JSONObject::iterator i=(*value.object).begin(); i != (*value.object).end(); i++) {
                outputstring += spaceStr+i->first +": ";
                outputstring += i ->second->toString(indentLevel + 1);
                JSONObject::iterator next=i;
                next++;
                if (next!=(*value.object).end()) {
                    outputstring += spaceStr",";
                }
                outputstring += spaceStr+"\n";
            }
            outputstring+="\n";
        }
        return outputstring;
    }

    void JSON_Node::printNode(int indentLevel) {
        std::cout<<toString(indentLevel);
    }
};
