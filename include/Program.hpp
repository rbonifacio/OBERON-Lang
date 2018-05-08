#ifndef PROGRAM_H
#define PROGRAM_H

#include "Command.hpp"

class Program : Command {
public:
  Program(Command* main) { this->mains = main; }
  void run();
private:
  Command* main; 
}


#endif 
