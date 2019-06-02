#include "handlers.hpp"

using namespace std;

LoginHnadler::LoginHnadler(Manager* _manager) : manager(_manager) {}
Response *LoginHnadler::callback(Request *req) {
  Response *res = new Response;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  int id = manager->login(username, password);
  if(id == -1)
    res = Response::redirect("/error");
  else {
    res = Response::redirect("/home_page");
    res->setSessionId(to_string(id));
  }
  return res;
}

SignupHandler::SignupHandler(Manager* _manager) : manager(_manager) {}
Response* SignupHandler::callback(Request* req) {
  Response *res = new Response;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string confrim_password = req->getBodyParam("confrim_password");
  string email = req->getBodyParam("email");
  string part = req->getBodyParam("part");
  int age = stoi(req->getBodyParam("age"));
  if(password != confrim_password)
    res = Response::redirect("/error");
  try{
    int session_id;
    if(part == "Customer")
      session_id = manager->add_customer(email, username, password, age);
    else
      session_id = manager->add_publisher(email, username, password, age);
    res = Response::redirect("/home_page");
    res->setSessionId(to_string(session_id));
  }
  catch(exception& ex) {
    res = Response::redirect("/error");
  }
  return res;
}


// Response *RandomNumberHandler::callback(Request *req) {
//   Response *res = new Response;
//   res->setHeader("Content-Type", "text/html");
//   string body;
//   body += "<!DOCTYPE html>";
//   body += "<html>";
//   body += "<body style=\"text-align: center;\">";
//   body += "<h1>AP HTTP</h1>";
//   body += "<p>";
//   body += "a random number in [1, 10] is: ";
//   body += to_string(rand() % 10 + 1);
//   body += "</p>";
//   body += "<p>";
//   body += "SeddionId: ";
//   body += req->getSessionId();
//   body += "</p>";
//   body += "</body>";
//   body += "</html>";
//   res->setBody(body);
//   return res;
// }

// Response *LoginHandler::callback(Request *req) {
//   string username = req->getBodyParam("username");
//   string password = req->getBodyParam("password");
//   if (username == "root")
//     throw Server::Exception("Remote root access has been disabled.");
//   cout << "username: " << username << ",\tpassword: " << password << endl;
//   Response *res = Response::redirect("/rand");
//   res->setSessionId("SID");
//   return res;
// }

// Response *UploadHandler::callback(Request *req) {
//   string name = req->getBodyParam("file_name");
//   string file = req->getBodyParam("file");
//   cout << name << " (" << file.size() << "B):\n" << file << endl;
//   Response *res = Response::redirect("/");
//   return res;
// }

// ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

// map<string, string> ColorHandler::handle(Request *req) {
//   map<string, string> context;
//   string newName = "I am " + req->getQueryParam("name");
//   context["name"] = newName;
//   context["color"] = req->getQueryParam("color");
//   return context;
// }
