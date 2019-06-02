#include "exeptions.h"

using namespace std;

char const * NotFound::what() const noexcept {
    return "Not Found";
}

char const * BadRequest::what() const noexcept {
    return "Bad Request";
}

char const * PermissionDenied::what() const noexcept {
    return "Permission Denied";
}