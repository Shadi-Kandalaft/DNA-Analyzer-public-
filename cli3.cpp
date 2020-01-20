//
// Created by shadikanda on 10/19/19.
//

#include "cli3.h"

#include <sstream>
#include <map>

using std::string;

typedef void (NewCommand::*cmd_method)();
typedef std::map<string, cmd_method > command_map;

typedef std::vector<string> VectorS;
VectorS parse_line(const string& s);

bool CommandFactory::isSetup = false;


CommandsMap CommandFactory::creators;
bool Run::m_quit = false;

void Run::setup(VectorS str_vector, DataBase& db){
    m_cmd = "cmd >>> ";
    m_db = db;
    CommandFactory::setup();
}

void Run::execute() {
    CommandFactory::setup();
    CommandFactory factory;

    while (!m_quit){
        std::cout << m_cmd;
        string line;
        std::getline(std::cin, line);

        while(line.empty())
            std::getline(std::cin, line);

        VectorS string_vector = parse_line(line);
        string s1 = *string_vector.begin();

        if(!my_strcmp(s1.c_str(), "exit"))  // Temporary quit function.
            break;

        Command* cmd = factory.makeCommand(string_vector[0]);
        cmd->setup(string_vector, m_db);
        cmd->execute();
    }
}

VectorS parse_line(const string& s) {
    VectorS result;
    std::istringstream iss(s);
    std::copy(std::istream_iterator<string>(iss), std::istream_iterator<string>(),
              std::back_inserter(result));
    return result;
}

