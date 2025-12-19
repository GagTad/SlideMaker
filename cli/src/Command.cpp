#include "Command.h"
#include "ShapeFactory.h"
#include "Serializer.h"
#include <iostream>

//CreateSlide
void CreateSlideCommand::execute(Presentation& presentation) {
    presentation.createSlide(slideName);
}
void CreateSlideCommand::undo(Presentation& presentation) {
    presentation.removeLastSlide();
}

//SelectSlide 
void SelectSlideCommand::execute(Presentation& presentation) {
    previousId = presentation.getActiveSlideId(); 
    presentation.setActiveSlideId(slideId);
}
void SelectSlideCommand::undo(Presentation& presentation) {
    presentation.setActiveSlideId(previousId); 
}

//AddShape
void AddShapeCommand::execute(Presentation& presentation) {
    auto shape = ShapeRegistry::getInstance().createShape(shapeType, params);
    shape->flags = flags;
    presentation.addShapeToActiveSlide(std::move(shape));
    std::cout << "Added " << shapeType << "." << std::endl;
}
void AddShapeCommand::undo(Presentation& presentation) {
    presentation.removeLastShapeFromActiveSlide();
}

//Others (No Undo)
void ListSlidesCommand::execute(Presentation& presentation) {
    presentation.listSlides();
}

void ExportCommand::execute(Presentation& presentation) {
    const Slide* activeSlide = presentation.getActiveSlide();
    if (!activeSlide) throw std::runtime_error("No active slide to export.");
    Serializer::exportSlideToSvg(activeSlide, filename);
    std::cout << "Exported to " << filename << std::endl;
}

void ExportSlideshowCommand::execute(Presentation& presentation) {
    if (presentation.getSlides().empty()) throw std::runtime_error("No slides to export.");
    Serializer::exportToHtml(presentation, filename);
}

void SaveCommand::execute(Presentation& presentation) {
    Serializer::savePresentation(presentation, filename);
    std::cout << "Presentation saved to " << filename << std::endl;
}