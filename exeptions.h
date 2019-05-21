#ifndef EXEP_H
#define EXEP_H

#include <exception>

class NotFound : public std::exception {
public:
    virtual char const * what() const noexcept;
};

class BadRequest : public std::exception {
public:
    virtual char const * what() const noexcept;
};

class PermissionDenied : public std::exception {
public:
    virtual char const * what() const noexcept;
};

#endif