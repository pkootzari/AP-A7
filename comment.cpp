#include "comment.h"

using namespace std;

Comment::Comment(int _id, string content) : id(_id) {
    comments_replies.push_back(content);
}