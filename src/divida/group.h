#pragma once

#include "person.h"
#include "report.h"

#include <memory>
#include <string>
#include <vector>

namespace divida
{
	class group
	{
	public:
		explicit group(const std::string& name);
		
		std::shared_ptr<divida::person> person(size_t id) const;
		std::shared_ptr<divida::person> person(const std::string& name);
		std::shared_ptr<divida::report> report(const std::string& name);
		const std::vector<std::shared_ptr<divida::person>>& persons() const;
		const std::vector<std::shared_ptr<divida::report>>& reports() const;

		const std::string& name() const;
		void set_name(const std::string& name);

	private:
		std::vector<std::shared_ptr<divida::person>> m_persons;
		std::vector<std::shared_ptr<divida::report>> m_reports;
		std::string m_name;
	};
}
