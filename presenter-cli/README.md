
---

# Presenter CLI Tool

A command-line interface (CLI) tool for creating and managing presentation slides and adding various geometric shapes and text objects to them.

## General Usage

The general syntax for all commands is as follows:
```sh
./presenter <command> [subcommand] [parameters]
```

---

## 1. Slide Management Commands

These commands are used to create, list, and select slides.

### `create_slide`
Creates a new slide.
- **Syntax:** `create_slide <name>`
- **`name`**: The title of the slide.

**Example:**
```sh
./presenter create_slide "Main Page"
```

### `list_slides`
Displays a list of all created slides, including their unique IDs and names.

**Example:**
```sh
./presenter list_slides
```

### `select_slide`
Selects an active slide. All new objects will be added to this selected slide.
- **Syntax:** `select_slide <ID>`
- **`ID`**: The unique ID of the slide.

**Example:**
```sh
./presenter select_slide 0
```

---

## 2. Object Creation Commands

Use the `add` command with a specific shape as a subcommand to add objects to the currently selected slide.

### `add text`
Adds a text field.
- **Syntax:** `add text <x> <y> "text"`
- **`<x>`, `<y>`**: The starting coordinates of the text.
- **`"text"`**: The text content to display.

**Example:**
```sh
./presenter add text 100 150 "This is text"
```

### `add line`
Adds a line segment.
- **Syntax:** `add line <x1> <y1> <x2> <y2>`
- **`<x1>`, `<y1>`**: The coordinates of the starting point.
- **`<x2>`, `<y2>`**: The coordinates of the ending point.

**Example:**
```sh
./presenter add line 50 50 200 50
```

### `add square`
Adds a square.
- **Syntax:** `add square <x> <y> <side>`
- **`<x>`, `<y>`**: The coordinates of the top-left corner.
- **`<side>`**: The length of the square's side.

**Example:**
```sh
./presenter add square 200 200 80
```

### `add rectangle`
Adds a rectangle.
- **Syntax:** `add rectangle <x> <y> <width> <height>`
- **`<x>`, `<y>`**: The coordinates of the top-left corner.
- **`<width>`**: The width of the rectangle.
- **`<height>`**: The height of the rectangle.

**Example:**
```sh
./presenter add rectangle 300 250 120 60
```

### `add parallelogram`
Adds a parallelogram defined by three of its vertices (the fourth is calculated automatically).
- **Syntax:** `add parallelogram <x1> <y1> <x2> <y2> <x3> <y3>`

**Example:**
```sh
./presenter add parallelogram 10 10 100 10 120 50
```

### `add triangle`
Adds a triangle.
- **Syntax:** `add triangle <x1> <y1> <x2> <y2> <x3> <y3>`
- **`<x1>...<y3>`**: The coordinates of the three vertices.

**Example:**
```sh
./presenter add triangle 100 100 150 200 50 200
```

### `add circle`
Adds a circle.
- **Syntax:** `add circle <cx> <cy> <radius>`
- **`<cx>`, `<cy>`**: The coordinates of the center.
- **`<radius>`**: The length of the radius.

**Example:**
```sh
./presenter add circle 400 400 75
```

### `add ellipse`
Adds an ellipse.
- **Syntax:** `add ellipse <cx> <cy> <rx> <ry>`
- **`<cx>`, `<cy>`**: The coordinates of the center.
- **`<rx>`**: The horizontal radius.
- **`<ry>`**: The vertical radius.

**Example:**
```sh
./presenter add ellipse 500 300 100 50
```

### `add arrow`
Adds an arrow (a directed line).
- **Syntax:** `add arrow <x1> <y1> <x2> <y2>`
- **`<x1>`, `<y1>`**: The coordinates of the starting point.
- **`<x2>`, `<y2>`**: The coordinates of the ending point (where the arrowhead will be).

**Example:**
```sh
./presenter add arrow 10 400 150 350
```

---

## 3. Optional Parameters

You can add optional parameters (flags) to any `add` command to modify the appearance of the object. These flags must be placed after the required parameters.

- **`--color <color>`**: Sets the outline/stroke color of the shape.
- **`--fill <color>`**: Sets the fill color of the shape's interior.
- **`--thickness <number>`**: Sets the thickness of the line or outline.

**Example with Optional Parameters:**
```sh
./presenter add circle 250 250 100 --color red --fill yellow --thickness 3
```
