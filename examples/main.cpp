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
    server.post("/publisher_homepage/buy_film", new PublisherBuyFilm(manager));
    server.post("/customer_homepage/buy_film", new CustomerBuyFilm(manager));
    server.get("/publisher_homepage/add_credit", new ShowPage("static/add_credit_publisher.html"));
    server.get("/customer_homepage/add_credit", new ShowPage("static/add_credit_customer.html"));
    server.post("/publisher_homepage/add_credit", new PublisherAddCredit(manager));
    server.post("/customer_homepage/add_credit", new CustomerAddCredit(manager));
    // server.get("/publisher_homepage/search_film", new PublisherSearchFilm(manager));
    // server.get("customer_homepage/search_film", new CustomerSearchFilm(manager));
    // server.get("/see_film_detail", new FilmDetail(manager));
    // server.get("/rate_comment_film", new FilmRatePage(manager));
    // server.post("/rate_comment_film". new FilmRate(manager));
    server.get("/logout", new Logout(manager));
    
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
  manager->free();
}
