#include"Processing.h"
#include"Receipt.h"
#include"Load.h"

#include<winapifamily.h>
#include<experimental/filesystem>
#include<vector>
#include<string>

void processing(const char* folder, const char*path)
{
	vector<Receipt> receipts;
	receipts = load(folder);
	std::ofstream no_error, error;
	string oldDirectory(path);
	string newPath(oldDirectory + "\\ProcessedReceipts\\");
	//CreateDirectory("C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\ProcessedRecipts", 0);
	std::vector<Receipt> correct;   //later here we will save receipts that are correct

	std::experimental::filesystem::create_directory(newPath);
	int count = 0;
	while (receipts.empty() == false)
	{
		time_t rawtime;
		struct tm  timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, sizeof(buffer), " %d-%m-%Y %I:%M:%S", &timeinfo);
		std::string str(buffer);

		Receipt receipt = receipts.back();
		receipts.pop_back();

		std::ofstream newFile;
		std::ifstream oldFile;
		string r = receipt.getReceiptName(); //name of receipt
		r = r.substr(0, r.size() - 4);
		r += str.substr(0, 11);

		oldFile.open(oldDirectory + receipt.getReceiptName());
		if (receipt.validate()) {//saving in good file    
			newFile.open(newPath + r + ".txt");
			correct[count++] = receipt;
		}
		else                     //saving in error file
			newFile.open(newPath + r + "_error.txt");

		newFile << oldFile.rdbuf();
		oldFile.close();
		newFile.close();
	}
	std::experimental::filesystem::remove_all(oldDirectory);
	std::experimental::filesystem::create_directory(oldDirectory);
}