#include"Processing.h"
#include"Receipt.h"
#include"Load.h"

#include<winapifamily.h>
#include<experimental/filesystem>
#include<vector>
#include<string>

void processing(const char* folder)
{
	vector<Receipt> receipts;
	receipts = load(folder);
	std::ofstream no_error, error;
	string oldDirectory = "C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\Racuni\\";
	std::experimental::filesystem::path newPath("C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\ProcessedReceipts\\");
	//CreateDirectory("C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\ProcessedRecipts", 0);

    std::experimental::filesystem::create_directory(newPath);
	while (receipts.empty() == false)
	{
		time_t rawtime;
		struct tm  timeinfo;
		char buffer[80];
		time(&rawtime);
		 localtime_s(&timeinfo,&rawtime);
		strftime(buffer, sizeof(buffer), " %d-%m-%Y %I:%M:%S", &timeinfo);
		std::string str(buffer);
	
		Receipt receipt = receipts.back();
		receipts.pop_back();

		std::ofstream newFile;
		std::ifstream oldFile;
		string r = receipt.getReceiptName(); //name of receipt
		r=r.substr(0, r.size() - 4);
		r += str.substr(0, 11);

		oldFile.open("C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\Racuni\\" + receipt.getReceiptName());
		if (receipt.validate()) //saving in good file    
			newFile.open("C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\ProcessedReceipts\\" + r+".txt");
		else                     //saving in error file
			newFile.open("C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\ProcessedReceipts\\" + r+ "_error.txt");

		newFile << oldFile.rdbuf();
		oldFile.close();
		newFile.close();
	}
}
