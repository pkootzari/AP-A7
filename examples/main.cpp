#include "handlers.hpp"
#include "my_server.hpp"
#include <iostream>
#include "manager.h"

using namespace std;

int main(int argc, char **argv) {
  Manager* manager = new Manager();
  try {
    Manager* manager = new Manager();
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/signup.html"));
    server.post("/", new SignupHandler(manager));
    server.get("/error", new ShowPage("static/error.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHnadler(manager));
    server.get("/home_page", new HomePageHandler(manager));
    server.get("/publisher_homepage", new PublisherHomePage(manager));
    server.get("/customer_homepage", new CustomerHomePage(manager));
    server.get("/publisher_homepage/profile", new PublisherProfile(manager));
    server.get("/customer_homepage/profile", new CustomerProfile(manager));
    server.get("/publisher_homepage/add_film", new ShowPage("static/add_film.html"));
    server.post("/publisher_homepage/add_film", new AddFilm(manager));
    // server.get("/publisher_homepage/buy_film", new PublisherBuy(manager));
    // server.get("/customer_homepage/buy_film", new CustomerBuy(manager));
    // server.get("/publisher_homepage/add_credit", new PublisherAddCredit(manager));
    // server.get("/customer_homepage/add_credit", new CustomerAddCredit(manager));
    // server.get("/publisher_homepage/search_film", new PublisherSearchFilm(manager));
    // server.get("customer_homepage/search_film", new CustomerSearchFilm(manager));
    // server.get("/see_film_detail", new FilmDetail(manager));
    // server.get("/rate_comment_film". new FilmRate(manager));
    server.get("/logout", new Logout(manager));
    
    // server.get("/login", new ShowPage("static/logincss.html"));
    // server.post("/login", new LoginHandler());
    // server.get("/up", new ShowPage("static/upload_form.html"));
    // server.post("/up", new UploadHandler());
    // server.get("/rand", new RandomNumberHandler());
    // server.get("/home.png", new ShowImage("static/home.png"));
    // server.get("/", new ShowPage("static/home.html"));
    // server.get("/colors", new ColorHandler("template/colors.html"));
    
    
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
  manager->free();
}
