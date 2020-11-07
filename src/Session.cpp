#include "../include/Session.h"
#include <iostream>
#include <ifstream>
#include "json.hpp"

using json=nlohmann::json;
using namespace std;

Session::Session(const std::string& path) {
    std::ifstream temp(path);
    json input;
    temp>>input;
    Graph g(input["graph"]);
    std::string c=input["tree"];
    std::vector<std::vector<int>> matrix=input["graph"];
}