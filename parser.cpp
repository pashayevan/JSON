#include "parser.h"

void JSONParser::parse()
{
    std::string key = "";

    while(tokenizer.hasMoreTokens())
    {
        Token token;

        try
        {
            token = tokenizer.getToken();
            std::cout << token.toString() << "\n";

            switch(token.type)
            {
                case TOKEN::CURLY_OPEN:
                {
                    std::shared_ptr<JSON_Node> parsedObject = parseObject();
                    //parsedObject -> printNode(0);
                    if(!root)
                    {
                        root = parsedObject;
                    }
                    break;
                }
                case TOKEN::ARRAY_OPEN:
                {
                    std::shared_ptr<JSON_Node> parsedList = parseList();
                    if(!root)
                    {
                        root = parsedList;
                    }
                    break;
                }
                case TOKEN::STRING:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedString = parseString();
                    if(!root)
                    {
                        root = parsedString;
                    }
                    break;
                }
                case TOKEN::NUMBER:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedNumber = parseNumber();
                    if(!root)
                    {
                        root = parsedNumber;
                    }
                    break;
                }
                case TOKEN::BOOLEAN:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedBoolean = parseBoolean();
                    break;
                }
            }
        }
        catch(const std::logic_error &e)
        {
            break;
        }

    }
}
std::shared_ptr<JSON_Node> JSONParser::parseList() {
    std::cout << "Parsed List\n";
    std::shared_ptr<JSON_Node> node = std::make_shared<JSON_Node>();
    JSONList * list = new JSONList();
    bool hasCompleted = false;
    while(!hasCompleted) {
        if(!tokenizer.hasMoreTokens()) {
            throw std::logic_error("No more tokens");
        } else {
            Token nextToken = tokenizer.getToken();
            std::shared_ptr<JSON_Node> node;
            switch(nextToken.type) {
                case TOKEN::ARRAY_OPEN:
                    node = parseList();
                    break;
                case TOKEN::CURLY_OPEN:
                    node = parseObject();
                    break;
                case TOKEN::STRING:
                    tokenizer.rollBackToken();
                    node = parseString();
                    break;
                case TOKEN::NUMBER:
                    tokenizer.rollBackToken();
                    node = parseNumber();
                    break;
                case TOKEN::BOOLEAN:
                    tokenizer.rollBackToken();
                    node = parseBoolean();
                    break;
                case TOKEN::NULL_TYPE:
                    node = parseNull();
                    break;
            }
            list->push_back(node);
            nextToken = tokenizer.getToken();
            if(nextToken.type == TOKEN::ARRAY_CLOSE) {
                hasCompleted = true;
            }
        }
    }
    node->setList(list);
    return node;
}
std::shared_ptr<JSON_Node> JSONParser::parseObject() {
    std::cout << "Parsed Object\n";
    std::shared_ptr<JSON_Node> node = std::make_shared<JSON_Node>();
    JSONObject * keyObjectMap = new JSONObject();
    bool hasCompleted = false;
    while(!hasCompleted) {
        if(tokenizer.hasMoreTokens()) {
            Token nextToken = tokenizer.getToken();
            std::string key = nextToken.value;
            std::cout << key << "\n";
            tokenizer.getToken();
            nextToken = tokenizer.getToken();
            std::shared_ptr<JSON_Node> node;
            switch(nextToken.type) {
                case TOKEN::STRING:
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key]=parseString();
                    break;
                case TOKEN::ARRAY_OPEN:
                    (*keyObjectMap)[key]=parseList();
                    break;
                case TOKEN::NUMBER:
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key]=parseNumber();
                    break;
                case TOKEN::CURLY_OPEN:
                    (*keyObjectMap)[key]=parseObject();
                    break;
                case TOKEN::BOOLEAN:
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key]=parseBoolean();
                    break;
                case TOKEN::NULL_TYPE:
                    (*keyObjectMap)[key]=parseNull();
                    break;
            }
            nextToken = tokenizer.getToken();
            if(nextToken.type == TOKEN::CURLY_CLOSE) {
                hasCompleted = true;
                break;
            }
        } else {
            throw std::logic_error("No more tokens\n");
        }
    }
    node->setObject(keyObjectMap);
    return node;
}

std::shared_ptr<JSON_Node> JSONParser::parseString() {
    std::cout << "Parsed string\n";
    std::shared_ptr<JSON_Node> node = std::make_shared<JSON_Node>();
    Token token = tokenizer.getToken();
    std::string *sValue = new std::string(token.value);
    node->setString(sValue);
    return node;
}#include "parser.h"

void JSONParser::parse()
{
    std::string key = "";

    while(tokenizer.hasMoreTokens())
    {
        Token token;

        try
        {
            token = tokenizer.getToken();
            std::cout << token.toString() << "\n";

            switch(token.type)
            {
                case TOKEN::CURLY_OPEN:
                {
                    std::shared_ptr<JSON_Node> parsedObject = parseObject();
                    //parsedObject -> printNode(0);
                    if(!root)
                    {
                        root = parsedObject;
                    }
                    break;
                }
                case TOKEN::ARRAY_OPEN:
                {
                    std::shared_ptr<JSON_Node> parsedList = parseList();
                    if(!root)
                    {
                        root = parsedList;
                    }
                    break;
                }
                case TOKEN::STRING:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedString = parseString();
                    if(!root)
                    {
                        root = parsedString;
                    }
                    break;
                }
                case TOKEN::NUMBER:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedNumber = parseNumber();
                    if(!root)
                    {
                        root = parsedNumber;
                    }
                    break;
                }
                case TOKEN::BOOLEAN:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedBoolean = parseBoolean();
                    break;
                }
            }
        }
        catch(const std::logic_error &e)
        {
            break;
        }

    }
}
std::shared_ptr<JSON_Node> JSONParser::parseList() {
    std::cout << "Parsed List\n";
    std::shared_ptr<JSON_Node> node = std::make_shared<JSON_Node>();
    JSONList * list = new JSONList();
    bool hasCompleted = false;
    while(!hasCompleted) {
        if(!tokenizer.hasMoreTokens()) {
            throw std::logic_error("No more tokens");
        } else {
            Token nextToken = tokenizer.getToken();
            std::shared_ptr<JSON_Node> node;
            switch(nextToken.type) {
                case TOKEN::ARRAY_OPEN:
                    node = parseList();
                    break;
                case TOKEN::CURLY_OPEN:
                    node = parseObject();
                    break;
                case TOKEN::STRING:
                    tokenizer.rollBackToken();
                    node = parseString();
                    break;
                case TOKEN::NUMBER:
                    tokenizer.rollBackToken();
                    node = parseNumber();
                    break;
                case TOKEN::BOOLEAN:
                    tokenizer.rollBackToken();
                    node = parseBoolean();
                    break;
                case TOKEN::NULL_TYPE:
                    node = parseNull();
                    break;
            }
            list->push_back(node);
            nextToken = tokenizer.getToken();
            if(nextToken.type == TOKEN::ARRAY_CLOSE) {
                hasCompleted = true;
            }
        }
    }
    node->setList(list);
    return node;
}
std::shared_ptr<JSON_Node> JSONParser::parseObject() {
    std::cout << "Parsed Object\n";
    std::shared_ptr<JSON_Node> node = std::make_shared<JSON_Node>();
    JSONObject * keyObjectMap = new JSONObject();
    bool hasCompleted = false;
    while(!hasCompleted) {
        if(tokenizer.hasMoreTokens()) {
            Token nextToken = tokenizer.getToken();
            std::string key = nextToken.value;
            std::cout << key << "\n";
            tokenizer.getToken();
            nextToken = tokenizer.getToken();
            std::shared_ptr<JSON_Node> node;
            switch(nextToken.type) {
                case TOKEN::STRING:
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key] = parseString();
                    break;
                case TOKEN::ARRAY_OPEN:
                    (*keyObjectMap)[key] = parseList();
                    break;
                case TOKEN::NUMBER:
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key] = parseNumber();
                    break;
                case TOKEN::CURLY_OPEN:
                    (*keyObjectMap)[key] = parseObject();
                    break;
                case TOKEN::BOOLEAN:
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key] = parseBoolean();
                    break;
                case TOKEN::NULL_TYPE:
                    (*keyObjectMap)[key] = parseNull();
                    break;
            }
            nextToken = tokenizer.getToken();
            if(nextToken.type == TOKEN::CURLY_CLOSE) {
                hasCompleted = true;
                break;
            }
        } else {
            throw std::logic_error("No more tokens\n");
        }
    }
    node->setObject(keyObjectMap);
    return node;
}

std::shared_ptr<JSON_Node> JSONParser::parseString() {
    std::cout << "Parsed string\n";
    std::shared_ptr<JSON_Node> node = std::make_shared<JSON_Node>();
    Token token = tokenizer.getToken();
    std::string *sValue = new std::string(token.value);
    node->setString(sValue);
    return node;
}