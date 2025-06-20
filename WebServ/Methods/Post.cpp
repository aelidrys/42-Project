/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:40:02 by onaciri           #+#    #+#             */
/*   Updated: 2024/03/04 16:21:27 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Post.hpp"

Post::Post()
{
	crfile = 0;
    time_out  = 0;
    pre_total_body = 0;
    enter_cgi = 0;
    chunk_ctl = 0;
    total_Body = 0;
    size_len = 0;
    left_over = 0;
    chunk_left = 0;
    rare = 0;
    special = 0;
    end = 0;
    MethodType = 0;
    find_sep = 0;
    is_first = 0;
    sep = "";
	sep_found = "";
    ran_file = "";
    the_file = "";
    file_hang = 0;
    here_is = 0;
    first_time = 0;
    first_run = 0;
    cgi_exe = 0;
    error = 0;
    error_time = 0;
    cmd = NULL;
    env = NULL;
    exit_status = 0;
    add_i = 0;
    err = 0;
    mimeType();
}


Post::Post(const Post& post) : Method(post)
{
    *this = post;
}

Post& Post::operator=(const Post& post)
{
    (void)post;
    return *this;
}

Post::~Post()
{

    if (env)
    {
        for (int i = 0; env[i]; i++)
            delete[] env[i];
        delete[] env;
    }
    if (cmd)
    {
        for (int i = 0; cmd[i]; i++)
            delete[] cmd[i];
        delete[] cmd;
    }
}


/*work*/

int Post::is_num(std::string name)
{
    for (size_t i = 0; i < name.size(); i++)
    {
        if (!isdigit(name[i]))
            return (0);
    }
    return (1);
}

std::string Post::creat_file_name(int ret)
{
    
    std::time_t currentTime = std::time(NULL);
    // Convert time to struct tm in local time
    std::tm* timeInfo = std::localtime(&currentTime);
    // Format the time into a string
    char time_B[80];  // Sufficiently large time_B
    std::strftime(time_B, sizeof(time_B), "%Y-%m-%d_%H-%M-%S", timeInfo);
    // Get the resulting string
    std::string currentTimeString = time_B;
    std::string root;
    if (ret)
    {
        std::string tmp;
        std::stringstream ss;
        ss << add_i;
        ss >> tmp;
        add_i++;
        return currentTimeString + tmp;
    }
    else
        root = serv.UriLocation.upload_path;
    return  root + "/"+ currentTimeString;
}
void Post::mimeType()
{
   std::string str =
    "  text/html html\n"
    "text/css   css\n"
    "text/xml  xml\n"
    "image/gif gif\n"
    "image/jpeg jpeg\n"
    "application/javascript   js\n"
    "application/atom+xml  atom\n"
    "application/rss+xml  rss\n"
    "text/mathml    mml\n"
    "text/plain txt\n"
    "text/vnd.sun.j2me.app-descriptor    jad\n"
    "text/vnd.wap.wml  wml\n"
    "text/x-component htc\n"
    "image/avif avif\n"
    "image/png  png\n"
    "image/svg+xml  svg\n"
    "image/tiff  tiff\n"
    "image/vnd.wap.wbmp wbmp\n"
    "image/webp webp\n"
    "image/x-icon ico\n"
    "image/x-jng  jng\n"
    "image/x-ms-bmp  bmp\n"
    "font/woff   woff\n"
    "font/woff2  woff2\n"
    "application/java-archive jar\n"
    "application/json json\n"
    "application/mac-binhex40  hqx\n"
    "application/msword   doc\n"
    "application/pdf   pdf\n"
    "application/postscript                           ps\n"
    "application/rtf                                  rtf\n"
    "application/vnd.apple.mpegurl                    m3u8\n"
    "application/vnd.google-earth.kml+xml             kml\n"
    "application/vnd.google-earth.kmz                 kmz\n"
    "application/vnd.ms-excel                         xls\n"
    "application/vnd.ms-fontobject                    eot\n"
    "application/vnd.ms-powerpoint                    ppt\n"
    "application/vnd.oasis.opendocument.graphics      odg\n"
    "application/vnd.oasis.opendocument.presentation  odp\n"
    "application/vnd.oasis.opendocument.spreadsheet   ods\n"
    "application/vnd.oasis.opendocument.text          odt\n"
    "application/vnd.openxmlformats-officedocument.presentationml.presentation pptx\n"
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet xlsx\n"
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document docx\n"
    "application/vnd.wap.wmlc  wmlc\n"
    "application/wasm   wasm\n"
    "application/x-7z-compressed  7z\n"
    "application/x-cocoa cco\n"
    "application/x-java-archive-diff  jardiff\n"
    "application/x-java-jnlp-file jnlp\n"
    "application/x-makeself   run\n"
    "application/x-perl   pl\n"
    "application/x-pilot  pdb\n"
    "application/x-rar-compressed  rar\n"
    "application/x-redhat-package-manager    rpm\n"
    "application/x-sea     sea\n"
    "application/x-shockwave-flash     swf\n"
    "application/x-stuffit  sit\n"
    "application/x-tcl    tcl\n"
    "application/x-x509-ca-cert   crt\n"
    "application/x-xpinstall                          xpi\n"
    "application/xhtml+xml                            xhtml\n"
    "application/xspf+xml                             xspf\n"
    "application/zip                                  zip\n"
    "audio/midi  midi\n"
    "audio/mpeg mp3\n"
    "audio/ogg ogg\n"
    "audio/x-m4a       m4a\n"
    "audio/x-realaudio    ra\n"
    "video/3gpp  3gpp\n"
    "video/mp2t   ts\n"
    "video/mp4    mp4\n"
    "video/mpeg   mpeg\n"
    "video/quicktime   mov\n"
    "video/webm   webm\n"
    "video/x-flv  flv\n"
    "video/x-m4v  m4v\n"
    "video/x-mng  mng\n"
    "video/x-ms-asf     asf\n"
    "video/x-ms-wmv    wmv\n"
    "video/x-msvideo   avi\n"
    "text/x-c c";
    std::istringstream input(str);
    std::string line;
    str.clear();
    while (input >> line >> str)
        mime[line] = str;
    
}


std::string Post::add_new_name(std::string name, std::string mime)
{
    int i = 1;
    std::stringstream ss;
    std::string tmp;
    std::string tmp1;
    while (1)
    {
    
        ss << i;
        ss >> tmp;
        tmp1 = name + "(" + tmp +  ")" + "." +  mime;
        if (access(tmp1.c_str(), F_OK))
            return tmp1;
        i++;
        ss.clear();
    }
}

void Post::openFile(std::string body)
{
	std::string mimeVal;

	if (headers.find("Transfer-Encoding") != headers.end() && headers.find("Content-Type") != headers.end())
    {
        std::string tmp_C = (headers.find("Content-Type"))->second;
        if ((headers.find("Transfer-Encoding"))->second == "chunked"&& tmp_C.find("boundary=") == std::string::npos)
			MethodType = 1;
        else if ((headers.find("Transfer-Encoding"))->second == "chunked"&& tmp_C.find("boundary=") != std::string::npos)
        {
            error = 6;
            return ;
        }
        else if ((headers.find("Transfer-Encoding"))->second != "chunked")
        {
            error = 6;
            return ;
        }
    }
    else if (!MethodType && headers.find("Content-Type") != headers.end() && !serv.Is_cgi)
    {
        std::string tmp_C = (headers.find("Content-Type"))->second;
		if (tmp_C.find("boundary=") != std::string::npos)
		{
			buffer = tmp_C.substr(tmp_C.find("boundary=") + strlen("boundary=") , tmp_C.size() - tmp_C.find("boundary=") - strlen("boundary="));
			MethodType = 3;
			sep = "--";
			sep.append(buffer,0, buffer.size());
            sep_end = sep + "--";
			buffer = "";
			crfile = 1;
		}
    }
    else if (!MethodType && headers.find("Content-Type") != headers.end() && serv.Is_cgi)
    {
        std::string tmp_C = (headers.find("Content-Type"))->second;
		if (tmp_C.find("boundary=") != std::string::npos)
		{
            MethodType = 2;
		}
    }
    if (!MethodType)
    {
        MethodType = 2;
    }
	if (MethodType != 3 && headers.find("Content-Type") != headers.end())
    {
        if (mime.find( headers.find("Content-Type")->second) != mime.end())
		{
			mimeVal = mime.find((headers.find("Content-Type")->second))->second;
            content_type = headers.find("Content-Type")->second;
		}
		else
		{
            if (serv.Is_cgi)
            {
                content_type = (headers.find("Content-Type")->second);
            }
            else
            {                
                error = 9;
                return ;
            }
		}
    }
    else if (MethodType != 3)
    {
		crfile = -2;
        end = 1;
        error = 3;
        return ;
    }
    if (headers.find("Content-Length") != headers.end())
    {
        std::stringstream ss;
        if (!is_num(headers.find("Content-Length")->second))
        {
            error = 3;
            return ;
        }
        ss << headers.find("Content-Length")->second;
        ss >> size_len;   
             
    }
    else
    {
        if (headers.find("Transfer-Encoding") == headers.end())
        {
            error = 5;
            return ;
        }
    }
	if (MethodType != 3)
	{
        std::string time_B;
        if (!(serv.UriLocation.permession & UPLOAD) && serv.Is_cgi)
            time_B = creat_file_name(1);
        else
            time_B = creat_file_name(0);
		std::string fileName = time_B;
		std::string dot  = ".";
		fileName = time_B + dot;
		fileName = fileName + mimeVal;
        the_file = fileName;
		outFile.open(fileName.c_str(), std::ios::out | std::ios::binary);
        if (!outFile.is_open())
        {
            error = 4;
            return ;
        }
	}
	if (MethodType == 3 || outFile.is_open())
	{
        crfile = 1;
        if (MethodType == 2)
            normalFile(body);
        else if (MethodType == 1)
            chunked_file(body);
        else if (MethodType == 3)
            ft_boundary(body);     
    }
}

void Post::normalFile(std::string body)
{
    size_t body_size = 0;
    if (total_Body >= size_len)
    {
        end = 1;
        return ;
    }
    if (size_len > (body.size() + total_Body))
    {
        outFile.write(body.c_str(), body.size());
        total_Body += body.size();
        if (total_Body >= size_len)
        {
            outFile.close();
            crfile = -2;
            end = 1;
        }
    }
    else
    {
        body_size = size_len - total_Body;
        if (body.size() < body_size)
            body_size = body.size();
        outFile.write(body.c_str(), body_size);
        total_Body += body_size;
        outFile.close();
        crfile = -2;
        end = 1;
    }
}


void Post::chunk_write(std::string body)
{
    if (chunk_ctl >= (int)body.size())
    {
        outFile.write(body.c_str(), body.size());
        total_Body += body.size();
        buffer = "";
        left_over = 0;
        if ((int)body.size() == chunk_ctl)
        {
             rare = 1;
             chunk_ctl = 0;
             return;
        }
        chunk_ctl = chunk_ctl - body.size();
    }
    else
    {
        std::string tmp = "";
        std::string chunks_s;
        std::stringstream ss;

        buffer = "";
        tmp.append(body, 0, chunk_ctl);
        if (body.size() - chunk_ctl == 1)
        {
            outFile.write(tmp.c_str(), tmp.size());
            total_Body += tmp.size();
            buff_chunk = body.substr(chunk_ctl, 1);
            left_over = 1;
            chunk_ctl = 0;
            rare = 1;
            return ;
        }
        buffer = body.substr(chunk_ctl + 2, body.size() - chunk_ctl - 2);
        if (buffer.find("\r\n") != std::string::npos)
        {
            chunks_s = buffer.substr(0, buffer.find("\r\n"));
            buffer = buffer.substr(buffer.find("\r\n") + 2, buffer.size() -  buffer.find("\r\n") - 2);
            ss << chunks_s;
            ss >> std::hex >> chunk_ctl;
            if (!chunk_ctl)
            {
                outFile.write(tmp.c_str(), tmp.size());
                total_Body += tmp.size();
                outFile.close();
                crfile = -2;
                end = 1;
                out.close();
                return ;
            }
            tmp.append(buffer, 0, buffer.size());
            outFile.write(tmp.c_str(), tmp.size());
            total_Body += tmp.size();
            chunk_ctl = chunk_ctl - buffer.size();
        }
        else
        {
            outFile.write(tmp.c_str(), tmp.size());
            total_Body += tmp.size();
            buff_chunk = buffer;
            left_over = buffer.size();
            chunk_ctl = 0;
        }

    }

}

void Post::chunked_file(std::string body)
{
    std::stringstream ss;

    if (!body.size()&& !left_over)
        return ;
    if (left_over)
    {
        buffer = "";
        buffer.append(buff_chunk, 0, left_over);
        buffer.append(body, 0, body.size());
        body = buffer;
        left_over = 0;
    }
    if (chunk_ctl)
        chunk_write(body);
    else
    {
        std::string chunks_s;
        if (rare)
        {
            body = body.substr(2, body.size() - 2);
            rare = 0;
        }
        if (body.find("\r\n") == std::string::npos)
        {
            error = 3;
            return ;
        }
        chunks_s = body.substr(0, body.find("\r\n"));
        body = body.substr(body.find("\r\n") + 2, body.size() -  body.find("\r\n") - 2);
        ss << chunks_s;
        ss >> std::hex >> chunk_ctl;
		if (!chunk_ctl)
		{
           	outFile.close();
           	crfile = -2;
            end = 1;
            out.close();
            return ;
		}
        chunk_write(body);
    }
}


void    Post::ft_boundary(std::string& body)
{
    size_t pos;
    size_t pos1;

    if (left_over)
    {
        buffer.append(body, 0, body.size());
        left_over = 0;
        body = buffer;
        buffer = "";
    }
	if (body.find("\r") != std::string::npos && body.find("\r") + 3 - body.size() < sep.size())
	{
        if (body.find(sep_end) != std::string::npos)
        {
            if (body.find("\r\n") !=std::string::npos)
            {
                buffer = body.substr(0, body.size() - 2);
		        left_over = body.size() - 2;
                return ;
            }
        }
		buffer = body;
		left_over = body.size();
		return ;
	}
    if (body.find(sep_end) != std::string::npos)
    {
		pos = body.find(sep_end);
        pos1 = body.find(sep);
        if (!pos || pos == 2)
        {
            end = 1;
            if (out.is_open())
            out.close();
            return ;
        }
        else if (pos == pos1)
        {
            out.write(body.c_str(), pos - 2);
            total_Body += pos - 2;
            out.close();
            end = 1;
            return ;
        }
    }
	if (body.find(sep) != std::string::npos)
	{
        pos = body.find(sep);
        if (body.find(sep, pos + 1) != std::string::npos)
        {
            if (!pos || pos <= 2)
            {
                pos1 = body.find(sep, pos + 1);
                std::string buff_tmp = body.substr(0, pos1 );
                buffer = body.substr(pos1, body.size() - (pos1));
                left_over = body.size() - pos1 ;
                body = buff_tmp;
                here_is = 1;
            }
            else
            {
                std::string buff_tmp = body.substr(0, pos);
                buffer = body.substr(pos, body.size() - pos);
                left_over = buffer.size();
                body = buff_tmp;
                out.write(body.c_str(), body.size());
                total_Body += body.size();
                out.close();
                return ;
            }
        }
        if (body.find("\r\n\r\n") != std::string::npos)
		{
			sep_found = body.substr(pos, sep.size());
            if (out.is_open())
            {
                if (pos > 2)
                {
                    buffer = body.substr(0, pos - 2);
                    out.write(buffer.c_str(), buffer.size());
                    total_Body += buffer.size();
                    buffer = body.substr(pos, body.size() - pos);
                    left_over = buffer.size();
                    out.close();
                    return ;
                }
                else
                    out.close();
            }
			if (body.find("name") != std::string::npos)
			{
                std::string mimeVal;
				pos = body.find("name");
                if (body.find("\"", pos + strlen("name=") + 1) != std::string::npos)
                    pos1 = body.find("\"", pos + strlen("name=") + 1);
				if (pos1 <= 1)
					pos1 = 2;
				std::string file = body.substr(pos + strlen("name=") + 1, pos1 - ( strlen("name=") + 1) - pos);
                if (!file[0])
                {
                    std::string time_B = creat_file_name(1);
                    file = time_B;
                }
                if (body.find("Content-Type:") != std::string::npos)
                {
                    std::string ext;
                    pos = body.find("Content-Type:");
                    pos1 = body.find("\r\n", pos);
                    ext = body.substr(pos + strlen("Content-Type: "), pos1 - (pos+ strlen("Content-Type: ")));
                    if (mime.find(ext) != mime.end())
	            		mimeVal = mime.find(ext)->second;
                    else
                    {
                        error = 9;
                        return ; 
                    }
                }
	            else
                    mimeVal = "txt";
                file = serv.UriLocation.upload_path + "/" +  file;
                std::string case0 = file;
                file = file + ".";
                file += mimeVal;
                if (access(file.c_str(),F_OK ) == 0)
                {
                    file  = add_new_name(case0, mimeVal);
                }
                out.open(file.c_str(), std::ios::out | std::ios::binary);
				if (!out.is_open())
                {
					error = 4;
                    return ;
                }
                name_bound.push_back(file);
				
			}
			else
			{
                std::string file;
                std::string time_B = creat_file_name(0);
                std::stringstream ss1;
                ss1 << file_hang;
                file = time_B + ss1.str();
                file_hang++;
                std::string dot  = ".";
                file = file +  dot;
                file = file + "txt";
                ss1.str("");
                out.open(file.c_str(), std::ios::out | std::ios::binary);
				if (!out.is_open())
                {
                    error = 4;
					return ;
                }
                name_bound.push_back(file);
			}
			buff_chunk = "";
			pos = body.find("\r\n\r\n");
            int end_sep;
            if (body.find(sep, pos) != std::string::npos)
            {
                pos1 = body.find(sep, pos);
                end_sep = pos1 - (pos + 4 + 2);
            }
            else 
                end_sep = body.size() - (pos + 4 );
            if (here_is)
                end_sep -= 2;
			buff_chunk.append(body, pos + 4, end_sep);
            out.write(buff_chunk.c_str(), buff_chunk.size() );
            total_Body += buff_chunk.size();
            here_is = 0;
		}
		else
		{
            if (left_over)
            {
                buffer.append(body, 0, body.size());
                left_over += body.size();   
            }
            else
            {
                buffer = body;
                left_over = body.size();
            }
            here_is = 0;
		}
	}
    else
    {
        if (out.is_open())
        {
            out.write(body.c_str(), body.size() );
            total_Body += body.size();
        }
        here_is = 0;
    }
}

std::string Post::find_ext()
{
    long i;
    if (!fullUri_path.size())
    {
        return std::string("");       
    }
    for (i = (long)fullUri_path.size() - 1; i >= 0 && fullUri_path[i]!= '.'; i--);

    if (!i || i == (long)fullUri_path.size() - 1)
    {
        return std::string("");
    }
    std::string ext_ret = fullUri_path.substr(i + 1,fullUri_path.size() - i);
    return ext_ret;
}


char **Post::set_cmd(std::string& ext_path)
{
    char **cmd = new char*[3];
    cmd[0] = new char[ext_path.size() + 1];
    cmd[1] = new char[name_of_script.size() + 1];
    cmd[2] = NULL;
    if (!cmd || !cmd[0] || !cmd[1])
    {
        if (cmd[0])
            delete[] cmd[0];
        if (cmd[1])
            delete[] cmd[1];
        if (cmd)
            delete[] cmd;
        return NULL;
    }
    std::strcpy(cmd[0], ext_path.c_str());
    std::strcpy(cmd[1], name_of_script.c_str());
    return cmd;
}


char **Post::set_env()
{
    std::string script_name;
    std::string script_name1;
    std::string content_len;
    std::string cont_type;
    std::string info_path;
    std::string query_str;
    std::string serv_prt;
    std::stringstream ss;
    std::string cookie;
    int is_cokie = 0;
    
    if (headers.find("Cookie") != headers.end())
    {
        is_cokie = 1;
        cookie = headers.find("Cookie")->second;
    }
	char **env = new char*[10 + is_cokie];
    if (!env)
        return NULL;
    env[0] = new char[strlen("REDIRECT_STATUS=HTTP/1.1 200 OK") + 1];
    if (!env[0])
    {
        delete[] env;
        return NULL;
    }
    std::strcpy(env[0], "REDIRECT_STATUS=HTTP/1.1 200 OK");
    env[1] = new char[strlen("REQUEST_METHOD=POST") + 1];
    if (!env[1])
    {
        delete[] env[0];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[1], "REQUEST_METHOD=POST");
    script_name = "SCRIPT_FILENAME=" + fullUri_path;
    env[2] = new char[script_name.size() + 1];
    if (!env[2])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[2], script_name.c_str());
    ss << total_Body;
    ss >> content_len;
    content_len =  "CONTENT_LENGTH=" + content_len;
    env[3] = new char[content_len.size() + 1];
    if (!env[3])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env[2];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[3], content_len.c_str());
    cont_type = "CONTENT_TYPE=" + content_type;
    env[4] = new char[cont_type.size() + 1];
    if (!env[4])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env[2];
        delete[] env[3];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[4], cont_type.c_str());
    info_path = "PATH_INFO=" + fullUri_path;
    env[5] = new char[info_path.size() + 1];
    if (!env[5])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env[2];
        delete[] env[3];
        delete[] env[4];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[5], info_path.c_str());
    serv_prt = "SERVER_PROTOCOL=HTTP/1.1";
    env[6] = new char[serv_prt.size() + 1];
        if (!env[6])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env[2];
        delete[] env[3];
        delete[] env[4];
        delete[] env[5];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[6], serv_prt.c_str());
    std::string nameScript = "SCRIPT_NAME=" + name_of_script;
    env[7] = new char[nameScript.size() + 1];
    if (!env[7])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env[2];
        delete[] env[3];
        delete[] env[4];
        delete[] env[5];
        delete[] env[6];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[7], nameScript.c_str());
    query_str = "QUERY_STRING=" + serv.querys;
    env[8] = new char[query_str.size() + 1];
    if (!env[8])
    {
        delete[] env[0];
        delete[] env[1];
        delete[] env[2];
        delete[] env[3];
        delete[] env[4];
        delete[] env[5];
        delete[] env[6];
        delete[] env[7];
        delete[] env;
        return NULL;
    }
    std::strcpy(env[8], query_str.c_str());
    if (is_cokie)
    {
        cookie = "HTTP_COOKIE=" + cookie;
        env[9] = new char[cookie.size() + 1];
        if (!env[9])
        {
            delete[] env[0];
            delete[] env[1];
            delete[] env[2];
            delete[] env[3];
            delete[] env[4];
            delete[] env[5];
            delete[] env[6];
            delete[] env[7];
            delete[] env[8];
            delete[] env;
            return NULL;
        }
        std::strcpy(env[9], cookie.c_str());
    }
    env[9 + is_cokie] = NULL;
    return env;
}

void Post::script_name()
{
    size_t i = fullUri_path.find(".");
    long find;
    while (i != std::string::npos)
    {
        find = i;
        i = fullUri_path.find(".", i + 1);
    }
    while (find >= 0 && fullUri_path[find] != '/')
        find--; 
    name_of_script = fullUri_path.substr(find + 1, fullUri_path.size() - find);
    my_root = fullUri_path.substr(0, fullUri_path.size() - name_of_script.size() - 1);
}

void Post::exe_cgi()
{
    if (!first_run)
    {
        std::string ext_path;

        end = 0;
        first_run = 1;
        std::string ext = find_ext();
        if (!ext.size())
        {
            error = 3;
            return ;
        }
        script_name();
        env = set_env();
        if (!env)
        {
            error = 4;
            return ;
        }
        if (serv.UriLocation.cgi_path.find(ext) != serv.UriLocation.cgi_path.end())
        {
            std::string ext_path = (serv.UriLocation.cgi_path.find(ext))->second;
            cmd = set_cmd(ext_path);
            if (!cmd)
            {
                error = 4;
                return ;
            }
        }
        else
        {
            error = 9;
            return ;
        }
        ran_file =  creat_file_name(1);
        ran_file = my_root + "/" + ran_file + ".html";
        start_time = clock();
        pid = fork();
        if (pid < 0)
        {
            error = 4;
            return ;
        }
        if (pid == 0)
        {
            FILE *infile;
            FILE *outfile;  
            infile = fopen(the_file.c_str(), "r");
            outfile = fopen(ran_file.c_str(), "w");
            if (chdir(my_root.c_str()))
                exit(3);
            if (!infile || !outfile)
            {
                exit(2);
            }

            dup2(infile->_fileno, STDIN_FILENO);
            dup2(outfile->_fileno, STDOUT_FILENO);
            if (execve(cmd[0], cmd, env) == -1)
            {
                exit(1);
            }
        }
    }
    if (waitpid(pid, &exit_status, WNOHANG) > 0)
    {
        int exit_status1 = WEXITSTATUS(exit_status);
        if (exit_status1)
        {
            error = 4;
        }
        else
            cgi_exe = 1;
        int rem = std::remove(the_file.c_str());
        if (rem)
        {
            error = 4;
        }
    }
    else if ((clock() - start_time) / CLOCKS_PER_SEC > 10)
    {
        kill(pid, SIGKILL);
        waitpid(pid, &exit_status, 0);
        int rem = std::remove(the_file.c_str());
        int ram = std::remove(ran_file.c_str());
        if (rem || ram)
        {
            error = 4;
            return ;
        }
        error = 2;
    }
}


void Post::ft_error()
{
    if ((access(the_file.c_str(),F_OK ) == 0 || MethodType == 3 ) && !error_time)
    {
        if (MethodType == 3)
        {
            for (size_t i = 0; i < name_bound.size(); i++)
            {
                int rem = std::remove(name_bound[i].c_str());
                if (rem)
                {
                    error = 4;
                    error_time = 1;
                }
            }
        }
        else
        {
            int rem = std::remove(the_file.c_str());
            if (rem)
            {
                error = 4;
                error_time = 1;
            }
        }
    }
    
    if (serv.Is_cgi && !error_time)
    {
        if (access(ran_file.c_str(),F_OK ) == 0)
        {
            int rem = std::remove(ran_file.c_str());
            if (rem)
            {
                error = 4;
            }
        }
        error_time = 1;
    }
    if (error == 2)
    {
        get.serv.status = "504";
        get.get(serv.error_page["504"]);
        serv.status = "504";
    }
    else if (error == 3)
    {
        get.serv.status = "400";
        get.get(serv.error_page["400"]);
        serv.status = "400";
    }
    else if (error == 4)
    {
        get.serv.status = "500";
        get.get(serv.error_page["500"]);
        serv.status = "500";
    }
    if (error == 5)
    {
        get.serv.status = "411";
        get.get(serv.error_page["411"]);
        serv.status = "411";
    }
    if (error == 6)
    {
        get.serv.status = "501";
        get.get(serv.error_page["501"]);
        serv.status = "501";
    }
    if (error == 7)
    {
        get.serv.status = "413";
        get.get(serv.error_page["413"]);
        serv.status = "413";
    }
    if (error == 8)
    {
        get.serv.status = "403";
        get.get(serv.error_page["403"]);
        serv.status = "403";
    }
    if (error == 9)
    {
        get.serv.status = "415";
        get.get(serv.error_page["415"]);
        serv.status = "415";
    }
    if (error == 10)
    {
        get.serv.status = "408";
        get.get(serv.error_page["408"]);
        serv.status = "408";
    }
    respons = get.respons;
    if (get.end)
        end = 1;
}


int Post::process(std::string body, int event)
{
    pre_total_body = total_Body;
    if (serv.status != "200 OK" &&  serv.status != "201 Created" && serv.Is_cgi)
    {
        if (event == EPOLLOUT)
        {
            get.serv.status = serv.status;
            get.get(fullUri_path);
            respons += get.respons;
            if (get.end)
                end = 1;
        }
        return 0;
    }
    if (!(serv.UriLocation.permession & UPLOAD) && !serv.Is_cgi)
        error = 8;
    else
    {
        
        if (serv.UriLocation.upload_path.find("./") != std::string::npos)
        {
            size_t find = serv.UriLocation.upload_path.find("./");
            serv.UriLocation.upload_path = serv.UriLocation.upload_path.substr(find + 2,  serv.UriLocation.upload_path.size() - find);   
        }  
    }
    if (err && !error)
    {
        error = 7;
    }
    if (error && event == EPOLLOUT)
    {
        ft_error();
        return 1;
    }
    if (crfile > 0 && body.size() == 2 && MethodType == 1 && !enter_cgi)
    {
        buff_chunk += body;
        left_over += body.size();
        if (left_over <= 2)
            return 1;
    } 
	if (crfile > 0 && !enter_cgi)
    {
		if (MethodType == 2)
			normalFile(body);
		else if (MethodType == 1)
			chunked_file(body);
		else if (MethodType == 3)
			ft_boundary(body);
    }
	else if (!crfile && !enter_cgi)
		openFile(body);
    if (end && !cgi_exe)
        enter_cgi = 1;
    if (enter_cgi && serv.Is_cgi && !error && !cgi_exe)
        exe_cgi();
    if (cgi_exe && event == EPOLLOUT && !error)
    {
        get.get(ran_file);
        respons = get.respons;
        if (get.end)
        {
            end = 1;
            int x =  std::remove(ran_file.c_str());
            if (x)
            {
                error = 4;
            }
        }
    }
    if (end && !serv.Is_cgi && !error)
    {
        serv.status = "201 Created";
        respons = "HTTP/1.1 " + serv.status;
        respons += string("\r\nContent-Type: text/html\r\n");
        respons += string("Content-Length: 13");
        respons += "\r\n\r\n";
        respons += "File created\n";
    }
    if (total_Body == pre_total_body && !error && !enter_cgi)
    { 
        if (time_out)
        {
            if ((clock() - start_time) / CLOCKS_PER_SEC > 5)
            {
                error = 10;
            }   
        }
        else
        {
            start_time = clock();
            time_out = 1;
        }
    }
    else
        time_out = 0;
    return 1; 
}