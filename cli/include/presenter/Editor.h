#pragma once
#include <string>
#include "Presentation.h"
#include "Executor.h"

class Editor {
public:
    Editor();
    void run(const std::string& inputFilePath);
    void runInteractive();

private:
    Presentation m_presentation;
    Executor m_executor;
    void processLine(const std::string& line);
};