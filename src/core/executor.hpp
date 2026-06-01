#pragma once
#include <string>
#include <vector>

bool execute_command(
    std::string cmd,
    bool background,
    std::vector<std::string> &history);