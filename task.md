# miniRT

- [x] Make makefile

  - [x] Compile libraries
  - [x] Compile source
  - [x] OS specification

- [x] Initialize project directory

- [x] Initialize program start with minilibx window API

- The Window Management

  - able to switch to another window
  - able to minimize the window
  - [?] able to remain content adjusted accordingly, when change of the resolution of window(?)
  - able to close the window and quit the program cleanly by
    - pressing ESC key
    - clicking on the cross on the window's frame

- Check argument
  - The Specification of the scene description file as a first arguement
    - name the file with the .rt extension
    - each type of element can be separated by one or more line breaks
    - each type of information from an element can be separated by one or more spaces
    - each type of element can be set in any order in the file
    - elements defined by a capital letter can only be declared once in the scene
    - Elements
      - **Ambient lightning**
        - id: **A**
        - ratio in range [0.0, 1.0]: **0.2**
        - color in range [0-255]: **255,255,255**
      - **Camera**
        - id: **C**
        - xyz coordinates of the view point: **-50.0,0,20**
        - 3d normalized orientation vector, in range [-1, 1] for each xyz axis: **0.0,0.0,1.0**
        - FOV, Horizontal field of view in degrees in range [0, 180]: **70**
      - **Light**
        - id: **L**
        - xyz coordinates of the view point: **-40.0,50.0,0.0**
        - light brightness ratio in range [0.0, 1.0]: **0.6**
        - (non-mandatory) color in range [0-255]: **10,0,255**
      - **Sphere**
        - id: **sp**
        - xyz coordinates of the view point: **0.0,0.0,20.6**
        - sphere diameter: **12.6**
        - color in range [0-255]: **10,0,255**
      - **Plane**
        - id: **pl**
        - xyz coordinates of the view point: **0.0,0.0,-10.0**
        - 3d normalized normal vector, in range [-1, 1] for each xyz axis: **0.0,1.0,0.0**
        - color in range [0-255]: **0,0,255**
      - **Cylinder**
        - id: **cy**
        - xyz coordinates of the view point: **50.0,0.0,20.6**
        - 3d normalized vector of axis of cylinder, in range [-1, 1] for each xyz axis: **0.0,0.0,1.0**
        - cylinder diameter: **14.2**
        - cylinder height: **21.42**
        - color in range [0-255]: **10,0,255**
  - If any misconfiguration of any kind is encountered in the file
    - The program must exit properly
    - Return `"Error\n"` followed by an explicit error message of your choice
  - Error Case
    - unsupported file extension
    - missing extension
    - empty file
    - unable to parse an element in description file
    - can not find one or more element(s)
    - unalbe to parse the information in element
    - can not fine required information in element
    - resolution should be bigger than 0
- Provide geometric objects

  - plane
  - sphere
  - cylinder

- The Object Management

  - [?] all posible intersections and the inside of the object must be handled correctly
  - able to reize the object's unique properties
    - sphere: diameter
    - cylinder: width, height

- The Geometric Control

  - objects
    - plane
      - apply translation
      - apply rotation transformation
    - sphere
      - apply translation
    - cylinder
      - apply translation
      - apply rotation transformation
  - lights
    - apply translation
  - cameras
    - apply translation
    - apply rotation transformation

- The Light Management
  - implement Ambient
  - implement diffuse lighting
  - spot brightness
  - hard shadows
  - ambiance lighting
    - (objects are never completely in the dark)
  - diffuse lighting
