#include "Analyst.h"
#include"Windows.h"
#
using std::string;
Analyst::Analyst(string name,string lastName,string pin,int usergroup,string username):
	UsersGroup(name, lastName, pin, usergroup, username) {}

bool Analyst::look_for_buyer()
{
	string buyer;
	std::cout << "Buyer's name:";
	std::cin >> buyer;

	string folder = "Pregled za kupca";
	string search_path =folder + "/*.*";
	 WIN32_FIND_DATA fd;
	 HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	 if (hFind != INVALID_HANDLE_VALUE) {
		 do {
		 } while (fd.cFileName != (buyer+".txt") && ::FindNextFile(hFind, &fd)  );
		 ::FindClose(hFind);
	 }
	 if (fd.cFileName != (buyer+".txt")) {
		 std::cout << "Not found";
		 return false;
	 }
	 std::ifstream f;
	 folder = fd.cFileName;
	 f.open("Pregled za kupca\\"+ folder);
	 std::cout << f.rdbuf();
	 f.close();
	 return true;
}

int Analyst::options()
{
	look_for_buyer();
	return LOGOUT;
}



