# SimpleSlide CLI: Vector Presentation Engine

**SimpleSlide CLI** is a robust, command-line based vector graphics editor and presentation engine written in **Modern C++ (C++17)**. It allows users to programmatically create slides, manipulate vector shapes, manage undo/redo history, and export presentations to SVG and interactive HTML formats.

The project is engineered with a strict adherence to **SOLID principles**, ensuring high cohesion, loose coupling, and architectural stability.


## Key Features

*   **Slide Management:** Create, duplicate, move (reorder), and delete slides.
*   **Vector Shapes:** Support for **Circle, Rectangle, Line, Text, Image, Ellipse, Triangle, and Polygon**.
*   **Deep Modification:**
    *   **Move:** Reposition shapes on the canvas.
    *   **Scale:** Resize shapes dynamically while maintaining geometric invariants.
    *   **Recolor:** Modify shape attributes (color, fill, stroke width).
    *   **Z-Order:** Bring shapes to front or send to back.
*   **Robust History System:** Unlimited **Undo/Redo** functionality for *every* mutative action (including creation, deletion, modification, and reordering).
*   **Serialization:** Save and Load projects using a custom human-readable script format.
*   **Exporting:**
    *   **SVG:** High-quality vector export for individual slides.
    *   **HTML5 Slideshow:** Generates a standalone HTML file with embedded JavaScript for full-screen presentations.

---

## Architecture & Design

The project follows a **Layered Architecture** to separate concerns between the User Interface (CLI), the Business Logic (Model), and the Infrastructure (Files/Parsing).

### Core Components

1.  **`Presentation` (The Pure Model):**
    *   Acts as the central data structure. It manages the list of `Slide` objects.
    *   **Primitiveness:** It contains *only* logic. It has **zero dependency** on `iostream` or console output. It exposes atomic operations (e.g., `createSlide` returns an ID, `getSlide` returns data) without side effects.
    *   **Invariance:** Enforces validity of data (e.g., prevents invalid slide IDs, ensures positive dimensions for shapes).

2.  **`Command` System (The Bridge):**
    *   Implements the **Command Pattern**.
    *   Acts as the **Controller**. It translates user intent into calls to the `Presentation` model and handles the IO (printing success messages).
    *   Handles **Undo/Redo** logic by storing the *inverse state* (e.g., `RemoveShapeCommand` takes ownership of the deleted shape to restore it later).

3.  **`Executor` (The History Manager):**
    *   Manages the `UndoStack` and `RedoStack`.
    *   Decouples the execution flow from the specific command implementation.

4.  **`Parser` & `Lexer` (The Input Layer):**
    *   Converts raw text strings into `Token` streams and then into `Command` objects.
    *   Supports a flexible flag-based syntax (e.g., `--color red --width 5`).

5.  **`Shape` Hierarchy (Polymorphism):**
    *   Abstract base class `Shape` with concrete implementations (`CircleShape`, `RectShape`, etc.).
    *   Supports deep cloning and polymorphic SVG generation.

### Design Patterns

*   **Command Pattern:** Encapsulates requests as objects, allowing for parameterization and Undo/Redo.
*   **Factory Method:** Used in `ShapeFactory` to create specific shapes based on string identifiers without coupling the client to concrete classes.
*   **Singleton:** The `ShapeRegistry` is a singleton to ensure a single point of registration for shape factories.
*   **Strategy:** The `Executor` defines the strategy for executing and storing commands.
*   **Composite (Simplified):** Slides contain Shapes, treating the collection uniformly.

### Memory Management

The project utilizes **RAII (Resource Acquisition Is Initialization)** and **Smart Pointers** (`std::unique_ptr`) exclusively.
*   **Ownership:** `Presentation` owns `Slide`s. `Slide`s own `Shape`s.
*   **Transfer:** When a shape is removed, ownership is transferred to the `Command` object (for Undo). When a Command is destroyed (if the stack is cleared), the memory is automatically freed.
*   **Safety:** No raw `new`/`delete` calls, ensuring zero memory leaks.

---

## Command Reference (DSL)

The editor accepts commands via a file or interactive shell.

### Slide Operations
| Command | Description |
| :--- | :--- |
| `create_slide "Title"` | Creates a new slide and returns its ID. |
| `select_slide <id>` | Switches the active context to the specified slide. |
| `list_slides` | Displays all slides with their IDs. |
| `move_slide <from> <to>` | Reorders slides. |
| `duplicate_slide <id>` | Creates a deep copy of a slide. |
| `clear_slide` | Removes all shapes from the active slide. |

### Shape Operations
| Command | Arguments | Flags (Optional) |
| :--- | :--- | :--- |
| `add circle` | `cx cy radius` | `--color red --fill blue` |
| `add rectangle` | `x y w h` | `--width 3` |
| `add line` | `x1 y1 x2 y2` | `--color green` |
| `add text` | `x y fontSize` | `--content "Hello World"` |
| `add image` | `x y w h` | `--path "img.png"` |
| `add triangle` | `x1 y1 x2 y2 x3 y3` | |
| `add polygon` | `x1 y1 x2 y2 ...` | |

### Modification
| Command | Description |
| :--- | :--- |
| `move_shape <idx> <x> <y>` | Moves shape at `idx` to new coordinates. |
| `scale_shape <idx> <factor>` | Scales shape (e.g., `1.5` for 150%). |
| `recolor_shape <idx> "color"`| Changes the stroke color. |
| `remove_shape <idx>` | Deletes the shape. |
| `bring_to_front <idx>` | Moves shape to the top of the stack. |
| `send_to_back <idx>` | Moves shape to the bottom. |

### Global / IO
| Command | Description |
| :--- | :--- |
| `undo` / `redo` | Reverts or reapplies the last action. |
| `save "file.txt"` | Saves the project to a script file. |
| `export "slide.svg"` | Exports the *active* slide to SVG. |
| `export_slideshow "p.html"` | Exports *all* slides to an interactive HTML presentation. |

---

## Building and Running

### Prerequisites
*   C++ Compiler supporting C++17 (GCC, Clang, MSVC).

### Compilation
```bash
# Using g++
g++ *.cpp -o simple_slide -std=c++17

# Using CMake (Recommended)
mkdir build && cd build
cmake ..
make
```

### Usage
1.  **Interactive Mode:**
    ```bash
    ./simple_slide
    CMD> create_slide "My Presentation"
    CMD> add circle 100 100 50 --color red
    ```

2.  **File Mode:**
    ```bash
    ./simple_slide scripts/demo.txt
    ```

---

## Export Formats

### 1. SVG (Scalable Vector Graphics)
Ideal for printing or editing in tools like Adobe Illustrator or Inkscape. Generates clean, standard XML-based vectors.

### 2. HTML5 Slideshow
Generates a single, portable `.html` file containing:
*   Embedded SVG data for all slides.
*   CSS for styling and Fullscreen API support.
*   JavaScript for navigation (Next/Prev) and keyboard controls (`Arrow Keys`, `F` for Fullscreen).

---

