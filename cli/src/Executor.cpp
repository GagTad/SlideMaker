#include <fstream>
#include <stdexcept>     
#include <iostream>   
#include "ShapeFactory.h"
#include "Executor.h"
#include "Shape.h"   

Executor::Executor(Presentation& presentation) : m_presentation(presentation) {}

void Executor::execute(const std::unique_ptr<Command>& command) {
     
    if (auto* cmd = dynamic_cast<const CreateSlideCommand*>(command.get())) {
        executeCreateSlide(cmd);
    }
    else if (auto* cmd = dynamic_cast<const SelectSlideCommand*>(command.get())) {
        executeSelectSlide(cmd);
    }
    else if (auto* cmd = dynamic_cast<const ListSlidesCommand*>(command.get())) {
        executeListSlides(cmd);
    }
    else if (auto* cmd = dynamic_cast<const AddShapeCommand*>(command.get())) {
       
        executeAddShape(cmd);
    }
    else if (auto* cmd = dynamic_cast<const ExportCommand*>(command.get())) {
        executeExport(cmd);
    }
    else {
        throw std::runtime_error("Execution Error: Unknown command type.");
    }
}

void Executor::executeCreateSlide(const CreateSlideCommand* cmd) {
   
    m_presentation.createSlide(cmd->slideName);
}

void Executor::executeListSlides(const ListSlidesCommand* cmd) {
  
    m_presentation.listSlides();
}

void Executor::executeSelectSlide(const SelectSlideCommand* cmd) {
 
    if (cmd->slideId < 0 || cmd->slideId >= m_presentation.getSlideCount()) {
        throw std::runtime_error("Semantic Error: Slide with ID " + std::to_string(cmd->slideId) + " does not exist.");
    }

    
    m_presentation.setActiveSlideId(cmd->slideId);
    std::cout << "Selected slide " << cmd->slideId << "." << std::endl;
}

 
void Executor::executeAddShape(const AddShapeCommand* cmd) {

    Slide* activeSlide = m_presentation.getActiveSlide();
    if (!activeSlide) {
        throw std::runtime_error("Semantic Error: No slide selected. Use 'select_slide' first.");
    }

    std::unique_ptr<Shape> newShape = ShapeRegistry::getInstance().createShape(cmd->shapeType, cmd->params);
    
    newShape->flags = cmd->flags;
    activeSlide->addShape(std::move(newShape));

    std::cout << "Successfully added '" << cmd->shapeType << "' to slide " << m_presentation.getActiveSlideId() << "." << std::endl;
}

void Executor::executeExport(const ExportCommand* cmd) {
    Slide* activeSlide = m_presentation.getActiveSlide();
    if (!activeSlide) {
        throw std::runtime_error("Semantic Error: No slide selected to export. Use 'select_slide' first.");
    }

    std::ofstream svgFile(cmd->filename);
    if (!svgFile.is_open()) {
        throw std::runtime_error("Execution Error: Could not open file '" + cmd->filename + "' to write.");
    }

    svgFile << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for (const auto& shape_ptr : activeSlide->getShapes()) {
        svgFile << "  " << shape_ptr->toSvg() << "\n";
    }

    svgFile << "</svg>\n";

    svgFile.close();
    std::cout << "Successfully exported slide " << m_presentation.getActiveSlideId()
        << " to '" << cmd->filename << "'" << std::endl;
}
