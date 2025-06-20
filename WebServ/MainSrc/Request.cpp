#include "Request.hpp"

Request::Request()
{
    method = NULL;
    body_state = 0;
    body_size = 0;
    error = 0;
    is_cgi = 0;
    err_end = 0;
    valid_uri = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!%$&'()*+,;=";
}


Request::Request(const vector<Servers>& vser){
    method = NULL;
    body_state = 0;
    err_end = 0;
    body_size = 0;
    error = 0;
    ser_vec = vser;
    serv = ser_vec[0];
    is_cgi = 0;
    valid_uri = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!%$&'()*+,;=";
}

Request::Request(const Request& req1){
    method = NULL;
    *this = req1;
}

Request& Request::operator=(const Request& oth){
    if (this != &oth){
        delete method;
        error = oth.error;
        method = oth.method;
        body_state = oth.body_state;
        body_size = oth.body_size;
        type = oth.type;
        http_v = oth.http_v;
        body = oth.body;
        headers = oth.headers;
        uri = oth.uri;
        ser_vec = oth.ser_vec;
        serv = oth.serv;
        is_cgi = oth.is_cgi;
        valid_uri = oth.valid_uri;
        err_end = oth.err_end;
    }
    return *this;
}

int Request::set_serv(){
    string serv_name;
    if (headers.find("Host") == headers.end()){
        error |= Invalid_Header;
        return 0;
    }
    serv_name = headers.find("Host")->second;
    if (serv_name.find(":") != string::npos)
        serv_name = serv_name.substr(0,serv_name.find(":"));
    vector<Servers>::iterator it;
    it = find(ser_vec.begin(), ser_vec.end(), serv_name);
    if (it != ser_vec.end())
        serv = *it;
    else
        serv = ser_vec[0];
    return 1;
}

int Request::spl_reqh_body(string s1)
{
    if (body_state){
        body = s1;
        body_size += (double)body.size();
        if (body_size > serv.client_max_body_size){
            error |= Body_SizeTooLarge;
            if (method)
                method->err = 1;
        }
        return 0;
    }
    size_t pos = s1.find("\r\n\r\n", 0);
    if (pos != s1.npos)
    {
        body = s1.substr(pos + 4);
        req_h += s1.substr(0, pos);
        body_state = 1;
        body_size = body.size();
    }
    else
        req_h += s1;
    if (req_h.length() > 10000){
        error = error | Headers_Too_Large;
        return 0;
    }
    return body_state;
}

int Request::parce_key(const string &key)
{
    if (key.size() > 0 && !isalpha(key[0]))
        return 0;
    for (size_t i = 0; i < key.size(); i++)
    {
        if (!isalnum(key[i]) && key[i] != '_' && key[i] != '-')
            return 0;
    }
    return 1;
}

int Request::is_uri_valid(string _uri){
    for (size_t i = 0; i < _uri.size(); i++){
        if (valid_uri.find(_uri[i]) == string::npos)
            return 0;
    }
    return 1;  
}

int Request::parce_rline(const string &rline){
    stringstream ss;
    string tmp;
    ss<<rline;
    getline(ss, tmp, ' ');
    type = tmp;
    if (type != "GET" && type != "POST" && type != "DELETE"){
        error = Method_Unkounu;
        return 0;
    }
    method_type = (type == "GET") + (type == "POST")*2 + (type == "DELETE")*4;
    getline(ss, tmp, ' ');
    uri = tmp;
    if (!is_uri_valid(uri)){
        error |= Invalid_Header;
        return 0;
    }
    if (uri.size() > 1000){
        error = Uri_Too_Long;
        return 0;
    }
    getline(ss, tmp);
    if (tmp != "HTTP/1.1\r" && tmp != "HTTP/1.1"){
        error = Httpv_Unkounu;
        return 0;
    }
    http_v = tmp;
    return 1;
}

int Request::parce_line(const string &line)
{
    stringstream ss;
    string key;
    string value;

    ss<<line;
    getline(ss, key, ':');
    getline(ss, value, ' ');
    value.clear();
    getline(ss, value, '\r');
    if (!parce_key(key) && value.size()){
        error = error | Invalid_Header;
        return 0;
    }
    if (value.size() == 0){
        error = error | Invalid_Header;
        return 0;
    }
    headers[key] = value;
    return 1;
}

int Request::parce_req(const string &req)
{
    std::stringstream sstr;
    string line;

    if (error || !spl_reqh_body(req))
        return 1;
    sstr << req_h;
    getline(sstr,line);
    if (!parce_rline(line))
        return 0;
    while (sstr.peek() != -1)
    {
        getline(sstr, line);
        if (line.size() && !parce_line(line))
            return 0;
    }
    if (set_serv())
        serv.FillData(uri,type);
    if (!(serv.UriLocation.permession & method_type)){
        error = error | Not_Allowed_Method;
        return 0;
    }
    method = create_method(type);
    cgi.set_arg(serv, type, headers);
    if (serv.Is_cgi && !cgi.get.is_tpye_supported(serv.rootUri) && type == "GET")
        is_cgi = 1;
    return 1;
}

void Request::check_for_error(int event){
    if (!error || err_end || event == EPOLLIN)
        return;
    
    string err_page_name;
    if (error & Invalid_Header)
        err_page_name = "400";
    else if (error & Method_Unkounu){
        err_page_name = "501";
        if (type == "HEAD"){
            error_resp = "HTTP/1.1 501\r\n\r\n";
            return ;
        }
    }
    else if (error & Not_Allowed_Method)
        err_page_name = "405";
    else if (error & Uri_Too_Long)
        err_page_name = "414";
    else if (error & Httpv_Unkounu)
        err_page_name = "505";
    else if (error & Headers_Too_Large || error & Body_SizeTooLarge)
        err_page_name = "413";
    get.serv.status = err_page_name;
    get.get(serv.error_page[err_page_name]);
    error_resp = get.respons;
    if (get.end)
        err_end = 1;
}

void    Request::process_req(const string &req, int event){
    if (!parce_req(req) || error){
        if (error & Body_SizeTooLarge && type == "POST" && method)
            method->process(body, event);
        check_for_error(event);
        return ;
    }
    if (body_state && method){
        if (is_cgi)
            cgi.execute(method, event);
        else
            method->process(body, event);
    }
}

int Request::resp_done() const{
    if (error && err_end)
        return 1;
    if (is_cgi){
        if (cgi.resp_done)
            return 1;
    }
    if (method && method->end)
        return 1;
    return 0;
}

Method* Request::create_method(const string &type){
    Method* m = NULL;
    if (type == "GET")
        m = new Get();
    else if (type == "POST")
        m = new Post();
    else if (type == "DELETE")
        m = new Delete();
    if (m){
        m->headers = headers;
        m->http_v = http_v;
        m->uri = uri;
        m->fullUri_path = serv.rootUri;
        m->serv = serv;
        m->err = 0;
    }
    return (m);
}

string Request::get_respons() const{
    if (error && !(type == "POST" && method && method->end)){
        return error_resp;
    }
    if (!method)
        return("");
    if (is_cgi){
        return cgi.get.respons;
    }
    return (method->respons);
}

Request::~Request(){
    delete method;
}
