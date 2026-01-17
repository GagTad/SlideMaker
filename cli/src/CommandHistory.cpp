#include "CommandHistory.h"
#include "Presentation.h"


void CommandHistory::push(std::unique_ptr<Command> command) {
    m_undoStack.push_back(std::move(command));
    m_redoStack.clear();
}

bool CommandHistory::canUndo() const {
    return !m_undoStack.empty();
}

bool CommandHistory::canRedo() const {
    return !m_redoStack.empty();
}

void CommandHistory::undo(Presentation& presentation) {
    if (!canUndo()) return;
    auto command = std::move(m_undoStack.back());
    m_undoStack.pop_back();
    command->undo(presentation);
    m_redoStack.push_back(std::move(command));
}

void CommandHistory::redo(Presentation& presentation) {
    if (!canRedo()) return;
    auto command = std::move(m_redoStack.back());
    m_redoStack.pop_back();
    command->execute(presentation);
    m_undoStack.push_back(std::move(command));
}