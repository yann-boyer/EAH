#include "Interpreter.hpp"
#include "Instructions.hpp"
#include <fstream>

Interpreter::Interpreter() {
	m_program.resize(0x0);
	m_pc = 0;
	m_ptr = 0;
}

void Interpreter::LoadProgramFromFile(const std::string& programPath) {
	std::ifstream programFile(programPath);

	if (!programFile.is_open())
		throw std::runtime_error("[Error] Unable to open the Brainfuck file !");
	
	std::vector<char> programBuffer;

	char character;
	while (programFile.good()) {
		programFile.get(character);
		programBuffer.push_back(character);
	}

	programFile.close();

	for (char pInstr : programBuffer) {
		switch (pInstr) {
			case '>': m_program.push_back(Instructions::IncrPtr); break;
			case '<': m_program.push_back(Instructions::DecrPtr); break;
			case '+': m_program.push_back(Instructions::IncrByte); break;
			case '-': m_program.push_back(Instructions::DecrByte); break;
			case '.': m_program.push_back(Instructions::ByteOut); break;
			case ',': m_program.push_back(Instructions::ByteIn); break;
			case '[': m_program.push_back(Instructions::JmpFwd); break;
			case ']': m_program.push_back(Instructions::JmpBckwd); break;
			default: break;
		}
	}
}

void Interpreter::PrecomputeJumps() {
	std::vector<uint64_t> stack;

	uint64_t pc = 0;
	uint64_t target;

	while (pc < m_program.size()) {
		Instructions instr = m_program[pc];

		switch (instr) {
			case Instructions::JmpFwd: stack.push_back(pc); break;
			case Instructions::JmpBckwd:
				target = stack.back();
				stack.pop_back();
				m_jumpMap[target] = pc;
				m_jumpMap[pc] = target;
				break;
			default: break;
		}

		pc++;
	}
}

void Interpreter::Interpret() {
	PrecomputeJumps();

	while (m_pc < m_program.size()) {
		Instructions instr = m_program[m_pc];

		switch (instr) {
			case Instructions::IncrPtr:
				if (!(m_memory.count(m_ptr) > 0))
					m_memory[m_ptr] = 0;
				m_ptr++;
				break;
			case Instructions::DecrPtr:
				m_ptr--;
				break;
			case Instructions::IncrByte:
				m_memory[m_ptr]++;
				break;
			case Instructions::DecrByte:
				m_memory[m_ptr]--;
				break;
			case Instructions::ByteOut:
				{
					char byteToOutput = static_cast<char>(m_memory[m_ptr]);
					std::cout << byteToOutput;
					std::cout.flush();
				}
				break;
			case Instructions::ByteIn:
				{
					char byteInput;
					std::cin >> byteInput;
					std::cin.clear();
					m_memory[m_ptr] = static_cast<uint8_t>(byteInput);
				}
			case Instructions::JmpFwd:
				if (m_memory[m_ptr] == 0)
					m_pc = m_jumpMap[m_pc];
				break;
			case Instructions::JmpBckwd:
				if (m_memory[m_ptr] != 0)
					m_pc = m_jumpMap[m_pc];
				break;
		}

		m_pc++;
	}
}
