#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../Methods/Cgi.hpp"
#include "../Methods/Delete.hpp"

using namespace std;


class Cgi;

enum errors{
    Method_Unkounu = 1,
    Httpv_Unkounu = 2,
    Invalid_Header = 4,
    Not_Allowed_Method = 8,
    Uri_Too_Long = 16,
    Headers_Too_Large = 32,
    Body_SizeTooLarge = 64,
};

class Request
{
int is_cgi;
int method_type;
string req_h;
string valid_uri;
int err_end;
string error_resp;
Cgi cgi;
Get get;
vector<Servers> ser_vec;
int parce_req(const string& req1);
int parce_line(const string& line);
int parce_rline(const string& line);
int parce_key(const string& key);
int spl_reqh_body(string s1);
Method* create_method(const string &type);
void check_for_error(int event);
int set_serv();
int is_uri_valid(string _uri);
double body_size;
Servers serv;
std::string uri;
std::string http_v;
std::string body;
std::string type;
public:
    int error;
    int body_state;
    clock_t startTime;
    Get get_timeout;
    Method* method;
    std::map<std::string, std::string> headers;

    Request();
    Request(const vector<Servers>& ser);
    Request(const Request& req);
    Request& operator=(const Request& oth);
    void process_req(const string &req, int event);
    string get_respons() const;
    int resp_done() const;
    ~Request();
};

#endif