#include "Cgi.hpp"


Cgi::Cgi(){
    cmds = new char *[3];
    cmds[0] = NULL;
    cmds[1] = NULL;
    cmds[2] = NULL;
    env = new char *[10];
    env[0] = NULL;
    env[1] = NULL;
    env[2] = NULL;
    env[4] = NULL;
    env[5] = NULL;
    env[6] = NULL;
    env[7] = NULL;
    env[8] = NULL;
    env[9] = NULL;
    cgi_execueted = 0;
    resp_done = 0;
    is_run = 0;
}

Cgi::Cgi(Servers _serv, const string& m_type){
    serv = _serv;
    method_type = m_type;
    cmds = new char *[3];
    cmds[0] = NULL;
    cmds[1] = NULL;
    cmds[2] = NULL;
    env = new char *[10];
    env[0] = NULL;
    env[1] = NULL;
    env[2] = NULL;
    env[4] = NULL;
    env[5] = NULL;
    env[6] = NULL;
    env[7] = NULL;
    env[8] = NULL;
    env[9] = NULL;
    cgi_execueted = 0;
    resp_done = 0;
    is_run = 0;
}

Cgi& Cgi::operator=(const Cgi& oth){
    if (this != &oth){
        serv = oth.serv;
        method_type = oth.method_type;
    }
    return *this;
}

void Cgi::set_arg(Servers srv, const string& mtype, map<string, string> h){
    serv = srv;
    method_type = mtype;
    headers = h;
}

int Cgi::is_cookies(){
    map<string, string>::iterator it;
    it = headers.find("Cookie");
    if (it != headers.end()){
        cookies = it->second;
        return 1;
    }
    return 0;
}

void Cgi::exec_cgi(const string& fullUri_path){
    if (!is_run){
        if (!set_cmd(fullUri_path)){
            cgi_execueted = 1;
            get.serv.status = "415";
            get.get(serv.error_page["415"]);
            return ;
        }
        set_env(fullUri_path);
        cmd = cmds[0];
        is_run = 1;
        start_time = clock();
        pid = fork();
        if(pid < 0){
            perror("fork fail");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){
            file = fopen(out_file.c_str(), "w");
            if (file == NULL)
                exit(1);
            dup2(file->_fileno,STDOUT_FILENO);
            if(chdir(cgi_dir.c_str()) || execve(cmd,cmds,env) == -1)
                exit(1);
        }
    }
    waiting();
}

void Cgi::waiting(){
    if (waitpid(pid,&exit_stat,WNOHANG)>0){
        cgi_execueted = 1;
        if (WEXITSTATUS(exit_stat)){
            std::remove(out_file.c_str());
            get.serv.status = "500";
            get.get(serv.error_page["500"]);
            if (get.end)
                resp_done = 1;
        }
    }
    else{
        if ((clock()-start_time)/CLOCKS_PER_SEC > 10)
            kill_proc(1);
    }
}

void Cgi::kill_proc(int return_err_page){
    std::remove(out_file.c_str());
    kill(pid,SIGKILL);
    waitpid(pid,&exit_stat,0);
    cgi_execueted = 1;
    if (return_err_page){
        get.serv.status = "504";
        get.get(serv.error_page["504"]);
    }
    resp_done = 1;
}

void Cgi::execute(Method *method, int event){
    if (event == EPOLLIN)
        return ;
    if (!cgi_execueted)
        exec_cgi(method->fullUri_path);
    else{
        get.get(string(out_file));
        if (get.end){
            resp_done = 1;
            std::remove(out_file.c_str());
        }
    }
}

int Cgi::set_cmd(const string& fullUri_path){

    extension = get.extension_search(fullUri_path, '.');
    cgi_dir = get.extension_search(fullUri_path, '/');
    map<string,string>::iterator it;
    it = serv.UriLocation.cgi_path.find(extension);
    if (it == serv.UriLocation.cgi_path.end())
        return 0;
    string cmdCgi = it->second;
    cmds[0] =  new char[cmdCgi.length() + 1];
    strcpy(cmds[0],cmdCgi.c_str());
    cmds[1] = new char[ fullUri_path.length() + 1];
    strcpy(cmds[1],fullUri_path.c_str());
    return 1;
}

void Cgi::set_env(const string& fullUri_path){

    generate_file_name();
    string senv("QUERY_STRING=");
    senv += serv.querys;
    env[0] = new char[senv.length()+1];
    strcpy(env[0],senv.c_str());
    senv = "PATH_INFO=";
    senv += fullUri_path;
    env[1] = new char[senv.length()+1];
    strcpy(env[1],senv.c_str());
    senv = "REQUEST_METHOD=GET";
    env[2] = new char[senv.length()+1];
    strcpy(env[2],senv.c_str());
    senv = "SCRIPT_FILENAME=" + fullUri_path;
    env[3] = new char[senv.length()+1];
    strcpy(env[3],senv.c_str());
    senv = "SERVER_PROTOCOL=HTTP/1.1";
    env[4] = new char[senv.length()+1];
    strcpy(env[4],senv.c_str());
    senv = "REDIRECT_STATUS=HTTP/1.1 200 OK";
    env[5] = new char[senv.length()+1];
    strcpy(env[5],senv.c_str());
    if (is_cookies()){
        senv = "HTTP_COOKIE=" + cookies;
        env[6] = new char[senv.length()+1];
        strcpy(env[6],senv.c_str());    
    }
}

void Cgi::generate_file_name(){
    time_t currentTime = std::time(NULL);
    std::tm* tm = std::localtime(&currentTime);
    char time_B[80];
    std::strftime(time_B, sizeof(time_B), "%Y-%m-%d-%H-%M-%S", tm);
    out_file = time_B;
    out_file += string(".html");
}

Cgi::~Cgi(){
    for (int i = 0; cmds && cmds[i]; i++)
	    delete [] cmds[i];
    delete [] cmds;

    for (int i = 0; env[i]; i++)
	    delete [] env[i];
    delete [] env;
    if (!cgi_execueted && is_run)
        kill_proc(0);
}
