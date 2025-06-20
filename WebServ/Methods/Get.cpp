#include "Get.hpp"
#include <sys/stat.h>

Get::Get(){
    set_extentions();
    set_err_page();
    end = 0;
    opened = 0;
    content_len = -1;
    head_size = 0;
    body_size = 0;
}


Get::Get(const Get& oth): Method(oth){
    set_extentions();
    set_err_page();
    head_size = 0;
    content_len = -1;
    *this = oth;
}


Get& Get::operator=(const Get& oth){
    if (this != &oth){
        head_size = oth.head_size;
        serv = oth.serv;
        http_v = oth.http_v;
        uri = oth.uri;
        headers = oth.headers;
        fullUri_path = oth.fullUri_path;
        content_len = oth.content_len;
        types = oth.types;
        body_size = oth.body_size;
    }
    return *this;
}

void Get::set_err_page(){
    err_pages["400"] = "400 Bad Request";
    err_pages["403"] = "403 Forbidden";
    err_pages["404"] = "404 Not Found";
    err_pages["405"] = "405 Method Not Allowed";
    err_pages["408"] = "408 Request Timeout";
    err_pages["411"] = "411 Length Required";
    err_pages["413"] = "413 Request Entity Too Large";
    err_pages["414"] = "414 Request-URI Too Long";
    err_pages["415"] = "415 Unsupported Media Type";
    err_pages["500"] = "500 Internal Server Error";
    err_pages["501"] = "501 Not Implemented";
    err_pages["504"] = "504 Gateway Timeout";
    err_pages["505"] = "505 HTTP Version Not Supported";
}

void Get::set_extentions(){
    types["html"] = "text/html";
    types["css"] = "text/css";
    types["xml"] = "text/xml";
    types["gif"] = "image/gif";
    types["jpeg"] = "image/jpeg";
    types["js"] = "application/javascript";
    types["atom"] = "application/atom+xml";
    types["rss"] = "application/rss+xml";
    types["mml"] = "text/mathml";
    types["txt"] = "text/plain";
    types["conf"] = "text/plain";
    types["jad"] = "text/vnd.sun.j2me.app-descriptor";
    types["wml"] = "text/vnd.wap.wml";
    types["htc"] = "text/x-component";
    types["avif"] = "image/avif";
    types["png"] = "image/png";
    types["svg"] = "image/svg+xml";
    types["tiff"] = "image/tiff";
    types["wbmp"] = "image/vnd.wap.wbmp";
    types["webp"] = "image/webp";
    types["ico"] = "image/x-icon";
    types["jng"] = "image/x-jng";
    types["jpg"] = "image/jpg";
    types["bmp"] = "image/x-ms-bmp";
    types["woff"] = "font/woff";
    types["woff2"] = "font/woff2";
    types["jar"] = "application/java-archive";
    types["json"] = "application/json";
    types["hqx"] = "application/mac-binhex40";
    types["doc"] = "application/msword";
    types["pdf"] = "application/pdf";
    types["ps"] = "application/postscript";
    types["rtf"] = "application/rtf";
    types["m3u8"] = "application/vnd.apple.mpegurl";
    types["kml"] = "application/vnd.google-earth.kml+xml";
    types["kmz"] = "application/vnd.google-earth.kmz";
    types["xls"] = "application/vnd.ms-excel";
    types["eot"] = "application/vnd.ms-fontobject";
    types["ppt"] = "application/vnd.ms-powerpoint";
    types["odg"] = "application/vnd.oasis.opendocument.graphics";
    types["odp"] = "application/vnd.oasis.opendocument.presentation";
    types["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    types["odt"] = "application/vnd.oasis.opendocument.text";
    types["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    types["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    types["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    types["wmlc"] = "application/vnd.wap.wmlc";
    types["wasm"] = "application/wasm";
    types["7z"] = "application/x-7z-compressed";
    types["cco"] = "application/x-cocoa";
    types["jardiff"] = "application/x-java-archive-diff";
    types["jnlp"] = "application/x-java-jnlp-file";
    types["run"] = "application/x-makeself";
    types["pdb"] = "application/x-pilot";
    types["rar"] = "application/x-rar-compressed";
    types["rpm"] = "application/x-redhat-package-manager";
    types["sea"] = "application/x-sea";
    types["swf"] = "application/x-shockwave-flash";
    types["sit"] = "application/x-stuffit";
    types["tcl"] = "application/x-tcl";
    types["crt"] = "application/x-x509-ca-cert";
    types["xpi"] = "application/x-xpinstall";
    types["xhtml"] = "application/xhtml+xml";
    types["xspf"] = "application/xspf+xml";
    types["zip"] = "application/zip";
    types["midi"] = "audio/midi";
    types["mp3"] = "audio/mpeg";
    types["ogg"] = "audio/ogg";
    types["m4a"] = "audio/x-m4a";
    types["ra"] = "audio/x-realaudio";
    types["3gpp"] = "video/3gpp";
    types["ts"] = "video/mp2t";
    types["mp4"] = "video/mp4";
    types["mpeg"] = "video/mpeg";
    types["mov"] = "video/quicktime";
    types["webm"] = "video/webm";
    types["flv"] = "video/x-flv";
    types["m4v"] = "video/x-m4v";
    types["mng"] = "video/x-mng";
    types["asf"] = "video/x-ms-asf";
    types["wmv"] = "video/x-ms-wmv";
    types["avi"] = "video/x-msvideo";
    types["c"] = "text/x-c";
    types["cpp"] = "text/x-c";
    types["hpp"] = "text/x-c";
}

int Get::is_tpye_supported(const string& file_name){
    string exten = extension_search(file_name, '.');
    if (types.find(exten) != types.end())
        return 1;
    return 0;
}

string Get::extension_search(const string& f_name, int spl){
    string extnsion = "";
    size_t tmp = f_name.find(spl);
    pos = tmp;
    while (tmp != string::npos){
        pos = tmp;
        tmp = f_name.find(spl,pos+1);
    }
    if (pos != string::npos && pos+1 < f_name.size()){
        if (spl == '/')
            extnsion = f_name.substr(0,pos);
        else
            extnsion = f_name.substr(pos+1);
    }
    return extnsion;
}


int Get::set_content_type(const string& file_name){
    extension = extension_search(file_name, '.');
    if (types.find(extension) != types.end())
        content_type = types.find(extension)->second;
    else if (extension == "")
        content_type = "application/octet-stream";
    else{
        serv.status = "415";
        get(serv.error_page["415"]);
        return 0;
    }
    return 1;
}

void Get::set_content_length(string line){
    if (content_len != -1)
        return ;
    stringstream sl;
    string key;
    string value;
    sl<<line;
    getline(sl, key, ':');
    if (key == "Content-Length"){
        getline(sl,value,'\r');
        content_len = (size_t)strtod(value.c_str(), NULL);
    }
    return ;
}

int Get::check_headers(){
    int hed = 0;
    string line;
    getline(src_file,line);
    res_h += line + "\n";
    head_size = line.size()+1;
    while (line.size() && line[line.size()-1] == '\r' && !hed){
        getline(src_file,line);
        res_h += line + "\n";
        set_content_length(line);
        head_size += line.size()+1;
        if (head_size > 10240)
            break;
        if (line.size() && line == "\r")
            hed = 1;
    }
    return hed;
}

void Get::set_headers(){
    int hed = 0;
    respons = "HTTP/1.1 " + serv.status;
    respons += string("\r\nContent-Type: ");
    respons += content_type+string("\r\n");
    respons += string("Content-Length: ");
    hed = check_headers();
    if (hed){
        file_len -= head_size;
        if (content_len != -1){
            if ((size_t)content_len < file_len)
                file_len = content_len;
            content_len += head_size;
        }
    }
    stringstream ss;
    ss<<file_len;
    respons += ss.str()+string("\r\n");
    if (!hed){
        respons += "\r\n";
        respons += res_h;
    }
    else
        respons += res_h;
}


void Get::open_file(const string& file_name){
    if (!set_content_type(file_name))
        return ;
    src_file.open(file_name.c_str(), ios::in);
    opened = 1;
    if (!src_file.is_open()){
        get_err_page();
        opened = -1;
        return;
    }
    src_file.seekg(0, std::ios::end);
    file_len = src_file.tellg();
    src_file.seekg(0, std::ios::beg);
    set_headers();
}


void Get::get(const string& file_name){
    respons.clear();
    if (file_name == ""){
        respons = "HTTP/1.1 " + serv.status + "\r\n\r\n";
        end = 1;
        return;
    }
    if (!opened)
        open_file(file_name);
    if (opened == 1 && file_len && !end)
        read_file();
    if (opened == -1 || !file_len)
        end = 1;
}

void Get::read_file(){
    ssize_t r_len, max_r = 1024;
    string res;

    if (content_len != -1 && content_len > max_r)
        content_len -= max_r;
    else if (content_len != -1){
        max_r = content_len;
        content_len = 0;
    }
    res.resize(max_r);
    src_file.read(&res[0], max_r);
    r_len = src_file.gcount();
    res.resize(r_len);
    respons += res;
    if (r_len < max_r || !content_len){
        src_file.close();
        end = 1;
    }
}

int Get::process(string body, int event){
    (void)body;
    if (event == EPOLLIN)
        return 0;
    get(fullUri_path);
    return 0;
}

void Get::get_err_page(){
    string body_res;
    stringstream c_len;

    respons = "HTTP/1.1 "+ serv.status + string("\r\nContent_Type: text/html\r\n");
    body_res += "<title>"+ err_pages[serv.status] +string("</title>");
    body_res += "<body><h1>"+ err_pages[serv.status] +string("</h1></body>");
    c_len << body_res.size();
    respons += "Content_Length: " + c_len.str() + string("\r\n\r\n");
    respons += body_res;
    end = 1;
}

Get::~Get(){
}