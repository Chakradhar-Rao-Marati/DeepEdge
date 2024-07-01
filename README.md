# Code is in the Main.cpp File.
# Image Resizing using OpenCV and Custom Implementation

This project performs image resizing using both OpenCV's `resize` function and a custom resize function. The project includes resizing an image using three different interpolation methods and measuring the performance (time taken) for 1000 iterations of each method.

## Prerequisites

- OpenCV library installed
- Visual Studio 2022 installed
- An image file named `G178_2-1080.BMP` in the specified directory

## Instructions to Build and Run in Visual Studio 2022

1. **Download and Install OpenCV:**
   Follow the installation instructions for OpenCV from the official [OpenCV documentation](https://opencv.org/).

2. **Save the Image:**
   Ensure you have the image file `G178_2-1080.BMP` saved in the appropriate directory. Replace `"path_to_your_image/G178_2-1080.BMP"` in the code with the actual path to your image file.

3. **Set Up Visual Studio 2022:**

   - Open Visual Studio 2022 and create a new project.
   - Select "Console App" as the project type and set the project name and location as desired.
   - Add the OpenCV include and library directories to the project configuration:
     - Right-click on the project in the Solution Explorer and select "Properties."
     - Go to "VC++ Directories" and add the OpenCV include directory to "Include Directories."
     - Add the OpenCV library directory to "Library Directories."
   - Link the necessary OpenCV libraries:
     - Go to "Linker" -> "Input" and add the OpenCV libraries (e.g., `opencv_core460.lib`, `opencv_imgproc460.lib`, `opencv_highgui460.lib`, etc.) to "Additional Dependencies."

4. **Add the Code:**

   - Create a new file named **main.cpp** in your project and paste the provided code into this file.

5. **Build and Run the Project:**

   - Click on "Build" in the top menu and select "Build Solution" (or press `Ctrl+Shift+B`) to compile the project.
   - After successful compilation, run the program by clicking "Debug" -> "Start Without Debugging" (or press `Ctrl+F5`).

## Code Explanation

### Loading the Image

The code starts by loading an input image using OpenCV's `imread` function. If the image cannot be loaded, an error message is printed, and the program exits.

### Defining the New Size

The new size for resizing is defined as half of the original width and height of the image.

### Resizing using OpenCV's `resize` Function

The image is resized using three different interpolation methods: `INTER_NEAREST`, `INTER_LINEAR`, and `INTER_CUBIC`. The resized images are saved to the disk.

### Measuring Performance

The time taken to perform 1000 iterations of the resizing operation is measured for each interpolation method using the `chrono` library.

### Custom Resize Function

A custom resize function is implemented using the nearest-neighbor interpolation method. This function manually calculates the corresponding pixel values in the resized image.

### Performance Comparison

The performance of the custom resize function is also measured for 1000 iterations. The results are printed to the console for comparison with the OpenCV functions.

# The time measure for 1000 iterations for opencv in-bulit functions
![Screenshot 2024-07-01 224451](https://github.com/Chakradhar-Rao-Marati/DeepEdge/assets/117653325/2f5587fa-4ce7-485c-ae2d-2719c457a7c2)

# The time measure for 1000 iterations for custom resize functions
![Screenshot 2024-07-01 224834](https://github.com/Chakradhar-Rao-Marati/DeepEdge/assets/117653325/089eec90-e171-49b9-a7fb-4c551b973c9c)
