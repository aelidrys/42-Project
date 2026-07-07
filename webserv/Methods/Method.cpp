#include "Method.hpp"

Method::Method(){
    err = 0;
}

Method::Method(const Method& oth){
    *this = oth;
}

Method& Method::operator=(const Method& oth){
    if (this != &oth){
        err = oth.err;
        end = oth.end;
        serv = oth.serv;
        uri = oth.uri;
        http_v = oth.http_v;
        headers = oth.headers;
        respons = oth.respons;
        fullUri_path = oth.fullUri_path;
    }
    return *this;
}


Method::~Method(){
    ;
}