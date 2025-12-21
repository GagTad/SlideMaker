#include "Command.h"
#include "ShapeFactory.h"
#include "Serializer.h"
#include <iostream> 

void CreateSlideCommand::execute(Presentation& presentation) {
    int newId = presentation.createSlide(slideName);
    presentation.setActiveSlideId(newId);
    std::cout << "Created slide '" << slideName << "' (ID: " << newId << ")." << std::endl;
}

void CreateSlideCommand::undo(Presentation& presentation) {
    presentation.removeLastSlide();
    std::cout << "Undid slide creation." << std::endl;
}

// SelectSlide 
void SelectSlideCommand::execute(Presentation& presentation) {
    previousId = presentation.getActiveSlideId();
    presentation.setActiveSlideId(slideId);
    std::cout << "Selected slide " << slideId << "." << std::endl;
}

void SelectSlideCommand::undo(Presentation& presentation) {
    presentation.setActiveSlideId(previousId);
    std::cout << "Restored selection to " << previousId << "." << std::endl;
}

// AddShape 
void AddShapeCommand::execute(Presentation& presentation) {
    auto shape = ShapeRegistry::getInstance().createShape(shapeType, params);
    shape->flags = flags;
    presentation.addShapeToActiveSlide(std::move(shape));
    std::cout << "Added " << shapeType << "." << std::endl;
}

void AddShapeCommand::undo(Presentation& presentation) {
    presentation.removeShapeFromActiveSlide(presentation.getActiveSlide()->getShapes().size() - 1);
    std::cout << "Undid add shape." << std::endl;
}

// MoveShape
void MoveShapeCommand::execute(Presentation& presentation) {
    auto oldPos = presentation.getShapePosition(shapeIndex);
    oldX = oldPos.first;
    oldY = oldPos.second;
    presentation.moveShape(shapeIndex, newX, newY);
    std::cout << "Moved shape " << shapeIndex << "." << std::endl;
}

void MoveShapeCommand::undo(Presentation& presentation) {
    presentation.moveShape(shapeIndex, oldX, oldY);
    std::cout << "Undid move shape." << std::endl;
}

//RemoveShape
void RemoveShapeCommand::execute(Presentation& presentation) {
    removedShape = presentation.extractShapeFromActiveSlide(shapeIndex);
    if (removedShape) {
        std::cout << "Removed shape at " << shapeIndex << "." << std::endl;
    }
    else {
        std::cout << "Failed to remove shape (invalid index)." << std::endl;
    }
}

void RemoveShapeCommand::undo(Presentation& presentation) {
    if (removedShape) {
        presentation.insertShapeToActiveSlide(shapeIndex, std::move(removedShape));
        std::cout << "Restored shape at " << shapeIndex << "." << std::endl;
    }
}

//ClearSlide
void ClearSlideCommand::execute(Presentation& presentation) {
    removedShapes = presentation.extractAllShapesFromActiveSlide();
    std::cout << "Cleared slide (removed " << removedShapes.size() << " shapes)." << std::endl;
}

void ClearSlideCommand::undo(Presentation& presentation) {
    presentation.restoreShapesToActiveSlide(std::move(removedShapes));
    std::cout << "Restored slide content." << std::endl;
}

//DuplicateSlide
void DuplicateSlideCommand::execute(Presentation& presentation) {
    presentation.duplicateSlide(slideId);
    std::cout << "Duplicated slide " << slideId << "." << std::endl;
}
void DuplicateSlideCommand::undo(Presentation& presentation) {
    presentation.removeLastSlide();
    std::cout << "Undid duplication." << std::endl;
}

//Scale
void ScaleShapeCommand::execute(Presentation& p) {
    p.scaleShape(index, factor);
    std::cout << "Scaled shape " << index << " by factor " << factor << std::endl;
}

void ScaleShapeCommand::undo(Presentation& p) {
    if (factor != 0) p.scaleShape(index, 1.0 / factor);
    std::cout << "Undid scale." << std::endl;
}

//Recolor
void RecolorShapeCommand::execute(Presentation& p) {
    oldColor = p.getShapeColor(index); 
    p.recolorShape(index, newColor);
    std::cout << "Recolored shape " << index << " to " << newColor << std::endl;
}

void RecolorShapeCommand::undo(Presentation& p) {
    p.recolorShape(index, oldColor); 
    std::cout << "Restored color." << std::endl;
}

//ZOrder
void ZOrderCommand::execute(Presentation& presentation) {
    if (toFront) {
        presentation.bringShapeToFront(shapeIndex);
        std::cout << "Shape " << shapeIndex << " brought to front." << std::endl;
    }
    else {
        presentation.sendShapeToBack(shapeIndex);
        std::cout << "Shape " << shapeIndex << " sent to back." << std::endl;
    }
}

//MoveSlide
void MoveSlideCommand::execute(Presentation& presentation) {
    presentation.moveSlide(fromId, toId);
    std::cout << "Moved slide " << fromId << " to position " << toId << "." << std::endl;
}

void MoveSlideCommand::undo(Presentation& presentation) {
    presentation.moveSlide(toId, fromId);
    std::cout << "Undid slide move." << std::endl;
}

//Lists & Exports
void ListSlidesCommand::execute(Presentation& presentation) {
    std::cout << "--- Slides ---" << std::endl;
    const auto& slides = presentation.getSlides();
    int active = presentation.getActiveSlideId();
    for (size_t i = 0; i < slides.size(); ++i) {
        std::cout << "ID: " << i << ", Name: \"" << slides[i]->getName() << "\""
            << (static_cast<int>(i) == active ? " [ACTIVE]" : "") << std::endl;
    }
    std::cout << "--------------" << std::endl;
}

void ListShapesCommand::execute(Presentation& presentation) {
    const Slide* slide = presentation.getActiveSlide();
    if (!slide) { std::cout << "No active slide." << std::endl; return; }
    
    const auto& shapes = slide->getShapes();
    std::cout << "--- Shapes on '" << slide->getName() << "' ---" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "  [" << i << "] " << shapes[i]->serialize() << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
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
    std::cout << "Slideshow exported to " << filename << std::endl;
}

void SaveCommand::execute(Presentation& presentation) {
    Serializer::savePresentation(presentation, filename);
    std::cout << "Presentation saved to " << filename << std::endl;
}
