#include <fstream>
#include <iostream>
#include <iomanip>

#if 0
using namespace divida;

void CostcoTest();

namespace
{

std::unique_ptr<report> LoadReport(const std::string& path)
{
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(path.c_str());
	if (!result)
		throw exception{ result.description() };

	auto report = report_xml_serializer::read(document.child("report"));
	return std::move(report);
}

void PrintReportInfoForPersonToConsole(const report& report, const person& person)
{
	auto reportInfo = report.get_report_info_for_person(person.name());
	if (reportInfo != nullptr)
	{
		if (reportInfo->payments.size() != 0)
		{
			std::cout << person.name() << " paid for:" << std::endl;
			std::cout << std::setw(32) << std::left << "name" << std::setw(6) << "amount" << std::endl;
			std::cout << std::setw(32) << std::left << "----" << std::setw(6) << "------" << std::endl;

			float total = 0.0f;
			for (auto payment : reportInfo->payments)
			{
				total += payment.amount;
				std::cout << std::setw(32) << std::left << payment.name << std::setw(6) << std::right << payment.amount << std::endl;
			}

			std::cout << std::endl;
			std::cout << std::setw(32) << std::left << "total" << std::setw(6) << std::right << total << std::endl;

			std::cout << std::endl;
		}

		if (reportInfo->expenses.size() != 0)
		{
			unsigned int namePrintWidth = report.get_item_name_print_width();

			std::cout << person.name() << " had the following expenses: " << std::endl;

			std::cout << std::setw(namePrintWidth) << std::left << "name";
			std::cout << std::setw(5) << "Share" << std::setw(5) << "  x  " << std::setw(9) << "item cost";
			std::cout << std::setw(5) << "  =  " << std::setw(6) << "amount" << std::endl;

			std::cout << std::setw(namePrintWidth) << std::left << "----";
			std::cout << std::setw(5) << "-----" << std::setw(5) << " " << std::setw(9) << "---------";
			std::cout << std::setw(5) << " " << std::setw(6) << "------" << std::endl;

			float total = 0.0f;
			for (auto expense : reportInfo->expenses)
			{
				total += expense.weight * expense.amount;

				std::cout << std::setw(namePrintWidth) << std::left << expense.name;
				std::cout << std::setw(5) << std::right << expense.weight << std::setw(5) << "  x  " << std::setw(9) << expense.amount;
				std::cout << std::setw(5) << "  =  " << std::setw(6) << expense.weight * expense.amount << std::endl;
			}

			std::cout << std::endl;
			std::cout << std::setw(namePrintWidth) << std::left << "total" << std::setw(30) << std::right << total << std::endl;

			std::wcerr << std::endl;
		}

		std::cout << std::endl;
	}
}

void PrintToConsole(report* report)
{
	auto transactions = report->calculate_transactions();

	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
	std::cout << report->name() << "\n\n";

	for (auto & person : report->persons())
		PrintReportInfoForPersonToConsole(*report, *person);

	for (auto transaction : transactions)
		std::cout << transaction << std::endl;
}

void PrintReportInfoForPersonToHtml(std::ostream& out, const report& report, const person& person)
{
	auto reportInfo = report.get_report_info_for_person(person.name());
	if (reportInfo != nullptr)
	{
		if (reportInfo->payments.size() != 0)
		{
			out << "<h5>" << person.name() << " paid for: </h5>\n";

			out << "<div class=\"table_div\">\n<table class=\"table_style\">\n<tbody>\n<tr>\n";
			out << "<td>name</td>\n";
			out << "<td>amount</td>\n";
			out << "</tr>\n";

			float total = 0.0f;
			for (auto payment : reportInfo->payments)
			{
				total += payment.amount;

				out << "<tr>\n";
				out << "<td>" << payment.name << "</td>\n";
				out << "<td class=\"ra\">$" << payment.amount << "</td>\n";
				out << "</tr>\n";
			}

			out << "</tbody>\n</table>\n</div><br>\n";
			out << "<h5>total: &nbsp;&nbsp;&nbsp;&nbsp;$" << total << "</h5>\n";
		}

		if (reportInfo->expenses.size() != 0)
		{
			out << "<h5>" << person.name() << " had the following expenses: </h5>\n";

			out << "<div class=\"table_div\">\n<table class=\"table_style\">\n<tbody>\n<tr>\n";
			out << "<td>name</td>\n";
			out << "<td>Share</td>\n";
			out << "<td>item cost</td>\n";
			out << "<td>amount</td>\n";
			out << "</tr>\n";

			float total = 0.0f;
			for (auto expense : reportInfo->expenses)
			{
				total += expense.weight * expense.amount;

				out << "<tr>\n";
				out << "<td>" << expense.name << "</td>\n";
				out << "<td>" << expense.weight << "</td>\n";
				out << "<td class=\"ra\">$" << expense.amount << "</td>\n";
				out << "<td class=\"ra\">$" << expense.weight * expense.amount << "</td>\n";
				out << "</tr>\n";
			}

			out << "</tbody>\n</table>\n</div><br>\n";
			out << "<h5>total: &nbsp;&nbsp;&nbsp;&nbsp;$" << total << "</h5>\n";
		}
	}
}

void PrintToHtml(std::ostream& out, report* report)
{
	auto transactions = report->calculate_transactions();

	out << std::setiosflags(std::ios::fixed) << std::setprecision(2);
	out << "<html>\n<head>\n<title>" << report->name() << "</title>\n</head>\n";
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

	for (auto & person : report->persons())
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
	catch (exception& e)
	{
		std::cerr << "Failed to load " << inputXmlFile << "; error: " << e.message() << std::endl;
		return -1;
	}
}

void CostcoTest()
{
	report report("Sharing the Foods : July - August 2013");

	auto Legolas = std::string("Legolas");
	auto Aragorn = std::string("Aragorn");
	auto Galadriel = std::string("Galadrie");
	auto Arwen = std::string("Arwen");

	report.add_person(Legolas);
	report.add_person(Aragorn);
	report.add_person(Galadriel);
	report.add_person(Arwen);

	std::vector<std::shared_ptr<beneficiary>> beneficiariesAll;
	beneficiariesAll.push_back(std::make_shared<beneficiary>(report.get_person(Legolas)));
	beneficiariesAll.push_back(std::make_shared<beneficiary>(report.get_person(Aragorn)));
	beneficiariesAll.push_back(std::make_shared<beneficiary>(report.get_person(Galadriel)));
	beneficiariesAll.push_back(std::make_shared<beneficiary>(report.get_person(Arwen)));

	std::vector<std::shared_ptr<beneficiary>> beneficiariesDollhouse;
	beneficiariesDollhouse.push_back(std::make_shared<beneficiary>(report.get_person(Galadriel)));
	beneficiariesDollhouse.push_back(std::make_shared<beneficiary>(report.get_person(Arwen)));

	std::vector<std::shared_ptr<beneficiary>> beneficiariesCairParavel;
	beneficiariesCairParavel.push_back(std::make_shared<beneficiary>(report.get_person(Legolas)));
	beneficiariesCairParavel.push_back(std::make_shared<beneficiary>(report.get_person(Aragorn)));

	std::vector<std::shared_ptr<beneficiary>> beneficiariesRachel;
	beneficiariesRachel.push_back(std::make_shared<beneficiary>(report.get_person(Galadriel)));

	std::vector<std::shared_ptr<beneficiary>> beneficiariesVanessa;
	beneficiariesVanessa.push_back(std::make_shared<beneficiary>(report.get_person(Arwen)));

	std::vector<std::shared_ptr<beneficiary>> beneficiariesChris;
	beneficiariesChris.push_back(std::make_shared<beneficiary>(report.get_person(Aragorn)));

	{
		auto expense = report.new_expense("Costco", date::create(2, 7, 2013), report.get_person(Aragorn));

		expense->add_item("Dentyne Ice Variety Pack", 7.99f, beneficiariesRachel);
		expense->add_item("Stamps", 45.75f, beneficiariesRachel);
	}

	{
		auto expense = report.new_expense("Costco", date::create(10, 7, 2013), report.get_person(Aragorn));

		std::vector<std::pair<std::string, float>> itemsAll;
		itemsAll.push_back(std::make_pair(std::string("Chicken Breasts"), 21.99f));
		itemsAll.push_back(std::make_pair(std::string("Salmon"), 25.49f));
		itemsAll.push_back(std::make_pair(std::string("Sausages (Smoked Mozzarella, Artichoke)"), 12.59f));
		itemsAll.push_back(std::make_pair(std::string("Shredded Parmesan"), 13.99f));
		itemsAll.push_back(std::make_pair(std::string("Kale Salad"), 4.79f));
		itemsAll.push_back(std::make_pair(std::string("Tortellini"), 9.39f));
		itemsAll.push_back(std::make_pair(std::string("Tax"), 5.17f));
		expense->add_items(itemsAll, beneficiariesAll);

		std::vector<std::pair<std::string, float>> itemsCairParavel;
		itemsCairParavel.push_back(std::make_pair(std::string("Dishwasher Ge"), 11.99f));
		itemsCairParavel.push_back(std::make_pair(std::string("2% Milk"), 5.15f));
		expense->add_items(itemsCairParavel, beneficiariesCairParavel);

		std::vector<std::pair<std::string, float>> itemsDollhouse;
		itemsDollhouse.push_back(std::make_pair(std::string("Dishwasher Soap Packs"), 10.99f));
		itemsDollhouse.push_back(std::make_pair(std::string("Paper Towels"), 14.99f));
		itemsDollhouse.push_back(std::make_pair(std::string("Curry Powder"), 5.49f));
		itemsDollhouse.push_back(std::make_pair(std::string("Red Pepper Flakes"), 3.25f));
		itemsDollhouse.push_back(std::make_pair(std::string("Quinoa"), 9.99f));
		itemsDollhouse.push_back(std::make_pair(std::string("Italian Seasoning"), 2.69f));
		expense->add_items(itemsDollhouse, beneficiariesDollhouse);

		expense->add_item(std::string("Fish Oi"), 9.49f, beneficiariesVanessa);
		expense->add_item(std::string("Laundry Detergent"), 11.99f, beneficiariesVanessa);

		expense->add_item(std::string("Frozen Burritos"), 14.49f, beneficiariesChris);
	}

	{
		auto expense = report.new_expense("Haggen", date::create(16, 7, 2013), report.get_person(Aragorn));

		expense->add_item(std::string("Artisan Loaf Bread"), 4.29f, beneficiariesAll);
		expense->add_item(std::string("Romaine Lettuce"), 1.49f, beneficiariesAll);
		expense->add_item(std::string("Lemon Juice"), 2.29f, beneficiariesAll);
		expense->add_item(std::string("Feta Cheese"), 5.99f, beneficiariesAll);
		expense->add_item(std::string("Cucumber"), 0.69f, beneficiariesAll);
		expense->add_item(std::string("Onions"), 0.53f, beneficiariesAll);
		expense->add_item(std::string("Olives"), 1.25f, beneficiariesAll);
		expense->add_item(std::string("Red Bell Pepper"), 1.50f, beneficiariesAll);
		expense->add_item(std::string("Green Bell Pepper"), 0.69f, beneficiariesAll);
		expense->add_item(std::string("Tomatoes"), 4.47f, beneficiariesAll);
	}

	{
		auto expense = report.new_expense("Haggen", date::create(28, 7, 2013), report.get_person(Arwen));

		expense->add_item(std::string("Honeydew Melon"), 4.11f, beneficiariesAll);
		expense->add_item(std::string("French Take-n-Bake Bread"), 2.99f, beneficiariesAll);
		expense->add_item(std::string("Brie"), 5.85f, beneficiariesAll);
	}

	{
		auto expense = report.new_expense("cost Cutter", date::create(28, 7, 2013), report.get_person(Aragorn));

		expense->add_item(std::string("Whipped Cream"), 2.79f, beneficiariesAll);
	}

	{
		auto expense = report.new_expense("Fred Meyer", date::create(29, 7, 2013), report.get_person(Arwen));

		expense->add_item(std::string("Cabbage"), 1.06f, beneficiariesAll);
		expense->add_item(std::string("Carrots"), 0.50f, beneficiariesAll);
		expense->add_item(std::string("Limes"), 1.17f, beneficiariesAll);
		expense->add_item(std::string("Green Beans"), 1.13f, beneficiariesAll);
	}

	{
		auto expense = report.new_expense("Haggen", date::create(30, 7, 2013), report.get_person(Aragorn));

		expense->add_item(std::string("Bourbon Steak Sauce"), 4.49f, beneficiariesAll);
		expense->add_item(std::string("Mozzarella Cheese"), 2.50f, beneficiariesAll);
		expense->add_item(std::string("Green Bell Peppers"), 1.58f, beneficiariesAll);
		expense->add_item(std::string("Sweet Onions"), 1.15f, beneficiariesAll);
	}

	auto transactions = report.calculate_transactions();
	{
		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);

		std::cout << report.name() << "\n\n";

		PrintReportInfoForPersonToConsole(report, Legolas);
		PrintReportInfoForPersonToConsole(report, Aragorn);
		PrintReportInfoForPersonToConsole(report, Galadriel);
		PrintReportInfoForPersonToConsole(report, Arwen);

		for (auto transaction : transactions)
			std::cout << transaction << std::endl;
	}
}
#else
int main()
{
}
#endif
