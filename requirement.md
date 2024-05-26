# miniRT

---

- [x] **Make makefile**
  - [x] Compile libraries
  - [x] Compile source
  - [x] OS specification
- [x] Initialize project directory
- [x] Initialize program start with minilibx window API

---

- [x] **The Window Management**

  - [x] able to switch to another window
  - [x] able to minimize the window
  - [?] able to remain content adjusted accordingly, when change of the resolution of window(?)
  - [x] able to close the window and quit the program cleanly by
    - [x] pressing ESC key
    - [x] clicking on the cross on the window's frame

> **❗: Testing on Linux is needed, only have done testing in macOS.**

---

- [x] **Check argument**

  - [x] The Specification of the scene description file as a first arguement
    - [x] name the file with the .rt extension
    - [x] each type of element can be separated by one or more line breaks
    - [x] each type of information from an element can be separated by one or more spaces
    - [x] each type of element can be set in any order in the file
    - [x] elements defined by a capital letter can only be declared once in the scene
    - [x] Elements
      - [x] **Ambient lightning**
        - [x] id: **A**
        - [x] ratio in range [0.0, 1.0]: **0.2**
        - [x] color in range [0-255]: **255,255,255**
      - [x] **Camera**
        - [x] id: **C**
        - [x] xyz coordinates of the view point: **-50.0,0,20**
        - [x] 3d normalized orientation vector, in range [-1, 1] for each xyz axis: **0.0,0.0,1.0**
        - [x] FOV, Horizontal field of view in degrees in range [0, 180]: **70**
      - [x] **Light**
        - [x] id: **L**
        - [x] xyz coordinates of the view point: **-40.0,50.0,0.0**
        - [x] light brightness ratio in range [0.0, 1.0]: **0.6**
        - [x] (non-mandatory) color in range [0-255]: **10,0,255**
      - [x] **Sphere**
        - [x] id: **sp**
        - [x] xyz coordinates of the view point: **0.0,0.0,20.6**
        - [x] sphere diameter: **12.6**
        - [x] color in range [0-255]: **10,0,255**
      - [x] **Plane**
        - [x] id: **pl**
        - [x] xyz coordinates of the view point: **0.0,0.0,-10.0**
        - [x] 3d normalized normal vector, in range [-1, 1] for each xyz axis: **0.0,1.0,0.0**
        - [x] color in range [0-255]: **0,0,255**
      - [x] **Cylinder**
        - [x] id: **cy**
        - [x] xyz coordinates of the view point: **50.0,0.0,20.6**
        - [x] 3d normalized vector of axis of cylinder, in range [-1, 1] for each xyz axis: **0.0,0.0,1.0**
        - [x] cylinder diameter: **14.2**
        - [x] cylinder height: **21.42**
        - [x] color in range [0-255]: **10,0,255**
  - [x] If any misconfiguration of any kind is encountered in the file
    - [x] The program must exit properly
    - [x] Return `"Error\n"` followed by an explicit error message of your choice
  - [x] Error Case
    - [x] unsupported file extension
    - [x] missing extension
    - [x] empty file
    - [x] unable to parse an element in description file
    - [x] can not find one or more element(s)
    - [x] unalbe to parse the information in element
    - [x] can not fine required information in element
    - [x] resolution should be bigger than 0

---

- [x] **Provide geometric objects**

  - [x] plane
  - [x] sphere
  - [x] cylinder

---

- [x] **The Object Management**

  - [x] [?] all posible intersections and the inside of the object must be handled correctly
  - [x] able to resize the object's unique properties
    - [x] sphere: diameter
    - [x] cylinder: width, height

---

- [x] **The Geometric Control**

  - [x] objects
    - [x] plane
      - [x] apply translation
      - [ ] apply rotation transformation
    - [x] sphere
      - [x] apply translation
    - [x] cylinder
      - [x] apply translation
      - [ ] apply rotation transformation
  - [x] lights
    - [ ] apply translation
  - [x] cameras
    - [x] apply translation
    - [x] apply rotation transformation

---

- [x] **The Light Management**

  - [x] implement Ambient
  - [x] implement diffuse lighting
  - [ ] spot brightness
  - [x] hard shadows
  - [x] ambiance lighting
    - [x] (objects are never completely in the dark)
  - [x] diffuse lighting
