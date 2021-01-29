#pragma once
#include <string>

namespace deq {
	namespace typing {

		enum Type {
			UNKNOWN,

			INT8,
			INT16,
			INT32,
			INT64,

			UINT8,
			UINT16,
			UINT32,
			UINT64,

			BYTE,
			STRING,

			FLOAT,
			DOUBLE,

			BOOL
		};

		std::string toString(Type type);
		Type fromString(std::string type);

		bool isValidType(Type type);
		bool isValidType(std::string type);

	}
}