#pragma once
#include <vector>
#include <memory>
#include "Command.h"
#include "Presentation.h"

class CommandHistory {
public:
    void push(std::unique_ptr<Command> command);
    bool canUndo() const;
    bool canRedo() const;
    void undo(Presentation& presentation);
    void redo(Presentation& presentation);

private:
    std::vector<std::unique_ptr<Command>> m_undoStack;
    std::vector<std::unique_ptr<Command>> m_redoStack;
};