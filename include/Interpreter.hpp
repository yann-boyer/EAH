#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <map>
#include <vector>
#include <cstdint>
#include <iostream>
#include "Instructions.hpp"

class Interpreter {
	public:
		Interpreter();

		void LoadProgramFromFile(const std::string& programPath);
		void Interpret();
	private:
		void PrecomputeJumps();

		std::vector<Instructions> m_program;
		std::map<uint64_t, uint8_t> m_memory;
		std::map<uint64_t, uint64_t> m_jumpMap;

		uint64_t m_pc;
		uint64_t m_ptr;
};

#endif