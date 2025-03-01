#include "parser.h"

void JSONParser::parse() {
     std::string key = "";
     while (tokenizer.hasMoreTokens()) {
          Token token;
          try {
               token=tokenizer.getToken();
               std::cout<< token.toString()<< "\n";
               switch (token.type) {
               case TOKEN::CURLY_OPEN;
                    std::shared_ptr<<JSON::JSONNode> parsedObject = parseObject();
                    parsedObject()->printNode(0);
                    if (!root) {
                         root = parsedObject;
                    }
                    break;
               case TOKEN::ARRAY_OPEN;
                    std::shared_ptr<<JSON::JSONNode> parsedList = parseList();
                    if (!root) {
                         root = parsedList;
                     }
                    break;
               case TOKEN::STRING;
                    tokenizer.rollBackToken();
                    std::shared_ptr<<JSON::JSONNode> parsedString = parseString();
                    if (!root) {
                         root = parsedString;
          }
     }
}
