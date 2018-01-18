#include"Load.h"

static int number_of_files;
vector<Receipt> load(string folder)
{
	std::ifstream myFile;

	vector<Receipt> bills;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

			
				string temp = fd.cFileName;
				temp = "Racuni\\" + temp;
				myFile.open(temp.c_str());
				Receipt new_receipt("", 0, 0);
			   new_receipt.format_checker(temp.c_str());
				   bills.push_back(new_receipt);
				myFile.close();
				
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	
	return bills;
}

int input_int(std::istream &stream)
{
	bool condition = false;
	int temp;
	do {
		condition = false;
		stream >>temp;
		condition = stream.fail();
		if (condition)
			std::cout << "Neispravan unos, pokusajte ponovo: " << std::endl;
		stream.clear();
		stream.ignore(10, '\n');

	} while (condition);
	return temp;
}

