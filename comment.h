#ifndef COMMENT_H_
#define COMMENT_H_

#include <string>
#include <vector>

class Comment {
public:
    Comment(int _id, std::string content);
private:
    int id;
    std::vector<std::string> comments_replies;
};

#endif