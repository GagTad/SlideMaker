#include "Executor.h"
#include <iostream>

Executor::Executor(Presentation& presentation) : m_presentation(presentation) {}

void Executor::execute(std::unique_ptr<Command> command) {
    if (!command) return;
    
    if (dynamic_cast<UndoCommand*>(command.get())) {
        undo();
        return;
    }
    if (dynamic_cast<RedoCommand*>(command.get())) {
        redo();
        return;
    }

    command->execute(m_presentation);

    if (command->isUndoable()) {
        m_undoStack.push_back(std::move(command));
        m_redoStack.clear();
    }
}

void Executor::undo() {
    if (m_undoStack.empty()) {
        std::cout << "[INFO] Nothing to undo." << std::endl;
        return;
    }

    std::unique_ptr<Command> cmd = std::move(m_undoStack.back());
    m_undoStack.pop_back();

    std::cout << "[UNDO] ";
    cmd->undo(m_presentation);

    m_redoStack.push_back(std::move(cmd));
}

void Executor::redo() {
    if (m_redoStack.empty()) {
        std::cout << "[INFO] Nothing to redo." << std::endl;
        return;
    }
    std::unique_ptr<Command> cmd = std::move(m_redoStack.back());
    m_redoStack.pop_back();
    std::cout << "[REDO] ";
    cmd->execute(m_presentation);
    m_undoStack.push_back(std::move(cmd));
}
