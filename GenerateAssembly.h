#ifndef GENERATE_ASSEMBLY_H
#define GENERATE_ASSEMBLY_H

#include <functional>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "BrainfuckConstants.h"
#include "AssemblyInstructions.h"

namespace bf {

    class GenerateAssembly {

        public:
            GenerateAssembly(std::vector<unsigned char>& instructions);
            ~GenerateAssembly();

            void createAssembly();
            void dumpAssembly(const char* fileName);

        private:
            // Variables
            const std::vector<unsigned char>&  m_InstructionVectorRef;
            std::vector<std::string>           m_GeneratedAssembly;
            bf::AssemblyInstructions           m_AsmInstructions;

            // Brutal hashmap
            std::unordered_map<unsigned char, std::function<std::string()>> m_HashedFunctions;

        private:
            // Functions
            void  m_InitBrutalHashMap();
    };
}
#endif // !GENERATE_ASSEMBLY_H