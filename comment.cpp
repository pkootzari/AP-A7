#include "comment.h"

using namespace std;

Comment::Comment(int _id, string content) : id(_id) {
    comments_replies.push_back(content);
}

int Comment::get_id() { return id; }

void Comment::add_reply(string content) {
    comments_replies.push_back(content);
}

ostream& operator<<(ostream& out, Comment* cm) {
    out << cm->id << ". " << cm->comments_replies[0] << endl;
    for(int i = 1; i < cm->comments_replies.size(); i++)
        out << cm->id << "." << i << ". " << cm->comments_replies[i] << endl;
}