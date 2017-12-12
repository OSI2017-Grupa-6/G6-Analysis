#include"Load.h"

static int number_of_files;
vector<Receipt> get_all_files_names_within_folder(string folder)
{
	std::ifstream myFile;

	vector<Receipt> bills;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

				//names.push_back(fd.cFileName);
				std::cout << fd.cFileName << std::endl;
				string temp = fd.cFileName;
				temp = "Racuni/" + temp;
				myFile.open(temp.c_str());
				Receipt new_receipt = format(temp.c_str());
				bool wrong_format = (&new_receipt == &Receipt::null_receipt);
				if (!wrong_format)
					bills.push_back(new_receipt);
				myFile.close();
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return bills;
}

