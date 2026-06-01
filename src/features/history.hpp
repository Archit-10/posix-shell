#pragma once

#include <vector>
#include <string>

void load_history(std::vector<std::string> &history);
void save_history(const std::vector<std::string> &history);
void display_history(const std::vector<std::string> &history, int num = 20);
void add_command_to_history(std::vector<std::string> &history,
                            const std::string &command);