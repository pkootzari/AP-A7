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
      body << "          <input name=\"film_id\" type=\"number\" value=\" " << films[i]->get_id() << "\" hidden>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "    </tr>" << endl;
    }
    body << "  </table>" << endl;

    body << "  Parchasable Films : <br>" << endl;
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
      body << "      <td>" << purchasable_films[i]->get_name() << "</td>" << endl;
      body << "      <td>" << purchasable_films[i]->get_price() << "</td> " << endl;
      body << "      <td>" << purchasable_films[i]->get_year() << " </td>" << endl;
      body << "      <td>" << purchasable_films[i]->get_length() << "</td>" << endl;
      body << "      <td>" << purchasable_films[i]->get_rate() << "</td>" << endl;
      body << "      <td>" << purchasable_films[i]->get_director() << "</td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/see_film_detail\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"number\" value=\" " << purchasable_films[i]->get_id() << "\" hidden>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/publisher_homepage/buy_film\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"number\" value=\" " << purchasable_films[i]->get_id() << "\" hidden>" << endl;
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
      body << "          <input name=\"film_id\" type=\"number\" value=\" " << films[i]->get_id() << "\" hidden>" << endl;
      body << "        </form>" << endl;
      body << "      </td>" << endl;
      body << "      <td>" << endl;
      body << "        <form action=\"/customer_homepage/buy_film\" method=\"post\">" << endl;
      body << "          <input name=\"film_id\" type=\"number\" value=\" " << films[i]->get_id() << "\" hidden>" << endl;
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

Logout::Logout(Manager* _manager) : manager(_manager) {}
Response* Logout::callback(Request* req) {
  Response* res = new Response;
  res->setSessionId("SID");
  res = Response::redirect("/login");
  res->setSessionId("SID");
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
