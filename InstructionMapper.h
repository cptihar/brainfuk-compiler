#ifndef INSTRUCTION_MAPPER_H
#define INSTRUCTION_MAPPER_H

#include <string>

namespace bf {

    class InstructionMapper {
        public:
            InstructionMapper() = default;
            ~InstructionMapper();

            std::string ptrMoveLeft();

    };

}
#endif // !INSTRUCTION_MAPPER_H