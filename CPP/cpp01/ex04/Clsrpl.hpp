#include <iostream>
#include <fstream>
#include <stdlib.h>

# ifndef Clsrpl_hpp
# define Clsrpl_hpp

class Clsrpl
{
private:
	std::string		file_name;
	std::string		s1;
	std::string		s2;
	std::string		Line;
	std::fstream	Out_file;
	std::fstream	In_file;
	void	open_outfile();
	void	open_infile();
public:
	Clsrpl(std::string f_n, std::string _s1, std::string _s2);
	void	replace();
};

#endif