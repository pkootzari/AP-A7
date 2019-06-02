#include "handlers.hpp"
#include "my_server.hpp"
#include <iostream>
#include "manager.h"

using namespace std;

int main(int argc, char **argv) {
  try {
    Manager* manager = new Manager();
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/signup.html"));
    server.post("/", new SignupHandler(manager));
    server.get("/error", new ShowPage("static/error.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHnadler(manager));
    server.post("/home_page", new ShowPage("static/home_page.html"));
    server.get("/home_page", new ShowPage("static/home_page.html"));
    
    // server.get("/login", new ShowPage("static/logincss.html"));
    // server.post("/login", new LoginHandler());
    // server.get("/up", new ShowPage("static/upload_form.html"));
    // server.post("/up", new UploadHandler());
    // server.get("/rand", new RandomNumberHandler());S
    // server.get("/home.png", new ShowImage("static/home.png"));
    // server.get("/", new ShowPage("static/home.html"));
    // server.get("/colors", new ColorHandler("template/colors.html"));
    
    
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
