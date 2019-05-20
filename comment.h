#ifndef COMMENT_H_
#define COMMENT_H_

#include <string>
#include <vector>
#include <iostream>

class Comment {
public:
    Comment(int _id, std::string content);
    int get_id();
    void add_reply(std::string content); 
private:
    int id;
    std::vector<std::string> comments_replies;
};

#endif