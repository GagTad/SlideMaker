#pragma once
#include <vector>
#include <memory>
#include "Command.h"
#include "Presentation.h"

class Executor {
public:
    Executor(Presentation& presentation);
    void execute(std::unique_ptr<Command> command);
    void undo();
    void redo();

private:
    Presentation& m_presentation;
    std::vector<std::unique_ptr<Command>> m_undoStack;
    std::vector<std::unique_ptr<Command>> m_redoStack;
};
