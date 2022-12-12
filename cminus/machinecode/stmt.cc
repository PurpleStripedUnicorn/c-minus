
#include "stmt.h"
#include "stmtstr.h"

std::string MCOperand::str(DataSize size) const {
    return mcOperandString(*this, size);
}

std::string MCStatement::str() const {
    return mcStatementString(*this);
}