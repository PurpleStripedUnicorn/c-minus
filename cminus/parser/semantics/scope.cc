
#include "scope.h"

ScopeManager::ScopeManager() { }

ScopeManager::~ScopeManager() { }

void ScopeManager::pushScope() {
    scopeStack.push_back({});
}

void ScopeManager::popScope() {
    if (scopeStack.size() > 0)
        scopeStack.pop_back();
}

long long ScopeManager::find(std::string name, bool fullDepth) const {
    size_t count = scopeStack.size();
    if (!fullDepth)
        count = 1;
    for (size_t i = 0; i < count; i++) {
        const auto &vmap = scopeStack[scopeStack.size() - i - 1];
        auto res = vmap.find(name);
        if (res != vmap.end())
            return res->second;
    }
    return -1;
}

void ScopeManager::push(std::string name, long long tacName) {
    scopeStack.back()[name] = tacName;
}