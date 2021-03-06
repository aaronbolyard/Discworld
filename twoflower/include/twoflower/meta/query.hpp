// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_META_QUERY_HPP
#define TWOFLOWER_META_QUERY_HPP

#include <unordered_map>
#include "twoflower/meta/recordDefinition.hpp"
#include "twoflower/meta/recordValue.hpp"

namespace twoflower
{
	class Query
	{
	public:
		// The RecordDefinition must not have a shorter lifespan than the
		// Record.
		explicit Query(const RecordDefinition& definition);

		bool get(const std::string& column, RecordValue& result) const;
		bool get(std::size_t index, RecordValue& result) const;

		template <typename T>
		bool get(const std::string& column, T& result) const;

		template <typename T>
		bool get(std::size_t index, T& result) const;

		bool set(const std::string& column, const RecordValue& value);
		bool set(std::size_t index, const RecordValue& value);

		template <typename T>
		bool set(const std::string& column, const T& result);

		template <typename T>
		bool set(std::size_t index, const T& result);

		bool unset(const std::string& column);
		bool unset(std::size_t index);

		bool empty() const;

		typedef std::unordered_map<
			std::size_t,
			RecordValue>::const_iterator const_iterator;
		const_iterator begin() const;
		const_iterator end() const;

	private:
		const RecordDefinition* definition;
		std::unordered_map<std::size_t, RecordValue> values;
	};
}

template <typename T>
bool twoflower::Query::get(const std::string& column, T& result) const
{
	RecordValue value;
	if (get(column, value))
	{
		return value.get(result);
	}

	return false;
}

template <typename T>
bool twoflower::Query::get(std::size_t index, T& result) const
{
	RecordValue value;
	if (get(index, value))
	{
		return value.get(result);
	}

	return false;
}

template <typename T>
bool twoflower::Query::set(const std::string& column, const T& value)
{
	RecordValue v;
	v.set(value);

	return set(column, v);
}

template <typename T>
bool twoflower::Query::set(std::size_t index, const T& value)
{
	RecordValue v;
	v.set(value);

	return set(index, v);
}

#endif
