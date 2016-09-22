#include "group.h"

#include <algorithm>

namespace divida
{
	group::group(const std::string& name)
		: m_name(name)
	{
	}

	std::shared_ptr<divida::person> group::person(size_t id) const
	{
		return m_persons.at(id);
	}

	std::shared_ptr<divida::person> group::person(const std::string& name)
	{
		auto findIter = std::find_if(std::begin(m_persons), std::end(m_persons), [&name](const std::shared_ptr<divida::person>& p) {	return p->name() == name; });
		if (findIter != std::end(m_persons))
			return *findIter;
		
		m_persons.emplace_back(new divida::person(m_persons.size(), name));
		return m_persons.back();
	}
	
	std::shared_ptr<divida::report> group::report(const std::string& name)
	{
		auto findIter = std::find_if(std::begin(m_reports), std::end(m_reports), [&name](const std::shared_ptr<divida::report>& r) {	return r->name() == name; });
		if (findIter != std::end(m_reports))
			return *findIter;

		m_reports.emplace_back(new divida::report(name));
		return m_reports.back();
	}

	const std::vector<std::shared_ptr<divida::person>>& group::persons() const
	{
		return m_persons;
	}

	const std::vector<std::shared_ptr<divida::report>>& group::reports() const
	{
		return m_reports;
	}

	const std::string& group::name() const
	{
		return m_name;
	}

	void group::set_name(const std::string& name)
	{
		m_name = name;
	}
}
