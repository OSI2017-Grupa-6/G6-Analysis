#include"Processing.h"


#include<winapifamily.h>
#include<experimental/filesystem>
#include<vector>
#include<string>
#include<algorithm>
void processing(const char* folder, const char*path)
{
	vector<Receipt> receipts;
	receipts = load(folder);
	std::ofstream no_error, error;
	string p(path);
	string oldDirectory(p + "Racuni\\");
	string newPath(p + "ProcessedReceipts\\");

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
			correct.push_back(receipt);
		}
		else                     //saving in error file
			newFile.open(newPath + r + "_error.txt");

		newFile << oldFile.rdbuf();

		newFile.close();
		oldFile.close();
	}
	std::experimental::filesystem::remove_all(oldDirectory);
	std::experimental::filesystem::create_directory(oldDirectory);
	send_to_files(correct, "C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\");
}

void send_to_files(std::vector<Receipt>& bills, const char * path)
{
	std::experimental::filesystem::path newPath(path);
	string nPath(path);
	std::experimental::filesystem::create_directory(nPath + "Pregled za proizvod\\");
	std::experimental::filesystem::create_directory(nPath + "Pregled za kupca\\");
	std::string product;
	std::string buyer;
	Receipt temp("", 0, 0), second("", 0, 0);
	double price, amount;   //local variables
	string temp_date;       //   ~||~
	while (bills.size())
	{
		temp = bills.back();         //geting one receipt
		bills.pop_back();            //deleting it
		std::ofstream pFile;         //file for product
		std::ofstream bFile;         //file for buyer
		buyer = temp.getBuyer();
		std::iostream::pos_type p = 0;
		if (buyer != "") {        //checking if buyer is already registered
			bFile.open(nPath + "Pregled za kupca\\" + buyer + ".txt", std::ios::app); //opening file
			if (bFile.tellp() == p)
				bFile << "Datum kupovine   ukupno za platiti\n";
			temp_date = temp.getDate();
			bFile << temp_date << " ";
			bFile << temp.getPayment() << "\n";
		}
		for (int j = 0; j < temp.getSize(); ++j) {    //searching for products in receipt
			product = temp.getProductKey()[j];
			pFile.open(nPath + "Pregled za proizvod\\" + product + ".txt", std::ios::app); //opening file
			if (pFile.tellp() == p) pFile << "Prodano  cijena  ukupno za proizvod\n";
			pFile << temp.getProductSold()[j] << " ";
			pFile << temp.getProductPrice()[j] << " ";
			pFile << temp.getProductTotal()[j] << "\n";
			for (int k = 0; k < bills.size(); ++k)       //searching for this product in other recipts and deleting it if found
			{
				vector<string> tmp = bills[k].getProductKey();

				std::vector<string>::iterator it;
				if ((it = std::find(tmp.begin(), tmp.end(), product)) != tmp.end())
				{
					second = bills[k];
					int index = it - tmp.begin();
					pFile << second.getProductSold()[index] << " ";
					pFile << second.getProductPrice()[index] << " ";
					pFile << second.getProductTotal()[index] << "\n";
					bills[k].erase(index);
				}
			}
			pFile.close();
		}

		for (int k = 0; k < bills.size() && buyer != ""; ++k)
			if (bills[k].getBuyer() == buyer) {
				temp_date = bills[k].getDate();
				bFile << temp_date << " ";
				bFile << bills[k].getPayment() << "\n";
				bills[k].erase_buyer();
			}
		bFile.close();
	}
}
