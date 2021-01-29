#include "typing.hpp"

std::string deq::typing::toString(deq::typing::Type type) {
	switch (type)
	{
	case deq::typing::UNKNOWN:
		return "unknown";
	case deq::typing::INT8:
		return "int8";
	case deq::typing::INT16:
		return "int16";
	case deq::typing::INT32:
		return "int32";
	case deq::typing::INT64:
		return "int64";
	case deq::typing::UINT8:
		return "uint8";
	case deq::typing::UINT16:
		return "uint16";
	case deq::typing::UINT32:
		return "uint32";
	case deq::typing::UINT64:
		return "uint64";
	case deq::typing::BYTE:
		return "byte";
	case deq::typing::STRING:
		return "string";
	case deq::typing::FLOAT:
		return "float";
	case deq::typing::DOUBLE:
		return "double";
	case deq::typing::BOOL:
		return "bool";
	default:
		return "unknown";
	}
}

deq::typing::Type deq::typing::fromString(std::string type) {
	if (type == "int8")
		return Type::INT8;
	else if (type == "int16")
		return Type::INT16;
	else if (type == "int32")
		return Type::INT32;
	else if (type == "int64")
		return Type::INT64;
	else if (type == "uint8")
		return Type::UINT8;
	else if (type == "uint16")
		return Type::UINT16;
	else if (type == "uint32")
		return Type::UINT32;
	else if (type == "uint64")
		return Type::UINT64;
	else if (type == "string")
		return Type::STRING;
	else if (type == "float")
		return Type::FLOAT;
	else if (type == "double")
		return Type::DOUBLE;
	else if (type == "bool")
		return Type::BOOL;
	else
		return Type::UNKNOWN;
}

bool deq::typing::isValidType(Type type) {
	switch (type)
	{
	case deq::typing::INT8:
	case deq::typing::INT16:
	case deq::typing::INT32:
	case deq::typing::INT64:
	case deq::typing::UINT8:
	case deq::typing::UINT16:
	case deq::typing::UINT32:
	case deq::typing::UINT64:
	case deq::typing::BYTE:
	case deq::typing::STRING:
	case deq::typing::FLOAT:
	case deq::typing::DOUBLE:
	case deq::typing::BOOL:
		return true;
	default:
		return false;
	}
}

bool deq::typing::isValidType(std::string type) {
	return isValidType(fromString(type));
}