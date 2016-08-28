#include <divida/ReportXmlSerializer.h>

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace Divida;

void CostcoTest();

namespace
{

std::unique_ptr<Report> LoadReport(const std::string& path)
{
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(path.c_str());
	if (!result)
		throw Exception{ result.description() };

	auto report = ReportXmlSerializer::Read(document.child("report"));
	return std::move(report);
}

void PrintReportInfoForPersonToConsole(const Report& report, const Person& person)
{
	auto reportInfo = report.GetReportInfoForPerson(person.Name());
	if (reportInfo != nullptr)
	{
		if (reportInfo->Payments.size() != 0)
		{
			std::cout << person.Name() << " paid for:" << std::endl;
			std::cout << std::setw(32) << std::left << "Name" << std::setw(6) << "Amount" << std::endl;
			std::cout << std::setw(32) << std::left << "----" << std::setw(6) << "------" << std::endl;

			float total = 0.0f;
			for (auto payment : reportInfo->Payments)
			{
				total += payment.Amount;
				std::cout << std::setw(32) << std::left << payment.Name << std::setw(6) << std::right << payment.Amount << std::endl;
			}

			std::cout << std::endl;
			std::cout << std::setw(32) << std::left << "Total" << std::setw(6) << std::right << total << std::endl;

			std::cout << std::endl;
		}

		if (reportInfo->Expenses.size() != 0)
		{
			unsigned int namePrintWidth = report.GetItemNamePrintWidth();

			std::cout << person.Name() << " had the following expenses: " << std::endl;

			std::cout << std::setw(namePrintWidth) << std::left << "Name";
			std::cout << std::setw(5) << "Share" << std::setw(5) << "  x  " << std::setw(9) << "Item Cost";
			std::cout << std::setw(5) << "  =  " << std::setw(6) << "Amount" << std::endl;

			std::cout << std::setw(namePrintWidth) << std::left << "----";
			std::cout << std::setw(5) << "-----" << std::setw(5) << " " << std::setw(9) << "---------";
			std::cout << std::setw(5) << " " << std::setw(6) << "------" << std::endl;

			float total = 0.0f;
			for (auto expense : reportInfo->Expenses)
			{
				total += expense.Weight * expense.Amount;

				std::cout << std::setw(namePrintWidth) << std::left << expense.Name;
				std::cout << std::setw(5) << std::right << expense.Weight << std::setw(5) << "  x  " << std::setw(9) << expense.Amount;
				std::cout << std::setw(5) << "  =  " << std::setw(6) << expense.Weight * expense.Amount << std::endl;
			}

			std::cout << std::endl;
			std::cout << std::setw(namePrintWidth) << std::left << "Total" << std::setw(30) << std::right << total << std::endl;

			std::wcerr << std::endl;
		}

		std::cout << std::endl;
	}
}

void PrintToConsole(Report* report)
{
	auto transactions = report->CalculateTransactions();

	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
	std::cout << report->Name() << "\n\n";

	for (auto & person : report->Persons())
		PrintReportInfoForPersonToConsole(*report, *person);

	for (auto transaction : transactions)
		std::cout << transaction << std::endl;
}

void PrintReportInfoForPersonToHtml(std::ostream& out, const Report& report, const Person& person)
{
	auto reportInfo = report.GetReportInfoForPerson(person.Name());
	if (reportInfo != nullptr)
	{
		if (reportInfo->Payments.size() != 0)
		{
			out << "<h5>" << person.Name() << " paid for: </h5>\n";

			out << "<div class=\"table_div\">\n<table class=\"table_style\">\n<tbody>\n<tr>\n";
			out << "<td>Name</td>\n";
			out << "<td>Amount</td>\n";
			out << "</tr>\n";

			float total = 0.0f;
			for (auto payment : reportInfo->Payments)
			{
				total += payment.Amount;

				out << "<tr>\n";
				out << "<td>" << payment.Name << "</td>\n";
				out << "<td class=\"ra\">$" << payment.Amount << "</td>\n";
				out << "</tr>\n";
			}

			out << "</tbody>\n</table>\n</div><br>\n";
			out << "<h5>Total: &nbsp;&nbsp;&nbsp;&nbsp;$" << total << "</h5>\n";
		}

		if (reportInfo->Expenses.size() != 0)
		{
			out << "<h5>" << person.Name() << " had the following expenses: </h5>\n";

			out << "<div class=\"table_div\">\n<table class=\"table_style\">\n<tbody>\n<tr>\n";
			out << "<td>Name</td>\n";
			out << "<td>Share</td>\n";
			out << "<td>Item Cost</td>\n";
			out << "<td>Amount</td>\n";
			out << "</tr>\n";

			float total = 0.0f;
			for (auto expense : reportInfo->Expenses)
			{
				total += expense.Weight * expense.Amount;

				out << "<tr>\n";
				out << "<td>" << expense.Name << "</td>\n";
				out << "<td>" << expense.Weight << "</td>\n";
				out << "<td class=\"ra\">$" << expense.Amount << "</td>\n";
				out << "<td class=\"ra\">$" << expense.Weight * expense.Amount << "</td>\n";
				out << "</tr>\n";
			}

			out << "</tbody>\n</table>\n</div><br>\n";
			out << "<h5>Total: &nbsp;&nbsp;&nbsp;&nbsp;$" << total << "</h5>\n";
		}
	}
}

void PrintToHtml(std::ostream& out, Report* report)
{
	auto transactions = report->CalculateTransactions();

	out << std::setiosflags(std::ios::fixed) << std::setprecision(2);
	out << "<html>\n<head>\n<title>" << report->Name() << "</title>\n</head>\n";
	out << "<style>\n";

	out << "#content\n{\n";
	out << "font-family: Helvetica, Arial, sans-serif;\n";
	out << "font-size: 12pt;";
	out << "line-height: 150%;";
	out << "text-align: center;";
	out << "margin: 32px auto;";
	out << "overflow: auto;\n}\n";

	out << ".table_style\n{\n";
	out << "border-collapse: collapse;\n";
	out << "border: 2px solid gray;";
	out << "font-size: 11pt;\n}\n";

	out << ".table_div\n{\n";
	out << "display: inline-block;\n}\n";

	out << ".ra\n{\n";
	out << "text-align: right;\n}\n";

	out << "td\n{\n";
	out << "border: 1px solid gray;\n";
	out << "padding: 4px;\n}\n";

	out << "</style>\n";
	out << "<body>\n";
	out << "<div id=\"content\">\n";

	for (auto & person : report->Persons())
		PrintReportInfoForPersonToHtml(out, *report, *person);

	for (auto transaction : transactions)
		out << "<h4>" << transaction << "</h4>\n";

	out << "</div>\n ";
	out << "</body>\n</html>\n";
	out.flush();
}

}

int main(int argc, char** argv)
{
	std::vector<std::string> arguments;
	for (int i = 1; i < argc; i++)
		arguments.emplace_back(argv[i]);

	if (arguments.size() == 0 || arguments.size() > 2)
	{
		std::cerr << "Invalid number of parameters.\nUsage:\tdivida-console <input-xml-file> [output-html-file]" << std::endl;
		return -1;
	}

	std::string inputXmlFile = arguments[0];
	std::string outputXmlFile;
	if (arguments.size() == 2)
		outputXmlFile = arguments[1];

	try
	{
		auto report = LoadReport(inputXmlFile);
		if (outputXmlFile.empty())
		{
			PrintToConsole(report.get());
		}
		else
		{
			std::ofstream outputFile(outputXmlFile);
			PrintToHtml(outputFile, report.get());
		}
	}
	catch (Exception& e)
	{
		std::cerr << "Failed to load " << inputXmlFile << "; error: " << e.GetMessage() << std::endl;
		return -1;
	}
}

void CostcoTest()
{
	Report report("Sharing the Foods : July - August 2013");

	auto Legolas = std::string("Legolas");
	auto Aragorn = std::string("Aragorn");
	auto Galadriel = std::string("Galadrie");
	auto Arwen = std::string("Arwen");

	report.AddPerson(Legolas);
	report.AddPerson(Aragorn);
	report.AddPerson(Galadriel);
	report.AddPerson(Arwen);

	std::vector<std::shared_ptr<Beneficiary>> beneficiariesAll;
	beneficiariesAll.push_back(std::make_shared<Beneficiary>(report.GetPerson(Legolas)));
	beneficiariesAll.push_back(std::make_shared<Beneficiary>(report.GetPerson(Aragorn)));
	beneficiariesAll.push_back(std::make_shared<Beneficiary>(report.GetPerson(Galadriel)));
	beneficiariesAll.push_back(std::make_shared<Beneficiary>(report.GetPerson(Arwen)));

	std::vector<std::shared_ptr<Beneficiary>> beneficiariesDollhouse;
	beneficiariesDollhouse.push_back(std::make_shared<Beneficiary>(report.GetPerson(Galadriel)));
	beneficiariesDollhouse.push_back(std::make_shared<Beneficiary>(report.GetPerson(Arwen)));

	std::vector<std::shared_ptr<Beneficiary>> beneficiariesCairParavel;
	beneficiariesCairParavel.push_back(std::make_shared<Beneficiary>(report.GetPerson(Legolas)));
	beneficiariesCairParavel.push_back(std::make_shared<Beneficiary>(report.GetPerson(Aragorn)));

	std::vector<std::shared_ptr<Beneficiary>> beneficiariesRachel;
	beneficiariesRachel.push_back(std::make_shared<Beneficiary>(report.GetPerson(Galadriel)));

	std::vector<std::shared_ptr<Beneficiary>> beneficiariesVanessa;
	beneficiariesVanessa.push_back(std::make_shared<Beneficiary>(report.GetPerson(Arwen)));

	std::vector<std::shared_ptr<Beneficiary>> beneficiariesChris;
	beneficiariesChris.push_back(std::make_shared<Beneficiary>(report.GetPerson(Aragorn)));

	{
		auto expense = report.NewExpense("Costco", Date::Create(2, 7, 2013), report.GetPerson(Aragorn));

		expense->AddItem("Dentyne Ice Variety Pack", 7.99f, beneficiariesRachel);
		expense->AddItem("Stamps", 45.75f, beneficiariesRachel);
	}

	{
		auto expense = report.NewExpense("Costco", Date::Create(10, 7, 2013), report.GetPerson(Aragorn));

		std::vector<std::pair<std::string, float>> itemsAll;
		itemsAll.push_back(std::make_pair(std::string("Chicken Breasts"), 21.99f));
		itemsAll.push_back(std::make_pair(std::string("Salmon"), 25.49f));
		itemsAll.push_back(std::make_pair(std::string("Sausages (Smoked Mozzarella, Artichoke)"), 12.59f));
		itemsAll.push_back(std::make_pair(std::string("Shredded Parmesan"), 13.99f));
		itemsAll.push_back(std::make_pair(std::string("Kale Salad"), 4.79f));
		itemsAll.push_back(std::make_pair(std::string("Tortellini"), 9.39f));
		itemsAll.push_back(std::make_pair(std::string("Tax"), 5.17f));
		expense->AddItems(itemsAll, beneficiariesAll);

		std::vector<std::pair<std::string, float>> itemsCairParavel;
		itemsCairParavel.push_back(std::make_pair(std::string("Dishwasher Ge"), 11.99f));
		itemsCairParavel.push_back(std::make_pair(std::string("2% Milk"), 5.15f));
		expense->AddItems(itemsCairParavel, beneficiariesCairParavel);

		std::vector<std::pair<std::string, float>> itemsDollhouse;
		itemsDollhouse.push_back(std::make_pair(std::string("Dishwasher Soap Packs"), 10.99f));
		itemsDollhouse.push_back(std::make_pair(std::string("Paper Towels"), 14.99f));
		itemsDollhouse.push_back(std::make_pair(std::string("Curry Powder"), 5.49f));
		itemsDollhouse.push_back(std::make_pair(std::string("Red Pepper Flakes"), 3.25f));
		itemsDollhouse.push_back(std::make_pair(std::string("Quinoa"), 9.99f));
		itemsDollhouse.push_back(std::make_pair(std::string("Italian Seasoning"), 2.69f));
		expense->AddItems(itemsDollhouse, beneficiariesDollhouse);

		expense->AddItem(std::string("Fish Oi"), 9.49f, beneficiariesVanessa);
		expense->AddItem(std::string("Laundry Detergent"), 11.99f, beneficiariesVanessa);

		expense->AddItem(std::string("Frozen Burritos"), 14.49f, beneficiariesChris);
	}

	{
		auto expense = report.NewExpense("Haggen", Date::Create(16, 7, 2013), report.GetPerson(Aragorn));

		expense->AddItem(std::string("Artisan Loaf Bread"), 4.29f, beneficiariesAll);
		expense->AddItem(std::string("Romaine Lettuce"), 1.49f, beneficiariesAll);
		expense->AddItem(std::string("Lemon Juice"), 2.29f, beneficiariesAll);
		expense->AddItem(std::string("Feta Cheese"), 5.99f, beneficiariesAll);
		expense->AddItem(std::string("Cucumber"), 0.69f, beneficiariesAll);
		expense->AddItem(std::string("Onions"), 0.53f, beneficiariesAll);
		expense->AddItem(std::string("Olives"), 1.25f, beneficiariesAll);
		expense->AddItem(std::string("Red Bell Pepper"), 1.50f, beneficiariesAll);
		expense->AddItem(std::string("Green Bell Pepper"), 0.69f, beneficiariesAll);
		expense->AddItem(std::string("Tomatoes"), 4.47f, beneficiariesAll);
	}

	{
		auto expense = report.NewExpense("Haggen", Date::Create(28, 7, 2013), report.GetPerson(Arwen));

		expense->AddItem(std::string("Honeydew Melon"), 4.11f, beneficiariesAll);
		expense->AddItem(std::string("French Take-n-Bake Bread"), 2.99f, beneficiariesAll);
		expense->AddItem(std::string("Brie"), 5.85f, beneficiariesAll);
	}

	{
		auto expense = report.NewExpense("Cost Cutter", Date::Create(28, 7, 2013), report.GetPerson(Aragorn));

		expense->AddItem(std::string("Whipped Cream"), 2.79f, beneficiariesAll);
	}

	{
		auto expense = report.NewExpense("Fred Meyer", Date::Create(29, 7, 2013), report.GetPerson(Arwen));

		expense->AddItem(std::string("Cabbage"), 1.06f, beneficiariesAll);
		expense->AddItem(std::string("Carrots"), 0.50f, beneficiariesAll);
		expense->AddItem(std::string("Limes"), 1.17f, beneficiariesAll);
		expense->AddItem(std::string("Green Beans"), 1.13f, beneficiariesAll);
	}

	{
		auto expense = report.NewExpense("Haggen", Date::Create(30, 7, 2013), report.GetPerson(Aragorn));

		expense->AddItem(std::string("Bourbon Steak Sauce"), 4.49f, beneficiariesAll);
		expense->AddItem(std::string("Mozzarella Cheese"), 2.50f, beneficiariesAll);
		expense->AddItem(std::string("Green Bell Peppers"), 1.58f, beneficiariesAll);
		expense->AddItem(std::string("Sweet Onions"), 1.15f, beneficiariesAll);
	}

	auto transactions = report.CalculateTransactions();
	{
		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);

		std::cout << report.Name() << "\n\n";

		PrintReportInfoForPersonToConsole(report, Legolas);
		PrintReportInfoForPersonToConsole(report, Aragorn);
		PrintReportInfoForPersonToConsole(report, Galadriel);
		PrintReportInfoForPersonToConsole(report, Arwen);

		for (auto transaction : transactions)
			std::cout << transaction << std::endl;
	}
}
