#pragma once

#include <memory>
#include "Command.h"
#include "Presentation.h"

class Executor {
public: 
    Executor(Presentation& presentation);
    void execute(const std::unique_ptr<Command>& command);

private:
    Presentation& m_presentation;
 
    void executeCreateSlide(const CreateSlideCommand* cmd);
    void executeSelectSlide(const SelectSlideCommand* cmd);
    void executeListSlides(const ListSlidesCommand* cmd);
    void executeAddShape(const AddShapeCommand* cmd);
    void executeExport(const ExportCommand* cmd);
};

