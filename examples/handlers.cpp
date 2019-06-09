#include "handlers.hpp"

using namespace std;

LoginHnadler::LoginHnadler(Manager* _manager) : manager(_manager) {}
Response* LoginHnadler::callback(Request *req) {
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

HomePageHandler::HomePageHandler(Manager* _manager) : manager(_manager) {}
Response* HomePageHandler::callback(Request* req) {
  Response *res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else {
    int id = stoi(req->getSessionId());
    User* cur_user = manager->find_user(id);
    if(cur_user->get_type() == "customer")
      res = Response::redirect("/customer_homepage");
    else
      res = Response::redirect("/publisher_homepage");
  }
  return res;
}
 
PublisherHomePage::PublisherHomePage(Manager* _manager) : manager(_manager) {}
Response* PublisherHomePage::callback(Request* req) {
  Response *res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "customer")
    res = Response::redirect("/error");
  else {
    res->setHeader("Content-Type", "text/html");
    vector<Film*> films = manager->get_published(stoi(req->getSessionId()));
    vector<Film*> purchasable_films = manager->see_purchaeable_films(stoi(req->getSessionId()));
    stringstream body;
    body << "<!DOCTYPE html>" << endl;
    body << "<html lang=\"en\">" << endl;
    body << "<head>" << endl;
    body << "  <title>User HomePage</title>" << endl;
    body << "  <meta charset=\"utf-8\">" << endl;
    body << "</head>" << endl;
    body << "<body>" << endl;
    body << "  <ul>" << endl;
    body << "    <li><a href=\"/publisher_homepage/profile\">Profile</a></li>" << endl;
    body << "    <li><a href=\"/publisher_homepage/add_film\">Add Film</a></li>" << endl;
    body << "    <li><a href=\"/publisher_homepage/add_credit\">Add Credit : " << manager->find_user(stoi(req->getSessionId()))->see_money() << " </a></li>" << endl;
    body << "    <li><a href=\"/logout\">Logout</a></li>" << endl;
    body << "  </ul>" << endl;
    body << "  <form action=\"/publisher_homepage/search_film\" method=\"post\">" << endl;
    body << "    Director : <input name=\"director\" type=\"text\" placeholder=\"Enter Director Name\" /> <br>" << endl;
    body << "    <button type=\"submit\" >Search</button>" << endl;
    body << "  </form>" << endl;
    body << "  Published Films : <br>" << endl;
    body << "  <table>" << endl;
    body << "    <tr>" << endl;
    body << "      <th>Name</th>" << endl;
    body << "      <th>Price</th> " << endl;
    body << "      <th>Production Year</th>" << endl;
    body << "      <th>Length</th>" << endl;
    body << "      <th>Rate</th>" << endl;
    body << "      <th>Director</th>" << endl;
    body << "    </tr>" << endl;
    for(int i = 0; i < films.size(); i++) {
      body << "    <tr>" << endl;
      body << "      <td>" << films[i]->get_name() << "</td>" << endl;
      body << "      <td>" << films[i]->get_price() << "</td> " << endl;
      body << "      <td>" << films[i]->get_year() << " </td>" << endl;
      body << "      <td>" << films[i]->get_length() << "</td>" << endl;
      body << "      <td>" << films[i]->get_rate() << "</td>" << endl;
      body << "      <td>" << films[i]->get_director() << "</td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/see_film_detail\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
      body << "          <button type=\"submit\" >See Details</button>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "    </tr>" << endl;
    }
    body << "  </table>" << endl;

    body << "  Purchasable Films : <br>" << endl;
    body << "  <table>" << endl;
    body << "    <tr>" << endl;
    body << "      <th>Name</th>" << endl;
    body << "      <th>Price</th> " << endl;
    body << "      <th>Production Year</th>" << endl;
    body << "      <th>Length</th>" << endl;
    body << "      <th>Rate</th>" << endl;
    body << "      <th>Director</th>" << endl;
    body << "    </tr>" << endl;
    for(int i = 0; i < purchasable_films.size(); i++) {
      if(!manager->if_purchased(films[i], stoi(req->getSessionId()))) {
        body << "    <tr>" << endl;
        body << "      <td>" << purchasable_films[i]->get_name() << "</td>" << endl;
        body << "      <td>" << purchasable_films[i]->get_price() << "</td> " << endl;
        body << "      <td>" << purchasable_films[i]->get_year() << " </td>" << endl;
        body << "      <td>" << purchasable_films[i]->get_length() << "</td>" << endl;
        body << "      <td>" << purchasable_films[i]->get_rate() << "</td>" << endl;
        body << "      <td>" << purchasable_films[i]->get_director() << "</td>" << endl;
        body << "      <td>" << endl;
        body << "        <form action=\"/see_film_detail\" method=\"post\">" << endl;
        body << "          <input name=\"film_id\" type=\"text\" value=\" " << purchasable_films[i]->get_id() << "\" hiden>" << endl;
        body << "          <button type=\"submit\" >See Details</button>" << endl;
        body << "        </form>" << endl;
        body << "      </td>" << endl;
        body << "      <td>" << endl;
        body << "        <form action=\"/publisher_homepage/buy_film\" method=\"post\">" << endl;
        body << "          <input name=\"film_id\" type=\"text\" value=\" " << purchasable_films[i]->get_id() << "\" hiden>" << endl;
        body << "          <button type=\"submit\" >Buy</button>" << endl;
        body << "        </form>" << endl;
        body << "      </td>" << endl;
        body << "    </tr>" << endl;
      }
    }
    body << "  </table>" << endl;

    body << "</body>" << endl;
    body << "</html>" << endl;
    res->setBody(body.str());
  }
  return res;
}

CustomerHomePage::CustomerHomePage(Manager* _manager) : manager(_manager) {}
Response* CustomerHomePage::callback(Request *req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "publisher")
    res = Response::redirect("/error");
  else {
    res->setHeader("Content-Type", "text/html");
    vector<Film*> films = manager->see_purchaeable_films(stoi(req->getSessionId()));
    stringstream body;
    body << "<!DOCTYPE html>" << endl;
    body << "<html lang=\"en\">" << endl;
    body << "<head>" << endl;
    body << "  <title>User HomePage</title>" << endl;
    body << "  <meta charset=\"utf-8\">" << endl;
    body << "</head>" << endl;
    body << "<body>" << endl;
    body << "  <ul>" << endl;
    body << "    <li><a href=\"/customer_homepage/profile\">Profile</a></li>" << endl;
    body << "    <li><a href=\"/customer_homepage/add_credit\">Add Credit : " << manager->find_user(stoi(req->getSessionId()))->see_money() << " </a></li>" << endl;
    body << "    <li><a href=\"/logout\">Logout</a></li>" << endl;
    body << "  </ul>" << endl;
    body << "  <form action=\"/customer_homepage/search_film\" method=\"post\">" << endl;
    body << "    Director : <input name=\"director\" type=\"text\" placeholder=\"Enter Director Name\" /> <br>" << endl;
    body << "    <button type=\"submit\" >Search</button>" << endl;
    body << "  </form>" << endl;

    body << "  Purchasable Films : <br>" << endl;
    body << "  <table>" << endl;
    body << "    <tr>" << endl;
    body << "      <th>Name</th>" << endl;
    body << "      <th>Price</th> " << endl;
    body << "      <th>Production Year</th>" << endl;
    body << "      <th>Length</th>" << endl;
    body << "      <th>Rate</th>" << endl;
    body << "      <th>Director</th>" << endl;
    body << "    </tr>" << endl;
    for(int i = 0; i < films.size(); i++) {
      if(!manager->if_purchased(films[i], stoi(req->getSessionId()))) {
        body << "    <tr>" << endl;
        body << "      <td>" << films[i]->get_name() << "</td>" << endl;
        body << "      <td>" << films[i]->get_price() << "</td> " << endl;
        body << "      <td>" << films[i]->get_year() << " </td>" << endl;
        body << "      <td>" << films[i]->get_length() << "</td>" << endl;
        body << "      <td>" << films[i]->get_rate() << "</td>" << endl;
        body << "      <td>" << films[i]->get_director() << "</td>" << endl;
        body << "      <td>" << endl;
        body << "      <td>" << endl;
        body << "        <form action=\"/see_film_detail\" method=\"post\">" << endl;
        body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
        body << "          <button type=\"submit\" >See Details</button>" << endl;
        body << "        </form>" << endl;
        body << "      </td>" << endl;
        body << "      <td>" << endl;
        body << "        <form action=\"/customer_homepage/buy_film\" method=\"post\">" << endl;
        body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
        body << "          <button type=\"submit\" >Buy</button>" << endl;
        body << "        </form>" << endl;
        body << "      </td>" << endl;
        body << "    </tr>" << endl;
      }
    }
    body << "  </table>" << endl;
    
    body << "</body>" << endl;
    body << "</html>" << endl;
    res->setBody(body.str());
  }
  return res;
}

PublisherProfile::PublisherProfile(Manager* _manager) : manager(_manager) {}
Response* PublisherProfile::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "customer")
    res = Response::redirect("/error");
  else {
    res->setHeader("Content-Type", "text/html");
    vector<Film*> films = manager->get_purchased(stoi(req->getSessionId()));
    stringstream body;
    body << "<!DOCTYPE html>" << endl;
    body << "<html lang=\"en\">" << endl;
    body << "<head>" << endl;
    body << "  <title>User Profile</title>" << endl;
    body << "  <meta charset=\"utf-8\">" << endl;
    body << "</head>" << endl;
    body << "<body>" << endl;
    body << "  <ul>" << endl;
    body << "    <li><a href=\"/publisher_homepage\">Home Page</a></li>" << endl;
    body << "    <li><a href=\"/logout\">Logout</a></li>" << endl;
    body << "  </ul>" << endl;

    body << "  Purchased Films : <br>" << endl;
    body << "  <table>" << endl;
    body << "    <tr>" << endl;
    body << "      <th>Name</th>" << endl;
    body << "      <th>Price</th> " << endl;
    body << "      <th>Production Year</th>" << endl;
    body << "      <th>Length</th>" << endl;
    body << "      <th>Rate</th>" << endl;
    body << "      <th>Director</th>" << endl;
    body << "    </tr>" << endl;
    for(int i = 0; i < films.size(); i++) {
      body << "    <tr>" << endl;
      body << "      <td>" << films[i]->get_name() << "</td>" << endl;
      body << "      <td>" << films[i]->get_price() << "</td> " << endl;
      body << "      <td>" << films[i]->get_year() << " </td>" << endl;
      body << "      <td>" << films[i]->get_length() << "</td>" << endl;
      body << "      <td>" << films[i]->get_rate() << "</td>" << endl;
      body << "      <td>" << films[i]->get_director() << "</td>" << endl;
      body << "      <td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/see_film_detail\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
      body << "          <button type=\"submit\" >See Details</button>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/rate_comment_film\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
      body << "          <button type=\"submit\" >Rate and Comment</button>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "    </tr>" << endl;
    }
    body << "  </table>" << endl;
    
    body << "</body>" << endl;
    body << "</html>" << endl;
    res->setBody(body.str());
  }
  return res;
}

CustomerProfile::CustomerProfile(Manager* _manager) : manager(_manager) {}
Response* CustomerProfile::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "publisher")
    res = Response::redirect("/error");
  else {
    res->setHeader("Content-Type", "text/html");
    vector<Film*> films = manager->get_purchased(stoi(req->getSessionId()));
    stringstream body;
    body << "<!DOCTYPE html>" << endl;
    body << "<html lang=\"en\">" << endl;
    body << "<head>" << endl;
    body << "  <title>User Profile</title>" << endl;
    body << "  <meta charset=\"utf-8\">" << endl;
    body << "</head>" << endl;
    body << "<body>" << endl;
    body << "  <ul>" << endl;
    body << "    <li><a href=\"/customer_homepage/profile\">Home Page</a></li>" << endl;
    body << "    <li><a href=\"/logout\">Logout</a></li>" << endl;
    body << "  </ul>" << endl;

    body << "  Purchased Films : <br>" << endl;
    body << "  <table>" << endl;
    body << "    <tr>" << endl;
    body << "      <th>Name</th>" << endl;
    body << "      <th>Price</th> " << endl;
    body << "      <th>Production Year</th>" << endl;
    body << "      <th>Length</th>" << endl;
    body << "      <th>Rate</th>" << endl;
    body << "      <th>Director</th>" << endl;
    body << "    </tr>" << endl;
    for(int i = 0; i < films.size(); i++) {
      body << "    <tr>" << endl;
      body << "      <td>" << films[i]->get_name() << "</td>" << endl;
      body << "      <td>" << films[i]->get_price() << "</td> " << endl;
      body << "      <td>" << films[i]->get_year() << " </td>" << endl;
      body << "      <td>" << films[i]->get_length() << "</td>" << endl;
      body << "      <td>" << films[i]->get_rate() << "</td>" << endl;
      body << "      <td>" << films[i]->get_director() << "</td>" << endl;
      body << "      <td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/see_film_detail\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
      body << "          <button type=\"submit\" >See Details</button>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/rate_comment_film\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"text\" value=\" " << films[i]->get_id() << "\" hiden>" << endl;
      body << "          <button type=\"submit\" >Rate and Comment</button>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "    </tr>" << endl;
    }
    body << "  </table>" << endl;
    
    body << "</body>" << endl;
    body << "</html>" << endl;
    res->setBody(body.str());
  }
  return res;
}

AddFilm::AddFilm(Manager* _manager) : manager(_manager) {} 
Response* AddFilm::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "customer")
    res = Response::redirect("/error");
  else {
    string name = req->getBodyParam("name");
    int length = stoi(req->getBodyParam("length"));
    int price = stoi(req->getBodyParam("price"));
    int year = stoi(req->getBodyParam("production_year"));
    string director = req->getBodyParam("director");
    string summary = req->getBodyParam("summary");
    manager->add_film(name, year, length, price, summary, director, stoi(req->getSessionId()));
    res = Response::redirect("/home_page");
  }
  return res;
}

PublisherBuyFilm::PublisherBuyFilm(Manager* _manager) : manager(_manager) {}
Response* PublisherBuyFilm::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "customer")
    res = Response::redirect("/error");
  else {
    manager->buy_film(stoi(req->getBodyParam("film_id")), stoi(req->getSessionId()));
    res = Response::redirect("/publisher_homepage/profile");
  }
  return res;
}

CustomerBuyFilm::CustomerBuyFilm(Manager* _manager) : manager(_manager) {}
Response* CustomerBuyFilm::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "publisher")
    res = Response::redirect("/error");
  else {
    manager->buy_film(stoi(req->getBodyParam("film_id")), stoi(req->getSessionId()));
    res = Response::redirect("/customer_homepage/profile");
  }
  return res;
}

PublisherAddCredit::PublisherAddCredit(Manager* _manager) : manager(_manager) {}
Response* PublisherAddCredit::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "customer")
    res = Response::redirect("/error");
  else {
    manager->post_money(stoi(req->getBodyParam("credit")), stoi(req->getSessionId()));
    res = Response::redirect("/publisher_homepage");
  }
  return res;
}

CustomerAddCredit::CustomerAddCredit(Manager* _manager) : manager(_manager) {}
Response* CustomerAddCredit::callback(Request* req) {
  Response* res = new Response;
  if(req->getSessionId() == "SID")
    res = Response::redirect("/error");
  else if(manager->find_user(stoi(req->getSessionId()))->get_type() == "publisher")
    res = Response::redirect("/error");
  else {
    manager->post_money(stoi(req->getBodyParam("credit")), stoi(req->getSessionId()));
    res = Response::redirect("/customer_homepage");
  }
  return res;
}

Logout::Logout(Manager* _manager) : manager(_manager) {}
Response* Logout::callback(Request* req) {
  Response* res = new Response;
  res = Response::redirect("/login");
  res->setSessionId("SID");
  return res; 
} 
