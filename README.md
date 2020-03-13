# 2D Scene Editor

This application is a 2D scene editor that operates with vector shapes. The project is made by [Manel Mourelo](https://github.com/manelmourelo), [Alfonso Sanchez](https://github.com/Siitoo) & [David Valdivia](https://github.com/ValdiviaDev).

## List of features of the editor:

- File tab:
  - New Scene: Discard every change on the scene and make a new one.
  - Open: Load a scene file previously saved.
  - Save: Save a scene.
  - Exit: Exit from the application.
  The application has a toolbar as a shortcut for the first three features.
  
- Hierarchy:
  - Add entity: Add a entity or object to the scene. This object is a vector shape that the user can edit.
  - Remove entity: With the entity clicked in the hierarchy, the user can delete an object from the scene.
  
- Inspector:
Every shape has an inspector window that has options to edit it. These options are:
  - Translation: Position of the shape in the canvas.
  - Scale: The size of the shape in two axis. In this way, squares can be rectangles, and spheres can be ellipses.
  - Shape: Choose between a circle shape or a recltangle shape for the object.
  - Stroke color: The color of the stroke or outline of the figure.
  - Fill color: The color of the figure.
  - Stroke thickness: How thick is the stroke or outline of the figure.
  - Strocke style: There are various stroke styles:
    - Solid
    - Dash
    - Dot
    - Dash dot
    - Dash dot dot
    - No stroke
    
## List of QT features used:
- Signal/slots events via code to comunicate with the different app elements.
- Style sheet: Used to change the colors of the application and the font of the text.
- Resource files: Used to charge image files into the QT editor to use as icons.
- Special dialogs: Used in the file tab to ask for user confirmation on certain actions.
- Docking: Feature of the QT editor that lets interchange the different UI windows in the application.
- Intercomunication with the UI on the QT editor via code.
