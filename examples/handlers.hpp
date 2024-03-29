#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <sstream>
#include "manager.h"
#include "user.h"
#include "publisher.h"
#include "customer.h"

class LoginHnadler : public RequestHandler {
public:
  LoginHnadler(Manager* _manager);
  Response *callback(Request *);
private: 
  Manager* manager;
};

class SignupHandler : public RequestHandler {
public:
  SignupHandler(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class HomePageHandler : public RequestHandler {
public: 
  HomePageHandler(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class PublisherHomePage : public RequestHandler {
public:
  PublisherHomePage(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class CustomerHomePage : public RequestHandler {
public:
  CustomerHomePage(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class PublisherProfile : public RequestHandler {
public:
  PublisherProfile(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class CustomerProfile : public RequestHandler {
public:
  CustomerProfile(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class AddFilm : public RequestHandler {
public:
  AddFilm(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class PublisherBuyFilm : public RequestHandler {
public:
  PublisherBuyFilm(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class CustomerBuyFilm : public RequestHandler {
public:
  CustomerBuyFilm(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class PublisherAddCredit : public RequestHandler {
public:
  PublisherAddCredit(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class CustomerAddCredit : public RequestHandler {
public:
  CustomerAddCredit(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

class Logout : public RequestHandler {
public:
  Logout(Manager* _manager);
  Response *callback(Request *);
private:
  Manager* manager;
};

#endif
