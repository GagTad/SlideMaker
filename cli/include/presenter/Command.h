#pragma once
#include <string>
#include <vector>
#include <map>
#include "Presentation.h"

struct Command {
    virtual ~Command() = default;
    virtual void execute(Presentation& presentation) = 0;

    // Undo ֆունկցիոնալ
    virtual void undo(Presentation& presentation) {}
    virtual bool isUndoable() const { return false; }
};

struct CreateSlideCommand : public Command {
    std::string slideName;
    void execute(Presentation& presentation) override;
    void undo(Presentation& presentation) override;
    bool isUndoable() const override { return true; }
};

struct SelectSlideCommand : public Command {
    int slideId;
    int previousId = -1; // State to restore
    void execute(Presentation& presentation) override;
    void undo(Presentation& presentation) override;
    bool isUndoable() const override { return true; }
};

struct AddShapeCommand : public Command {
    std::string shapeType;
    std::vector<int> params;
    std::map<std::string, std::string> flags;
    void execute(Presentation& presentation) override;
    void undo(Presentation& presentation) override;
    bool isUndoable() const override { return true; }
};

// Non-undoable commands
struct ExportCommand : public Command {
    std::string filename;
    void execute(Presentation& presentation) override;
};

struct ExportSlideshowCommand : public Command {
    std::string filename;
    void execute(Presentation& presentation) override;
};

struct ListSlidesCommand : public Command {
    void execute(Presentation& presentation) override;
};

struct SaveCommand : public Command {
    std::string filename;
    void execute(Presentation& presentation) override;
};

// Special Commands for Parser
struct UndoCommand : public Command {
    void execute(Presentation&) override {}
};
struct RedoCommand : public Command {
    void execute(Presentation&) override {}
};
