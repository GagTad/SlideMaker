# SimpleSlide CLI - Scriptable Presentation Engine

**SimpleSlide CLI** is a robust, command-line based tool written in C++ that allows users to create vector-based presentations using a simple scripting language. 

Instead of dragging and dropping shapes manually, you describe your slides using commands. The engine interprets these commands, builds the internal object model, and exports the result as individual **SVG images** or a fully interactive **HTML Slideshow**.

## 🚀 Key Features

*   **Interactive Shell:** Type commands in real-time and see the results.
*   **Script Execution:** Run complex `.txt` or `.prs` scripts to generate presentations automatically.
*   **Vector Graphics:** Supports creating Circles, Rectangles, and Lines with customizable attributes (color, fill, stroke width).
*   **Export Options:** 
    *   Export individual slides to **SVG**.
    *   Export the entire presentation to an interactive **HTML Slideshow** (viewable in any browser).
*   **State Management:** Full **Undo/Redo** support for all creative actions.
*   **Serialization:** Save your work-in-progress to a file and reload it later.
*   **Modern C++:** Built using Smart Pointers (`std::unique_ptr`), STL containers, and SOLID principles.

---

## 🏗️ Architecture & Design Patterns

This project demonstrates clean architecture and object-oriented design:

1.  **Command Pattern:** Every action (`CreateSlide`, `AddShape`, `SelectSlide`) is encapsulated in a Command object. This enables the robust **Undo/Redo** system.
2.  **Factory Pattern:** The `ShapeFactory` and `ShapeRegistry` allow for dynamic creation of shapes ("circle", "rectangle") without coupling the logic to specific classes. Adding a new shape (like Text) requires no changes to the parser.
3.  **Interpreter Pattern (Lexer/Parser):** A custom tokenizer and recursive descent parser process the input text and convert it into executable commands.
4.  **Presentation Facade:** The `Presentation` class acts as the main interface, protecting the internal state (`Slide` objects) from direct external modification.
5.  **Modern Memory Management:** No raw pointers are owned; `std::unique_ptr` is used throughout to ensure memory safety.

---

## 🛠️ How to Build & Run

### Prerequisites
*   C++17 compliant compiler (MSVC, GCC, Clang).
*   Visual Studio 2022 (recommended) or CMake.

### Running
1.  **Interactive Mode:**
    Run the executable without arguments.
    ```bash
    ./SlideMaker.exe
    ```
2.  **File Mode:**
    Pass a script file as an argument.
    ```bash
    ./SlideMaker.exe my_script.txt
    ```

---

## 📖 Command Reference

### Slide Management
| Command | Description | Example |
| :--- | :--- | :--- |
| `create_slide "Name"` | Creates a new slide with the given name. | `create_slide "Intro"` |
| `select_slide <ID>` | Switches focus to a specific slide ID (starts at 0). | `select_slide 0` |
| `list_slides` | Displays all slides and their IDs in the console. | `list_slides` |

### Drawing Shapes
Usage: `add <type> <params> [flags]`

| Shape Type | Parameters | Example |
| :--- | :--- | :--- |
| **circle** | `cx cy radius` | `add circle 100 100 50` |
| **rectangle** | `x y width height` | `add rectangle 10 10 200 100` |
| **line** | `x1 y1 x2 y2` | `add line 0 0 800 600` |

**Styling Flags:**
*   `--color "value"` : Stroke color (e.g., "red", "#FF0000"). Default: "black".
*   `--fill "value"` : Fill color. Default: "transparent".
*   `--width "value"` : Stroke width in pixels. Default: "2".

### Project Management
| Command | Description |
| :--- | :--- |
| `export "file.svg"` | Exports the **currently selected** slide to an SVG image. |
| `export_slideshow "file.html"` | Exports **all slides** into a single HTML file with navigation controls. |
| `save "backup.prs"` | Serializes the current state into a script file. |
| `undo` | Reverts the last action (shape addition, slide creation, selection). |
| `redo` | Reapplies the last undone action. |
| `exit` | Closes the application (Interactive mode only). |

---

## 📝 Example Script

Create a file named `demo.txt` and run it:

```text
# Step 1: Create the first slide
create_slide "Solar System"
select_slide 0

# Draw the Sun
add circle 400 300 100 --color "orange" --fill "yellow"

# Draw a Planet
add circle 600 350 30 --color "blue" --fill "lightblue"

# Step 2: Create a second slide
create_slide "Abstract Art"
select_slide 1

# Draw lines and rectangles
add line 0 0 800 600 --width "5" --color "purple"
add rectangle 50 50 200 150 --fill "rgba(0,255,0,0.5)"

# Step 3: Undo mistake and Export
undo 
export_slideshow "presentation.html"
