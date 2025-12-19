#pragma once
#include "Presentation.h"
#include <string>

class Serializer {
public:
    static void savePresentation(const Presentation& presentation, const std::string& filename);
    static void exportSlideToSvg(const Slide* slide, const std::string& filename);
    static void exportToHtml(const Presentation& presentation, const std::string& filename);
};